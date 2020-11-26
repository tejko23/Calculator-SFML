#pragma once
#include <string>

class Tmath {
public:
	Tmath(int, int);
	void addExp(std::string);
	std::string getResult();
	std::string getExp();
	int getAmountop();
	int getAmountcp();
	
private:
	std::string expression{};
	std::string result{};
	int op_amnt = 0;
	int cp_amnt = 0;

	int op{};
	int cp{};
	

	void prepareExp();
	std::string calcTheExp(std::string);
	std::string trueMath(std::string);
	std::string mMath(std::string, std::string, std::string);
	void zerem(std::string&);
};