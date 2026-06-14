#include <iostream>
#include <fstream>
#include "turingmachine.h"

void parcer(std::ifstream& inFile, char* symbol) {

	char ch;
	int index = 0;
	
	while ((ch = static_cast<char>(inFile.get())) != EOF && ch != ' ' && ch != '\n') {
		symbol[index++] = ch;
	
	}
	symbol[index] = '\0';

}

int main(int argc, char* argv[]) {

	if (argc != 4) {
		std::cerr << "Cannot start TM " << std::endl;
		return 1;
	}

	std::ifstream inFile(argv[1]);
	if (!inFile) {
		std::cout << "Could not open file" << std::endl;
		return 1;
	}

	int ruleCnt = 0;
	const int ruleSize = 1000;
	Rule* ruleMassive = new Rule[ruleSize];
	while ((inFile.peek()) != EOF && ruleCnt < ruleSize) {

		parcer(inFile, ruleMassive[ruleCnt].currentState);

		ruleMassive[ruleCnt].inputSymbol = static_cast<char>(inFile.get());
		inFile.get();

		if (inFile.get() == '-' && inFile.get() == '>') {
			inFile.get();
		}

		parcer(inFile, ruleMassive[ruleCnt].newState);

		ruleMassive[ruleCnt].writeSymbol = static_cast<char>(inFile.get());

		inFile.get();

		ruleMassive[ruleCnt].move = static_cast<char>(inFile.get());

		while (inFile.peek() == ' ' || inFile.peek() == '\n') {
			inFile.get(); //пропустим пробелы в конце строки
		}

		ruleCnt++;

	}

	Program prog;

	for (int i = 0; i < ruleCnt; ++i) {
		prog.add(ruleMassive[i]);
	}

	//инициализируем размер ленты
	long long tapeSize = atoll(argv[2]);
	std::string tape(tapeSize, '0');
	
	//инициализируем количество тактов
	long long maxSteps = atoi(argv[3]);

	TuringMachine tm(tapeSize, prog);
	tm.calc(tape, maxSteps);
	std::cout << '\n';
	delete[] ruleMassive;
	return 0;
}
