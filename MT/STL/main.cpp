#include <iostream>
#include <set>
#include <vector>
#include <string>

using namespace std;

enum states {
	initial = 0,
	sign,
	coeff,
	var,
	s_pow,
	end
};

enum symbols {
	sy_sign = 0,
	digit,
	letter,
	sy_pow,
	endl
};

struct summand {
	bool isPositive;
	int coeff;
	std::string var;
	unsigned int pow;

	summand() {
		pow = 1;
		coeff = 1;
	}

	std::string toString(bool needPosSign) const {
		std::string res = "";

		if (!isPositive) res += "-";
		else if (needPosSign)
			res += "+";

		int actCoeff = coeff * pow;
		int actPow = pow - 1;
		
		if (actCoeff > 1) res += std::to_string(actCoeff);

		if (actPow == 0 && actCoeff == 1) res += "1";
		else {
			if (actCoeff > 1) res += "*";
			res += var;
			if (actPow > 1) res += "^" + std::to_string(actPow);
		}

		return res;
	};

    bool isConst() {
        return pow == 1;
    };
};

struct summand *current_summand = NULL;
std::vector<char> buf;
char *cur = NULL;

struct pow_comparator {
	bool operator()(const summand &a, const summand &b) {
		return a.pow >= b.pow;
	}
};
std::set<summand, pow_comparator> s;

bool isPos(const char c) {
	return c == '+';
}

typedef void(*transition_callback)(enum states state, enum symbols symbol);
struct transition {
	enum states new_state;
	transition_callback worker;
};

int getIntFromBuf() {
	return atoi(std::string(buf.begin(), buf.end()).c_str());
}

void init_to_sign(enum states state, enum symbols symbol) {
	current_summand = new summand();
	current_summand->isPositive = false;
}

void init_to_digit(enum states state, enum symbols symbol) {
	current_summand = new summand();
	current_summand->isPositive = true;
	buf.push_back(*cur);
}

void init_to_letter(enum states state, enum symbols symbol) {
	current_summand = new summand();
	current_summand->isPositive = true;
	current_summand->var = *cur;
}

void sign_to_digit(enum states state, enum symbols symbol) {
	buf.push_back(*cur);
}

void sign_to_letter(enum states state, enum symbols symbol) {
	current_summand->var = *cur;
}

void coeff_to_sign(enum states state, enum symbols symbol) {
	delete(current_summand);
	current_summand = new summand();
	current_summand->isPositive = isPos(*cur);
}

void coeff_to_digit(enum states state, enum symbols symbol) {
	buf.push_back(*cur);
}

void coeff_to_letter(enum states state, enum symbols symbol) {
	current_summand->coeff = getIntFromBuf();
	current_summand->var = *cur;
	buf.clear();
}

void coeff_to_end(enum states state, enum symbols symbol) {
	buf.clear();
}

void var_to_end(enum states state, enum symbols symbol) {
	s.insert(*current_summand);
	delete(current_summand);
}

void var_to_sign(enum states state, enum symbols symbol) {
	s.insert(*current_summand);
	coeff_to_sign(state, symbol);
}

void var_to_pow(enum states state, enum symbols symbol) {

}

void pow_to_digit(enum states state, enum symbols symbol) {
	buf.push_back(*cur);
}

void pow_to_sign(enum states state, enum symbols symbol) {
	current_summand->pow = getIntFromBuf();
	buf.clear();
	var_to_sign(state, symbol);
}

void pow_to_end(enum states state, enum symbols symbol) {
	current_summand->pow = getIntFromBuf();
	buf.clear();
	s.insert(*current_summand);
	delete (current_summand);
}

void doNothing() {}

void setInvalidState(enum states state, enum symbols symbol) {
	if (current_summand) delete(current_summand);
	if (buf.size() > 0) buf.clear();
}

struct transition FSM_table[5][5] = {
	//states::initial
	{ 
		{ states::sign, init_to_sign }, //symbols::s_sign
		{ states::coeff, init_to_digit }, //symbols::digit
		{ states::var, init_to_letter }, //symbols::letter
		{ states::end, setInvalidState }, //symbols::sy_pow
		{ states::end, setInvalidState } //symbols::endl
	},
	//states::sign
	{
		{ states::sign, setInvalidState }, //symbols::s_sign
		{ states::coeff, sign_to_digit }, //symbols::digit
		{ states::var, sign_to_letter }, //symbols::letter
		{ states::end, setInvalidState }, //symbols::sy_pow
		{ states::end, setInvalidState } //symbols::endl
	},
	//states::coeff
	{
		{ states::sign, coeff_to_sign }, //symbols::s_sign
		{ states::coeff, coeff_to_digit }, //symbols::digit
		{ states::var, coeff_to_letter }, //symbols::letter
		{ states::end, setInvalidState }, //symbols::sy_pow
		{ states::end, coeff_to_end } //symbols::endl
	},
	//states::var
	{
		{ states::sign, var_to_sign }, //symbols::s_sign
		{ states::end, setInvalidState }, //symbols::digit
		{ states::end, setInvalidState }, //symbols::letter
		{ states::s_pow, var_to_pow }, //symbols::sy_pow
		{ states::end, var_to_end } //symbols::endl
	},
	//states::s_pow
	{
		{ states::sign, pow_to_sign }, //symbols::s_sign
		{ states::s_pow, pow_to_digit }, //symbols::digit
		{ states::end, coeff_to_letter }, //symbols::letter
		{ states::end, setInvalidState }, //symbols::sy_pow
		{ states::end, pow_to_end } //symbols::endl
	}
};

symbols getCharType(char c) {
	if (c == '\0')                                        return symbols::endl;
	if (c == '+' || c == '-')                             return symbols::sy_sign;
	if (c == '^')                                         return symbols::sy_pow;
	if (c >= '0' && c <= '9')                             return symbols::digit;
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return symbols::letter;

	return symbols::endl;
}

std::string derivative(std::string polynomial) {
	cur = &polynomial[0];

	states cur_state = states::initial;
	while (cur) {
		if (*cur != ' ' && *cur != '*') {
			symbols cur_symbol = getCharType(*cur);
			transition tran = FSM_table[cur_state][cur_symbol];
			cur_state = tran.new_state;
			tran.worker(cur_state, cur_symbol);
			if (cur_symbol == symbols::endl) break;
		}

		cur++;
	}

	int iterNum = 1;
	std::string res = "";
    int lastSummand = 0;
	for (auto i = s.begin(); i != s.end(); i++) {
        summand cur_s = *i;
        if (!cur_s.isConst()) {
            std::string ii = cur_s.toString(iterNum > 1);
            res += ii;
        } else {
            if (cur_s.isPositive) lastSummand += cur_s.coeff;
            else lastSummand -= cur_s.coeff;
        }
		iterNum++;
	}

    if (lastSummand != 0) {
        res += lastSummand > 0 ? "+" : "-";
        res += std::to_string(lastSummand);
        if (res[0] == '+') res.erase(0, 1);
    }

	return res;
}

void test(std::string data) {
	cout << "Testing: " << data << "   ->   ";
	std::string res = derivative(data);
	cout << res;

	cout << std::endl << std::endl;
	s.clear();
}

int main() {
    /*int t = atoi("+1");
	test("x^2+x");
	test("2*x^100+100*x^2");
	test("x^10000+x+1");
	test("-x^2-x^3");*/
	test("2*x^100-x+x+x+x+x+x^2+x+x-3x+x+x");

	//cout << std::endl << "Hello, World!" << std::endl;
	return 0;
}
