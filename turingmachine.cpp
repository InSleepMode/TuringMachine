#include "turingmachine.h"
#include <iostream>
#include <fstream>
#include <cstring>


TuringMachine::TuringMachine(long long tapeSize, const Program& prog) :
	sizeOfTape(tapeSize), headPos(0), program(prog), rulesAmount(static_cast<int>(prog.size())) {
	if (prog.size() > 0) {
		strncpy(current_state, prog.getRules()[0].currentState, sizeof(current_state) - 1);
		current_state[sizeof(current_state) - 1] = '\0';
	}
}


unsigned long long TuringMachine::calc(std::string& tape, unsigned long long maxsteps) {


	const Rule* rules = program.getRules();
	unsigned long long current_steps = 0;
	headPos = 0;
	while (current_steps < maxsteps) {


		char currentSymbol = tape[headPos];

		bool matched = false;

		for (unsigned long long i = 0; i < rulesAmount; ++i) {

			//проверим что состояния соответствуют и входное число так же нас удовлетворяет
			if (strcmp(current_state, rules[i].currentState) == 0 && currentSymbol == rules[i].inputSymbol) {
				//перейдем в новое состояние
				strncpy(current_state, rules[i].newState, sizeof(current_state) - 1);

				//перепишем новое число в ленте
				tape[headPos] = rules[i].writeSymbol;

				//передвинем головку машины
				if (rules[i].move == 'R') {
					moveRight(headPos,(tape.size()));

				}
				else if (rules[i].move == 'L') {
					moveLeft(headPos, (tape.size()));
				}
				else {
				}
				matched = true;
				++current_steps;
				break;

			}
		}

		if (!matched) {
			break;
		}
	}

	if (current_steps >= maxsteps) {
		std::cout << "Not applicable";
		return 0;
	}

	std::cout << current_steps << '\n';

	//найдем индекс последней единицы
	unsigned long long lastOne = -1;
	unsigned long long current = headPos;
	for (unsigned long long i = 0; i < tape.size(); ++i) {
		if (tape[current] == '1') {
			lastOne = current;
		}
		current = (current + 1) % tape.size();
	}

	if (lastOne == -1) {
		std::cout << "0";
		return 0;
	}
	
	//выведем получившуюся ленту
	if (lastOne >= headPos) {
		for (unsigned long long i = headPos; i <= lastOne; ++i) {
			std::cout << tape[i];
		}
	}
	else {
		//учитывая что ленца кольцевая выводим от начала головки до конца ленты
		for (unsigned long long i = headPos; i < tape.size(); ++i) {
			std::cout << tape[i];
		}
		//так же от начала до позиции последней единицы 
		for (unsigned long long i = 0; i <= lastOne; ++i) {
			std::cout << tape[i];
		}
	}

	return current_steps;
}

