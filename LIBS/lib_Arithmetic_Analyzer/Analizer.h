// Copyright 2022 Filatov Maxim
#ifndef INCLUDE_ANALIZER_H_
#define INCLUDE_ANALIZER_H_

#define START_NUMBERS 48
#define END_NUMBERS 57

#include <iostream>
#include <ostream>
#include <vector>
#include <functional>
#include <string>
#include <cmath>
#include <stack>

class Node {
public:
	std::string m_data;
	Node* m_left;
	Node* m_right;
public:
	Node() {
		m_left = nullptr;
		m_right = nullptr;
	}

	Node(std::string data) {
		m_data = data;
		m_left = nullptr;
		m_right = nullptr;
	}
	~Node() {}

	//std::pair<Node*, bool> find_empty_slot_right_step() {
	//	/*std::pair<Node*, bool> ansR;
	//	std::pair<Node*, bool> ansL;*/
	//	if (this->m_right == nullptr) {
	//		return { this, true };
	//	}
	//	else if (this->m_right->m_data[0] <= START_NUMBERS || this->m_right->m_data[0] >= END_NUMBERS) {
	//		return this->m_right->find_empty_slot_right_step();
	//	}
	//	else if ((this->m_left->m_data[0] <= START_NUMBERS || this->m_left->m_data[0] >= END_NUMBERS) && this->m_left != nullptr) {
	//		return this->m_left->find_empty_slot_right_step();
	//	}
	//	return { this, false };
	//}

	bool can_add() {
		if (this == nullptr) {
			return true;
		}
		if (this->m_data[0] >= START_NUMBERS && this->m_data[0] <= END_NUMBERS) {
			return false;
		}
		return (this->m_right->can_add() || this->m_left->can_add());
	}

	void insert(std::string data) {
		if (this->m_right->can_add()) {
			if (this->m_right == nullptr) {
				this->m_right = new Node(data);
			}
			else {
				this->m_right->insert(data);
			}
		}
		else if (this->m_left->can_add()) {
			if (this->m_left == nullptr) {
				this->m_left = new Node(data);
			}
			else {
				this->m_left->insert(data);
			}
		}
	}

private:

};

using CPS_TYPE = double;
typedef CPS_TYPE (*FUNC) (std::string);
static std::string NUMBER_ALPHABET = "0123456789";
static std::string ACTION_SIGN = "+-/*^";
static std::string LETTERS_ALPHABET = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";

enum class PRIORITY { none, low, medium, high, very_high };
bool operator == (PRIORITY l, PRIORITY r) { return static_cast<int>(l) == static_cast<int>(r) ? true : false; }
bool operator != (PRIORITY l, PRIORITY r) { return static_cast<int>(l) != static_cast<int>(r) ? true : false; }
bool operator < (PRIORITY l, PRIORITY r) { return static_cast<int>(l) < static_cast<int>(r) ? true : false; }
bool operator > (PRIORITY l, PRIORITY r) { return static_cast<int>(l) > static_cast<int>(r) ? true : false; }

static class CPS {
public:
	static struct VAR {
		char symbol;
		CPS_TYPE value;
		VAR create(char _symbol, CPS_TYPE _value) {
			symbol = _symbol;
			value = _value;
			return *this;
		}
		VAR set_value(CPS_TYPE _value) {
			value = _value;
			return *this;
		}
	};
	static class STORAGE {
	public:
		static std::vector<CPS::VAR> VARIABLES;
		static std::vector<std::pair<std::string, FUNC>> FUNCTIONS;

	public:
		STORAGE() {}
		~STORAGE() {}

		static void add_variable(CPS::VAR var) {
			VARIABLES.push_back(var);
		}
		static void change_variable(VAR var) {
			find_var(var.symbol).set_value(var.value);
		}
		static VAR& find_var(char s) {
			for (auto& elem : VARIABLES) {
				if (elem.symbol == s) {
					return elem;
				}
			}
			throw "Не нашёл нужную переменную";
		}
		static void add_func(std::string name, FUNC _func) {
			FUNCTIONS.emplace_back(name, _func);
		}
		static int find_func_id(std::string name) {
			int size = FUNCTIONS.size();
			for (int i = 0; i < size; i++) {
				if (FUNCTIONS[i].first == name) {
					return i;
				}
			}
			return -1;
		}
		static CPS_TYPE call_func_by_id(int id, std::string context) {
			if (id < 0) {
				throw CPS::SETTENGS::ERROR(
					"function id < 0", "static T call_func_by_id(int id, std::string context)", "Logic"
				);
			}
			else if (id >= FUNCTIONS.size()) {
				throw CPS::SETTENGS::ERROR(
					"function id > funtions size", "static T call_func_by_id(int id, std::string context)", "Logic"
				);
			}
			else {
				return FUNCTIONS[id].second(context);
			}
		}
		static CPS_TYPE call(std::string name, std::string context) {
			return call_func_by_id(find_func_id(name), context);
		}

		static void reset_vars() {
			VARIABLES.clear();
		}
	};
	static class ENGINE {
	public:
		static class CORRECTOR {
		public:
			CORRECTOR() {}
			~CORRECTOR() {}
			static std::string correcting(std::string stock) {
				std::string strfinally = "";
				if (SETTENGS::FREE_SPACES != SETTENGS::MODE::disabled) {
					int stock_size = stock.size();
					for (int i = 0; i < stock_size; i++) {
						char symbol = stock[i];
						if (symbol == ' ') {
							if (SETTENGS::FREE_SPACES == SETTENGS::MODE::correction) {
								continue;
							}
							else {
								throw CPS::SETTENGS::ERROR(
									"Finded free spaces", "std::string correcting(std::string stock)", "Syntax spaces"
								);
							}
						}
						else {
							strfinally += symbol;
						}
					}
				}
				if (SETTENGS::DOT_OUT_OF_NUMBER != SETTENGS::MODE::disabled) {
					int strfinally_size_DOON = strfinally.size();
					std::string tmp = "";
					for (int i = 0; i < strfinally_size_DOON; i++) {
						char symbol = strfinally[i];
						if (
							(CPS::SETTENGS::CHECKER::isDot(symbol) &&
							(i > 0 && i != strfinally_size_DOON - 1) &&
							(!CPS::SETTENGS::CHECKER::isNumber(strfinally[i - 1]) 
							|| !CPS::SETTENGS::CHECKER::isNumber(strfinally[i + 1]))) 
							|| (CPS::SETTENGS::CHECKER::isDot(symbol) && i == 0) 
							&& !CPS::SETTENGS::CHECKER::isNumber(strfinally[i + 1]) 
							|| (CPS::SETTENGS::CHECKER::isDot(symbol) && i == strfinally_size_DOON - 1) 
							&& !CPS::SETTENGS::CHECKER::isNumber(strfinally[i - 1]))
						{
							if (SETTENGS::DOT_OUT_OF_NUMBER == SETTENGS::MODE::correction) {
								continue;
							}
							else {
								throw CPS::SETTENGS::ERROR(
									"Finded free dots", "std::string correcting(std::string stock)", "Syntax dots"
								);
							}
						}
						else {
							tmp += symbol;
						}
					}
					strfinally = tmp;
				}
				if (SETTENGS::FREE_BRACKETS != SETTENGS::MODE::disabled) {
					int strfinally_size_DOON = strfinally.size();
					int counter = 0;
					std::string tmp = "";
					for (int i = 0; i < strfinally_size_DOON; i++) {
						char symbol = strfinally[i];
						if (symbol == '{' || symbol == '[') {
							if (SETTENGS::FREE_BRACKETS == SETTENGS::MODE::except) {
								throw CPS::SETTENGS::ERROR(
									"Finded another brackets", "std::string correcting(std::string stock)", "Another brackets"
								);
							}
							counter++;
							tmp += '(';
							continue;
						}
						else if (symbol == '}' || symbol == ']') {
							if (SETTENGS::FREE_BRACKETS == SETTENGS::MODE::except) {
								throw CPS::SETTENGS::ERROR(
									"Finded another brackets", "std::string correcting(std::string stock)", "Another brackets"
								);
							}
							counter--;
							tmp += ')';
							continue;
						}
						else if (symbol == '(') {
							counter++;
							tmp += '(';
						}
						else if (symbol == ')') {
							counter--;
							tmp += ')';
						}
						else {
							tmp += symbol;
						}
					}
					if (counter != 0) {
						throw CPS::SETTENGS::ERROR(
							"Finded free bracket", "std::string correcting(std::string stock)", "Free bracket"
						);
					}
					strfinally = tmp;
				}
				if (SETTENGS::REPLACE_ABS != SETTENGS::MODE::disabled) {
					int strfinally_size_DOON = strfinally.size();
					int abs_counter = 0;
					std::vector<int> counter;
					std::string tmp = "";
					for (int i = 0; i < strfinally_size_DOON; i++) {
						char symbol = strfinally[i];
						if (!counter.empty()) {
							if (symbol == '(') {
								counter.back()++;
							}
							else if (symbol == ')') {
								counter.back()--;
							}
						}
						if (symbol == '|') {
							if (SETTENGS::REPLACE_ABS == SETTENGS::MODE::except) {
								throw CPS::SETTENGS::ERROR(
									"Finded abs bracket", "std::string correcting(std::string stock)", "Find abs bracket"
								);
							}
							abs_counter++;
							if (counter.empty() || counter.back() > 0) {
								counter.push_back(0);
								tmp += 'a';
								tmp += 'b';
								tmp += 's';
								tmp += '(';
								continue;
							}
							else if (!counter.empty() && counter.back() == 0) {
								tmp += ')';
								counter.pop_back();
								continue;
							}
						}
						tmp += symbol;
					}
					strfinally = tmp;
				}
				return strfinally.empty() ? stock : strfinally;
			}
		};
		static class PARSER {
		public:
			PARSER() {}
			~PARSER() {}
			static std::vector<std::string> parse_string_to_elements(std::string input) {
				std::vector<std::string> tmp;
				std::string node = "";
				CPS::SETTENGS::RULES::TYPES last_type = CPS::SETTENGS::RULES::get_type(input[0]);
				int str_size = input.size();
				for (int i = 0; i <= str_size; i++) {
					CPS::SETTENGS::RULES::TYPES tmp_type = CPS::SETTENGS::RULES::get_type(input[i]);
					if (
						last_type != tmp_type 
						|| last_type == CPS::SETTENGS::RULES::TYPES::close_b 
						|| last_type == CPS::SETTENGS::RULES::TYPES::open_b)
					{
						if (node == "-") {
							if (!tmp.empty()) {
								CPS::SETTENGS::RULES::TYPES stack_elem_type = CPS::SETTENGS::RULES::get_type(tmp.back()[0]);
								if (stack_elem_type != CPS::SETTENGS::RULES::TYPES::number 
									&& stack_elem_type != CPS::SETTENGS::RULES::TYPES::factorial
									&& stack_elem_type != CPS::SETTENGS::RULES::TYPES::close_b
									) 
								{
									tmp.push_back("0");
								}
							}
							else {
								tmp.push_back("0");
							}
						}
						if (tmp_type == CPS::SETTENGS::RULES::TYPES::dot) {
							tmp_type = CPS::SETTENGS::RULES::TYPES::number;
							last_type = tmp_type;
							node += input[i];
							continue;
						}
						node.empty() ? void() : tmp.push_back(node);
						node = "";
 						if (tmp_type == CPS::SETTENGS::RULES::TYPES::close_b 
							|| tmp_type == CPS::SETTENGS::RULES::TYPES::open_b
							|| tmp_type == CPS::SETTENGS::RULES::TYPES::sign
							|| tmp_type == CPS::SETTENGS::RULES::TYPES::factorial
							) 
						{
							tmp_type = CPS::SETTENGS::RULES::TYPES::none;
						}
					}
					last_type = tmp_type;
					node += input[i];
				}
				return tmp;
			}
			static std::vector<std::string> parse_elements_to_polish(std::vector<std::string> input) {
				std::stack<std::string> stack;
				std::vector<std::string> output;
				int size = input.size();
				std::string element = "";
				for (int i = 0; i < size; i++) {
					element = input[i];
					CPS::SETTENGS::RULES::TYPES element_type = CPS::SETTENGS::RULES::get_type(element[0]);
					if (
						CPS::SETTENGS::CHECKER::isNumber(element[0])
						|| (element.size() == 1 
							&& element_type == CPS::SETTENGS::RULES::TYPES::letter)) {
						output.push_back(element);
					}
					else if (element.size() >= 3 || element_type == CPS::SETTENGS::RULES::TYPES::comma) {
						stack.push(element);
					}
					else if (element_type == CPS::SETTENGS::RULES::TYPES::open_b) {
						stack.push(element);
					}
					else if (element_type == CPS::SETTENGS::RULES::TYPES::close_b) {
						while (CPS::SETTENGS::RULES::get_type(stack.top()[0]) != CPS::SETTENGS::RULES::TYPES::open_b) {
							output.push_back(stack.top());
							stack.pop();
						}
						stack.pop();
					}
					else if (element_type == CPS::SETTENGS::RULES::TYPES::sign || element == "!") {
						while (!stack.empty()) {
							std::string stack_top = stack.top();
							if (stack_top.size() >= 3 && CPS::SETTENGS::RULES::get_type(stack_top[0]) == CPS::SETTENGS::RULES::TYPES::letter
								|| CPS::SETTENGS::RULES::get_type(stack_top[0]) == CPS::SETTENGS::RULES::TYPES::comma
								|| CPS::SETTENGS::RULES::get_priority(stack_top[0]) >= CPS::SETTENGS::RULES::get_priority(element[0])
								) 
							{
								output.push_back(stack_top);
								stack.pop();
							}
							else {
								break;
							}
						}
						stack.push(element);
					}
					else {
						throw CPS::SETTENGS::ERROR(
							"Unknown type error", "std::vector<std::string> parse_elements_to_polish(std::vector<std::string> input)", "Program core error"
						);
					}
				}
				while (!stack.empty()) {
					output.push_back(stack.top());
					stack.pop();
				}
				return output;
			}
		};
		static class CALCULATOR {
		public:
			CALCULATOR() {}
			~CALCULATOR() {}
			static CPS_TYPE calculate(std::vector<std::string> input) {
				// start tree
				Node tree(input[input.size() - 1]);
				for (int i = input.size() - 2; i >= 0; i--) {
					tree.insert(input[i]);
				}
				// end tree
				replace_varialbles(input);
				std::stack<std::string> stack;
				std::string function_row;
				int count_commas = 0;
				CPS_TYPE output;
				for (const auto elem : input) {
					CPS::SETTENGS::RULES::TYPES elem_type = CPS::SETTENGS::RULES::get_type(elem[0]);
					if (CPS::SETTENGS::RULES::get_type(elem[0]) == CPS::SETTENGS::RULES::TYPES::number) {
						stack.push(elem);
					}
					else if (elem_type == CPS::SETTENGS::RULES::TYPES::comma) {
						count_commas++;
					}
					else if (elem_type == CPS::SETTENGS::RULES::TYPES::sign
 						|| elem_type == CPS::SETTENGS::RULES::TYPES::factorial) {
						char sign = elem[0];
						CPS_TYPE value;
						value = std::stof(stack.top());
						stack.pop();
						if (sign == '+') {
							value += std::stof(stack.top());
							stack.pop();
						}
						else if (sign == '-') {
							value = std::stof(stack.top()) - value;
							stack.pop();
						}
						else if (sign == '*') {
							value *= std::stof(stack.top());
							stack.pop();
						}
						else if (sign == '/') {
							value = std::stof(stack.top()) / value;
							stack.pop();
						}
						else if (sign == '^') {
							value = pow(std::stof(stack.top()), value);
							stack.pop();
						}
						else {
							value = factorial(value);
						}
						stack.push(std::to_string(value));
					}
					else if (elem.size() >= 3 && elem_type == CPS::SETTENGS::RULES::TYPES::letter) {
						std::string context = "";
						for (int g = 0; g <= count_commas; g++) {
							context += stack.top();
							if (g < count_commas) {
								context += ",";
							}
							stack.pop();
						}
						stack.push(std::to_string(STORAGE::call(elem, context)));
						count_commas = 0;
					}
				}
				output = std::stof(stack.top());
				stack.pop();
				if (!stack.empty()) {
					throw CPS::SETTENGS::ERROR(
						"Arithmetic stack is not empty", "T calculate(std::vector<std::string> input)", "Math core error"
					);
				}
				return output;
			}
			static void replace_varialbles(std::vector<std::string>& input) {
				for (auto& elem : input) {
					char letter = elem[0];
					if (elem.size() == 1 && CPS::SETTENGS::RULES::get_type(letter) == CPS::SETTENGS::RULES::TYPES::letter) {
						elem = std::to_string(STORAGE::find_var(letter).value);
					}
				}
			}
			static CPS_TYPE factorial(double x) {
				return std::tgammaf(x + 1);
			}
		};
		ENGINE() {}
		~ENGINE() {}
	};
	static class SETTENGS {
	public:
		static class RULES {
		public:
			enum TYPES {
				none,
				letter,
				number,
				open_b,
				close_b,
				dot,
				sign,
				comma,
				factorial
			};
			RULES() {}
			~RULES() {}
			static TYPES get_type(char s) {
				TYPES lt = TYPES::none;
				if (CHECKER::isLetter(s)) { lt = TYPES::letter; }
				else if (CHECKER::isNumber(s)) { lt = TYPES::number; }
				else if (CHECKER::isDot(s)) { lt = TYPES::dot; }
				else if (CHECKER::isActionSign(s)) { lt = TYPES::sign; }
				else if (CHECKER::isComma(s)) { lt = TYPES::comma; }
				else if (CHECKER::isFactorial(s)) { lt = TYPES::factorial; }
				else if (s == '(') { lt = TYPES::open_b; }
				else { lt = TYPES::close_b; }
				return lt;
			}
			static PRIORITY get_priority(char c) {
				return 
					c == '!' ? PRIORITY::very_high :
					c == '^' ? PRIORITY::high :
					c == '*' || c == '/' ? PRIORITY::medium :
					c == '+' || c == '-' ? PRIORITY::low : PRIORITY::none;
			}
		};
		static class ERROR {
		public:
			static std::string ERROR_NAME;
			static std::string ERROR_CALL_BLOCK;
			static std::string ERROR_CALL_LINE;
			static std::string ERROR_TYPE;
		public:
			ERROR() {
				ERROR_NAME = "";
				ERROR_CALL_BLOCK = "";
			}
			ERROR(std::string _name, std::string _call_block, std::string _type) {
				ERROR_NAME = _name;
				ERROR_CALL_BLOCK = _call_block;
				ERROR_TYPE = _type;
			}
			ERROR(std::string _name, std::string _call_block, std::string _line, std::string _type) {
				ERROR_NAME = _name;
				ERROR_CALL_BLOCK = _call_block;
				ERROR_CALL_LINE = _line;
				ERROR_TYPE = _type;
			}
			~ERROR() {}
			std::string get_last_error_name() { return ERROR_NAME; }
			std::string get_last_error_block() { return ERROR_CALL_BLOCK; }
			std::string get_last_error_line() { return ERROR_CALL_LINE; }
			std::string  get_last_error_type() { return ERROR_TYPE; }
		};
		static class CHECKER {
		public:
			CHECKER() {}
			~CHECKER() {}
			static bool isNumber(char s) {
				int alphabet_size = NUMBER_ALPHABET.size();
				for (int i = 0; i < alphabet_size; i++) { if (s == NUMBER_ALPHABET[i]) { return true; } }
				return false;
			}
			static bool isActionSign(char s) {
				int alphabet_size = ACTION_SIGN.size();
				for (int i = 0; i < alphabet_size; i++) { if (s == ACTION_SIGN[i]) { return true; } }
				return false;
			}
			static bool isLetter(char s) {
				int alphabet_size = LETTERS_ALPHABET.size();
				for (int i = 0; i < alphabet_size; i++) { if (s == LETTERS_ALPHABET[i]) { return true; } }
				return false;
			}
			static bool isDot(char s) { return s == '.' ? true : false; }
			static bool isComma(char s) { return s == ',' ? true : false; }
			static bool isFactorial(char s) { return s == '!' ? true : false; }
		};
		enum MODE { disabled, correction, except };
		enum MODE_EXCEPT { off, error };
		static MODE FREE_SPACES;
		static MODE FREE_BRACKETS;
		static MODE REPEATED_ACTION_SIGN;
		static MODE DOT_OUT_OF_NUMBER;
		static MODE REPLACE_ABS;
		static bool STEPS_SOLVING;
		SETTENGS() { FREE_SPACES = disabled; }
		SETTENGS(const SETTENGS& settings) {}
		~SETTENGS() {}
	private:
		bool get_steps_solving() { return STEPS_SOLVING; }
		void set_steps_solving(bool variant) { STEPS_SOLVING = variant; }
	};

	static CPS_TYPE solve(std::string expression) {
		return CPS::ENGINE::CALCULATOR::calculate(CPS::ENGINE::PARSER::parse_elements_to_polish(CPS::ENGINE::PARSER::parse_string_to_elements(CPS::ENGINE::CORRECTOR::correcting(expression))));
	}

	static CPS_TYPE force_solve(std::string expression) {
		return CPS::ENGINE::CALCULATOR::calculate(CPS::ENGINE::PARSER::parse_elements_to_polish(CPS::ENGINE::PARSER::parse_string_to_elements(expression)));
	}

	static CPS_TYPE force_solve(std::vector<std::string> polish_expression) {
		return CPS::ENGINE::CALCULATOR::calculate(polish_expression);
	}

	static std::vector<std::string> convert_polish(std::string expression) {
		return CPS::ENGINE::PARSER::parse_elements_to_polish(CPS::ENGINE::PARSER::parse_string_to_elements(expression));
	}

	static std::vector<std::string> slice(std::string expression) {
		return CPS::ENGINE::PARSER::parse_string_to_elements(expression);
	}

private:
	CPS() {}
	~CPS() {}
};
CPS::SETTENGS::MODE CPS::SETTENGS::FREE_SPACES;
CPS::SETTENGS::MODE CPS::SETTENGS::FREE_BRACKETS;
CPS::SETTENGS::MODE CPS::SETTENGS::REPEATED_ACTION_SIGN;
CPS::SETTENGS::MODE CPS::SETTENGS::DOT_OUT_OF_NUMBER;
CPS::SETTENGS::MODE CPS::SETTENGS::REPLACE_ABS;
std::vector<CPS::VAR> CPS::STORAGE::VARIABLES;
std::vector<std::pair<std::string, FUNC>> CPS::STORAGE::FUNCTIONS;
std::string CPS::SETTENGS::ERROR::ERROR_NAME;
std::string CPS::SETTENGS::ERROR::ERROR_CALL_BLOCK;
std::string CPS::SETTENGS::ERROR::ERROR_CALL_LINE;
std::string CPS::SETTENGS::ERROR::ERROR_TYPE;
#endif  // INCLUDE_ANALIZER_H_
/*
																	   *-----*
											 +-----------+             | CPS |               +-------+
											 | Corrector |			   *-----*               | Rules |
											 +-----------+     		  /   |   \              +-------+
														  \          /    |    \            /
														   +--------+     |     +----------+
														   | Engine |     |     | Settings |
											  +------------+--------+     |     +----------+-----------+
											 /            / 			  |                 \		    \
							   +------------+   +--------+           +---------+             +--------+ +--------+
							   | Calculator |   | Parser |	         | Storage |             | Errors | | Checks |
							   +------------+   +--------+	         +---------+             +--------+ +--------+
*/
