#include "Tscreen.hpp"
#include "Tmath.hpp"
#include <iostream>

using namespace std;

Tscreen::Tscreen() {
	display.setSize(sf::Vector2f(326, 146));
	display.setFillColor(sf::Color(0x483e3dff));
	display.setOrigin(0, 0);
	display.setPosition(sf::Vector2f(5, 5));
	font.loadFromFile("fonts/digital-7.ttf");
	expression.setFont(font);
	result.setFont(font);
	expression.setCharacterSize(30);
	result.setCharacterSize(60);
	expression.setFillColor(sf::Color::White);
	result.setFillColor(sf::Color::White);
	result.setString("0");

	sf::FloatRect bounds = result.getLocalBounds();
	expression.setPosition(sf::Vector2f(300, 10));
	result.setPosition(sf::Vector2f(300 - bounds.width, 48));
}

void Tscreen::addValue(string s) {
	if (s == "C") {
		exp.clear();
		result.setString("0");
		nofop = 0;
		nofcp = 0;
	}
	else if (s == "CE") {
		if (exp.getSize() > 0 && (exp[exp.getSize() - 1] == '(' ||
			exp[exp.getSize() - 1] == ')' ||
			exp[exp.getSize() - 1] == '+' ||
			exp[exp.getSize() - 1] == '-' ||
			exp[exp.getSize() - 1] == '*' ||
			exp[exp.getSize() - 1] == '/' )) {
			if (exp[exp.getSize() - 1] == '(') nofop--;
			if (exp[exp.getSize() - 1] == ')') nofcp--;
			exp.erase(exp.getSize() - 1);
		}
		while (exp.getSize() > 0 && ((exp[exp.getSize() - 1] >= 48 &&
			exp[exp.getSize() - 1] <= 57) || exp[exp.getSize() - 1] == 46)) {
			exp.erase(exp.getSize() - 1);
		}
	}
	else if (s == "<-") {
		if (exp.getSize() > 0) {
			if (exp[exp.getSize() - 1] == '(') nofop--;
			if (exp[exp.getSize() - 1] == ')') nofcp--;
			exp.erase(exp.getSize() - 1);
		}
		else return;
	}
	else if (s == "=") {
		Tmath calc(nofop, nofcp);
		calc.addExp(std::string(exp));
		exp = calc.getExp();
		nofop = calc.getAmountop();
		nofcp = calc.getAmountcp();
		result.setString(calc.getResult());
	}
	else if (s == "(") {
		nofop++;
		exp += s;
	}
	else if (s == ")") {
		nofcp++;
		exp += s;
	}
	else {
		if (exp.getSize() == 1 && exp[0] == '0' && (s == "1" || s == "2" || 
			s == "3" || s == "4" || s == "5" || s == "6" || s == "7" ||
			s == "8" || s == "9")) {
			exp.replace(0, 1, s);
		}
		else exp += s;
	}

	expression.setString(exp);
	sf::FloatRect bounds = expression.getLocalBounds();
	expression.setPosition(sf::Vector2f(300 - bounds.width, 10));

	bounds = result.getLocalBounds();
	result.setPosition(sf::Vector2f(300 - bounds.width, 48));
}

string Tscreen::askforButtons() {
	int exps = exp.getSize();
	string forbidden;
	if (exps == 0) {
		forbidden = ")+*/.=";
	}
	else {
		if (exp[exps - 1] == '(') forbidden = "+*/.";
		else if (exp[exps - 1] == ')') forbidden = ".";
		else if (exp[exps - 1] == '+') forbidden = ")+-*/.";
		else if (exp[exps - 1] == '-') forbidden = ")+-*/.";
		else if (exp[exps - 1] == '*') forbidden = ")+*/.";
		else if (exp[exps - 1] == '/') forbidden = ")+*/.";
		else if (exp[exps - 1] == '(') forbidden = ")+*/.";
		else if (exp[exps - 1] == '.') forbidden = "()+-*/.";
		else if ((exp[exps - 1] >= 48 && exp[exps - 1] <= 57) && findDot()) 
			forbidden = ".";
		else forbidden = "";
	}
	if (nofcp == nofop){
		forbidden += ")";
	}

	return forbidden;
}

bool Tscreen::findDot() {
	size_t pos;
	string stdexp = exp.toAnsiString();
	pos = stdexp.find_last_of("()+-*/");

	if (pos != string::npos) {
		size_t posf = stdexp.find(".", pos);
		if (posf != string::npos) return true;
		else return false;
	}
	else {
		size_t posf = stdexp.find(".", 0);
		if (posf != string::npos) return true;
		else return false;
	}
}