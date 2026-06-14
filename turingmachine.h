#include <fstream> 
#include <iostream>
#include <string>
#include <cstring>


struct Rule {

	char currentState[16];
	char inputSymbol;
	char newState[16];
	char writeSymbol;
	char move;

};

class Program {
private:

	Rule* rules;
	size_t size_;
	size_t maxSize = 0;

public:

	Program() : rules(nullptr), size_(0), maxSize(0){}


	Program(const Program& other) : size_(other.size_) {
		rules = new Rule[size_];
		for (size_t i = 0; i < size_; ++i) {
			rules[i] = other.rules[i];
		}
	}

	void enhance(size_t newMaxsize) {
		Rule* newRules = new Rule[newMaxsize];
		for (size_t i = 0; i < size_; ++i) {
			newRules[i] = rules[i];
		}
		delete[] rules;
		rules = newRules;
	}

	void add(const Rule& rule) {
		if (size_ >= maxSize) {
			enhance(size_ == 0 ? 1 : size_ * 2);
		}
		rules[size_++] = rule;
	}


	void swap(Program& other) noexcept {
		std::swap(rules, other.rules);
		std::swap(size_, other.size_);
	}

	Program& operator=(const Program& other) {
		if (this != &other) {
			Program temp(other);
			swap(temp);
		}
		return *this;
	}

	const Rule* getRules() const { 
		return rules;
	}

	size_t size() const { 
		return size_;
	}


	~Program() {
		delete[] rules;
	}
};

class TuringMachine {

private:

	unsigned long long headPos;
	long long sizeOfTape;
	Program program;
	int rulesAmount;
	char current_state[16];

public:

	TuringMachine(long long tapeSize, const Program& prog);

	TuringMachine(const TuringMachine& other) { //конструктор копирования
		sizeOfTape = other.sizeOfTape;
		headPos = other.headPos;
		rulesAmount = other.rulesAmount;
		strncpy(current_state, other.current_state, sizeof(current_state));
		program = other.program;

	}

	void swap(TuringMachine& other) noexcept {
		std::swap(headPos, other.headPos);
		std::swap(sizeOfTape, other.sizeOfTape);
		std::swap(program, other.program);
		std::swap(rulesAmount, other.rulesAmount);
		std::swap(current_state, other.current_state);
	}

	TuringMachine& operator=(const TuringMachine& other) { //оператор присваивания
		if (this != &other) {
			TuringMachine temp(other);

			// Обмен данными
			std::swap(headPos, temp.headPos);
			std::swap(sizeOfTape, temp.sizeOfTape);
			std::swap(rulesAmount, temp.rulesAmount);
			std::swap(program, temp.program);
			std::swap(current_state, temp.current_state);
		}
		return *this;
	}

	unsigned long long calc(std::string& tape, unsigned long long maxsteps);

	void static moveRight(unsigned long long& headPos, unsigned long long tapeSize) {
		headPos = (headPos + 1) % tapeSize;
	}

	void static moveLeft(unsigned long long& headPos, unsigned long long tapeSize) {
		headPos = (headPos - 1 + tapeSize) % tapeSize;
	}

	~TuringMachine() = default;

};
