#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>
#include "Tmath.hpp"

using namespace std;

Tmath::Tmath(int a, int b) : op(a), cp(b) {}

void Tmath::addExp(string s) {
	if (s != "") {
		expression = s;
	}
	else expression = "0";
	prepareExp();
	result = calcTheExp(expression);
}

string Tmath::getResult() {
	return result;
}

string Tmath::getExp() {
	return expression;
}

int Tmath::getAmountop() {
	return op;
}

int Tmath::getAmountcp() {
	return cp;
}

void Tmath::prepareExp() {
	//Delete math markings from the end
	while ((expression.back() == '+' || expression.back() == '-' ||
		expression.back() == '*' || expression.back() == '/' ||
		expression.back() == '.' || expression.back() == '(') && 
		expression.size() > 1) {
		if (expression.back() == '(') op--;
		expression.pop_back();
	}

	//Put 0 if the expression is wrong
	if (expression == "+" || expression == "-" || expression == "*" ||
		expression == "/" || expression == ".") {
		expression = "0";
	}


	/// brackets / parentheses counter
	while (op != cp) {
		if (op > cp) {
			expression += ")";
			cp++;
		}
		else if (op < cp) {
			//expression.insert(0, "(");
			string temp = "(" + expression;
			expression = temp;
			op++;
		}
	}

	//Remove empty parentheses
	size_t pos = 0;
	while ((pos = expression.find("()", pos)) != string::npos) {
		expression.erase(pos, 2);
		cp--;
		op--;
		pos = 0;
	}

	//Insert the right markings before and after the brackets
	pos = 0;
	while ((pos = expression.find("(", pos)) != string::npos) {
		if (pos != 0) {
			if (expression[pos - 1] != '+' && expression[pos - 1] != '-' &&
				expression[pos - 1] != '*' && expression[pos - 1] != '/' &&
				expression[pos - 1] != '(' ) {
				expression.insert(pos, "*");
				pos++;
			}
		}
		pos++;
	}

	pos = 0;
	while ((pos = expression.find(")", pos)) != string::npos) {
		if (pos != expression.size() - 1) {
			if (expression[pos + 1] != '+' && expression[pos + 1] != '-' &&
				expression[pos + 1] != '*' && expression[pos + 1] != '/' &&
				expression[pos + 1] != ')') {
				expression.insert(pos + 1, "+");
				pos++;
			}
		}
		pos++;
	}

	//Insert 0 if empty
	if (expression.empty()) expression = "0";
}


string Tmath::calcTheExp(string act_exp) {
	//Sometimes duplicate math signs can happen, this can fix it
	size_t pos = 0;
	while ((pos = act_exp.find("--", pos)) != string::npos) {
		act_exp.replace(pos, 2, "+");
		pos = 0;
	}

	pos = 0;
	while ((pos = act_exp.find("+-", pos)) != string::npos) {
		act_exp.replace(pos, 2, "-");
		pos = 0;
	}

	//We are looking for math expressions hidden in parentheses
	//It works recursively
	pos = act_exp.find("(");
	if (pos != string::npos) {
		size_t pos_c = 0;

		while ((pos_c = act_exp.find(")", pos_c)) != string::npos) {
			cp_amnt++;
			string temp = act_exp.substr(0, pos_c + 1);
			size_t poso = 0;
			size_t tposo = 0;

			while ((poso = temp.find("(", poso)) != string::npos) {
				op_amnt++;
				if (op_amnt == 1) tposo = poso;
				poso++;
			}
			if (op_amnt == cp_amnt) {
				if (tposo == 0 && pos_c == act_exp.size() - 1) {
					op_amnt = 0;
					cp_amnt = 0;
					act_exp = act_exp.substr(tposo + 1, pos_c - 1);
					return calcTheExp(act_exp);
				}
				else {
					op_amnt = 0;
					cp_amnt = 0;
					string rtemp = act_exp.substr(tposo + 1, 
						pos_c - (tposo + 1));
					act_exp.replace(tposo, pos_c - (tposo - 1), 
						calcTheExp(rtemp));
					return calcTheExp(act_exp);
				}
			}
			op_amnt = 0;
			pos_c++;
		}
	}
	op_amnt = 0;
	cp_amnt = 0;
	//If we already have a math expression without parentheses
	return trueMath(act_exp);
}

string Tmath::trueMath(string exp) {
	//We start with multiplication and division
	size_t found_ix = exp.find_first_of("*/");
	if (found_ix != string::npos) {
		//If we found something, we are looking for the first part
		size_t b_ix = exp.find_last_of("+-", found_ix);
		//"temp_one" is the first part of expression
		string temp_one;

		if (b_ix == string::npos || b_ix == 0) {
			b_ix = 0;
			temp_one = exp.substr(b_ix, found_ix);
		}
		else temp_one = exp.substr(b_ix + 1, found_ix - (b_ix + 1));

		//Now it's time for the second part
		size_t c_ix = exp.find_first_of("*/+-", found_ix + 1);
		if ((c_ix - (found_ix + 1)) == 0) {
			c_ix = exp.find_first_of("*/+-", found_ix + 2);
		}
		//"temp_two" is obviously the other part
		string temp_two = exp.substr(found_ix + 1, c_ix - (found_ix + 1));

		//And "exp_char" is a math mark
		string exp_char = exp.substr(found_ix, 1);

		//We send our math expression to the final computation function
		string score = mMath(temp_one, temp_two, exp_char);
		zerem(score);

		//Instead of the calculated expression, we insert its result
		size_t len_of_exp = temp_one.size() + exp_char.size() + temp_two.size();
		if (b_ix == 0) {
			exp.replace(b_ix, len_of_exp, score);
		}
		else exp.replace(b_ix + 1, len_of_exp, score);

		//We repeat recursively
		return trueMath(exp);
	}

	//We do a little differently when there is no multiplication or division
	found_ix = exp.find_first_of("+-");
	if (found_ix == 0) found_ix = exp.find_first_of("+-", found_ix + 1);
	if (found_ix != string::npos) {
		//The first part
		string temp_one = exp.substr(0, found_ix);
		
		//The last part
		size_t c_ix = exp.find_first_of("*/+-", found_ix + 1);
		string temp_two;
		if (c_ix != string::npos) {
			temp_two = exp.substr(found_ix + 1, c_ix - (found_ix + 1));
		}
		else temp_two = exp.substr(found_ix + 1, c_ix);

		//Math mark
		string exp_char = exp.substr(found_ix, 1);

		//We calculate the result and put it in the right place
		size_t len_of_exp = temp_one.size() + exp_char.size() + temp_two.size();
		string score = mMath(temp_one, temp_two, exp_char);
		zerem(score);
		exp.replace(0, len_of_exp, score);

		//We repeat recursively
		return trueMath(exp);
	}

	//If everything is ok, we return the result
	else return exp;
}

string Tmath::mMath(string one, string two, string mchar) {
	long double first_ex = stold(one);
	long double sec_ex = stold(two);
	stringstream ss;

	if (mchar == "*") {
		ss << fixed << setprecision(12) << first_ex * sec_ex;
	}
	else if (mchar == "/") {
		ss << fixed << setprecision(12) << first_ex / sec_ex;
	}
	else if (mchar == "+") {
		ss << fixed << setprecision(12) << first_ex + sec_ex;
	}
	else if (mchar == "-") {
		ss << fixed << setprecision(12) << first_ex - sec_ex;
	}

	return ss.str();
}

void Tmath::zerem(string& score) {
	//This func removes '0' and '.' from the end of the result
	while (score.size() > 1 && score[score.size() - 1] == '0') {
			score.pop_back();
	}
	if (score[score.size() - 1] == '.') score.pop_back();
}