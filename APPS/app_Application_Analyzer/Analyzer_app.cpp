// Copyright 2022 Filatov Maxim

#include "../../APPS/app_Application_Analyzer/Analyzer_app.h";
#include "../../LIBS/lib_Arithmetic_Analyzer/tinyexpr.h"
#include <ctime>
CPS_TYPE gaa(std::string str) {
	return 10.0/*std::stof(str)*/;
}

CPS_TYPE _sin(std::string str) {
	return sin(std::stof(str));
}

CPS_TYPE _cos(std::string str) {
	return cos(std::stof(str));
}

CPS_TYPE _sqrt(std::string str) {
	return sqrt(std::stof(str));
}

CPS_TYPE _abs(std::string str) {
	return fabsf(std::stof(str));
}

CPS_TYPE plusall(std::string str) {
	std::vector<float> vec;
	int size = str.size();
	std::string word;
	for (int i = 0; i <= size; i++) {
		if (str[i] == ',') {
			vec.push_back(std::stof(word));
			word.clear();
		}
		else {
			word += str[i];
		}
	}
	vec.push_back(std::stof(word));
	int result = 0;
	for (const auto elem : vec) {
		result += elem;
	}
	return result;
}

void print_vector(std::vector<std::string> vector) {
	std::cout << "\n";
	for (const auto elem : vector) {
		std::cout << elem << " ";
	}
}


void test() {
	CPS::STORAGE::add_variable(CPS::VAR().create('x', 3));
	CPS::STORAGE::add_variable(CPS::VAR().create('y', 0));
	CPS::STORAGE::change_variable(CPS::VAR().create('y', 11));
	CPS::STORAGE::add_func("sin", _sin);
	CPS::STORAGE::add_func("cos", _cos);
	CPS::STORAGE::add_func("sqrt", _sqrt);
	CPS::STORAGE::add_func("plusall", plusall);
	CPS::STORAGE::add_func("abs", _abs);
	//try {
	//	CPS::STORAGE::add_func("gaa", gaa);
	//	//std::cout << CPS::storage.call_func_by_id(1, "");
	//}
	//catch (CPS::SETTENGS::ERROR e) {
	//	//std::cout << "Error name: " << e.get_last_error_name() << "\n" << "Error block: " << e.get_last_error_block() << "\n" << "Error type: " << e.get_last_error_type();
	//}

	//CPS::SETTENGS::FREE_SPACES = CPS::SETTENGS::MODE::correction;
	//CPS::SETTENGS::DOT_OUT_OF_NUMBER = CPS::SETTENGS::MODE::disabled;
	//try {
	//	std::cout << "\n" << CPS::ENGINE::CORRECTOR::correcting("..sin(x+2) +  1.2 -    8.....     - 6     ..");
	//}
	//catch (CPS::SETTENGS::ERROR e) {
	//	std::cout << "Error name: " << e.get_last_error_name() << "\n" << "Error block: " << e.get_last_error_block() << "\n" << "Error type: " << e.get_last_error_type();
	//}
	//CPS::SETTENGS::FREE_SPACES = CPS::SETTENGS::MODE::correction;
	//CPS::SETTENGS::DOT_OUT_OF_NUMBER = CPS::SETTENGS::MODE::correction;
	//try {
	//	std::cout << "\n" << CPS::ENGINE::CORRECTOR::correcting("..sin(x+2) +  1.2 -    8.....     - 6     ..");
	//}
	//catch (CPS::SETTENGS::ERROR e) {
	//	std::cout << "Error name: " << e.get_last_error_name() << "\n" << "Error block: " << e.get_last_error_block() << "\n" << "Error type: " << e.get_last_error_type();
	//}
	//std::cout << "\n";
	CPS::ENGINE::PARSER parser;
	////std::stack s = std::stack<std::string>();//Stack<std::string>(Analyzer_settings::STACK_BUFFER);
	////s = Analyzer_parser::parse_string_to_stack("sqrt(x)-1/2*sin(x^2-2)+((11)-(2!-2!!))");
	//std::vector<std::string> d;
	////d = Analyzer_parser::parse_string_to_polish("sqrt(x)-1/2*sin(x^2-2)");
	//std::vector<std::string> ans;
	////ans = CPS::ENGINE::PARSER::parse_string_to_elements("sqrt(x)-1/2*sin(x^2-2)");
	//std::vector<std::string> result;
	////result = CPS::ENGINE::PARSER::parse_elements_to_polish(ans); // -2
	////print_vector(result);
	std::string example = "(4-9)*(5*2+12)";
	std::cout << "\n\n" << example;
	print_vector(parser.parse_elements_to_polish(parser.parse_string_to_elements(example)));
	std::cout << "\nSolve: " << CPS::solve(example) << "\n";
	//print_vector(parser.parse_elements_to_polish(parser.parse_string_to_elements("1+(-2)")));
	//print_vector(parser.parse_elements_to_polish(parser.parse_string_to_elements("sin(cos(tan(ctan(sqrt(2^7)))))")));
	//print_vector(parser.parse_elements_to_polish(parser.parse_string_to_elements("1+2*3")));
	//print_vector(parser.parse_elements_to_polish(parser.parse_string_to_elements("7*3/10+1*6+3-1")));
	//print_vector(parser.parse_elements_to_polish(parser.parse_string_to_elements("sqrt(1,5)")));
	//print_vector(parser.parse_elements_to_polish(parser.parse_string_to_elements("func((1+2),(3*3),(9-9),((sin(12))!))")));
	//std::cout << "\n" << CPS::STORAGE::call("gaa", "1.12443");
	//print_vector(parser.parse_elements_to_polish(parser.parse_string_to_elements("1+gaa(gaa(1,2,3,4,5))")));
	//std::cout << "\n" << CPS::ENGINE::CALCULATOR::calculate(parser.parse_elements_to_polish(parser.parse_string_to_elements("2/gaa(gaa(1,2,3,4,5))")));
	//unsigned int start_time = clock();
	//std::cout << "\n" << CPS::ENGINE::CALCULATOR::calculate(parser.parse_elements_to_polish(parser.parse_string_to_elements("sin(1)-cos(0)+plusall(1,2,3,4,5)/5*2")));
	//std::cout << "\n" << CPS::ENGINE::CALCULATOR::calculate(parser.parse_elements_to_polish(parser.parse_string_to_elements("(cos(y)*5)!")));
	//std::cout << "\n" << CPS::ENGINE::CALCULATOR::calculate(parser.parse_elements_to_polish(parser.parse_string_to_elements("abs(-10-(-1))")));
	//std::cout << "\n" << std::to_string(CPS::ENGINE::CALCULATOR::calculate(parser.parse_elements_to_polish(parser.parse_string_to_elements("abs(-(3!+sin(6!)!-cos(3!)!!)^3!)")))); //sin(abs(cos(sin(3589/847)^5)))!
	//unsigned int end_time = clock();
	//std::cout << "\n" << end_time - start_time << "ms";
	//
	//
	//CPS::SETTENGS::FREE_SPACES = CPS::SETTENGS::MODE::correction;
	//CPS::SETTENGS::DOT_OUT_OF_NUMBER = CPS::SETTENGS::MODE::correction;
	//CPS::SETTENGS::REPLACE_ABS = CPS::SETTENGS::MODE::correction;
	//CPS::SETTENGS::FREE_BRACKETS = CPS::SETTENGS::MODE::correction;
	//try {
	//	std::cout << "\n" << CPS::ENGINE::CORRECTOR::correcting("..|sin(|x|+2) +  {1.2} -    (|8|).....     - 6|     ..");
	//}
	//catch (CPS::SETTENGS::ERROR e) {
	//	std::cout << "Error name: " << e.get_last_error_name() << "\n" << "Error block: " << e.get_last_error_block() << "\n" << "Error type: " << e.get_last_error_type();
	//}
	//
	////std::string exp = "1+gaa(gaa(1,2,3,4,5))+2/gaa(gaa(1,2,3,4,5))+abs(-(3!+sin(6!)!-cos(3!)!!)^3!)+sin(1)-cos(0)+plusall(1,2,3,4,5)/5*2+(cos(y)*5)!+abs(-10-(-1))";
	///*std::string exp = "cos(sin(cos(1*2/3+2^3-sin(cos(6^2+5!*20)))))"; 123+5-(4*123/5*(123+123+(1))/123)-2^10
	//const char* exp2 = "cos(sin(cos(1*2/3+2^3-sin(cos(6^2+5!*20)))))";*/
	//std::string exp = "sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(1234567)))))))))))))))))))))))))))))))))))))))))))))))))))";
	////const char* exp2 = "sin(cos(sqrt(2^3^4+6!-sqrt(5640))))";
	//const char* exp2 = "sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(sqrt(1234567)))))))))))))))))))))))))))))))))))))))))))))))))))";
	//std::cout.precision(17);
	//std::cout << "\n ===================== \n";
	//std::vector<std::string> expr = CPS::convert_polish(exp);
	//start_time = clock();
	//std::cout << CPS::solve(exp);
	//for (int i = 0; i < 10000; i++) {
	//	//CPS::solve(exp);
	//}
	//end_time = clock();
	//unsigned int dif = end_time - start_time;
	//std::cout << "\n" << end_time - start_time << "ms | solve";
	//start_time = clock();
	//std::cout << "\n";
	//std::cout << CPS::force_solve(exp);
	//for (int i = 0; i < 10000; i++) {
	//	//CPS::force_solve(expr);
	//}
	//end_time = clock();
	//unsigned int dif2 = end_time - start_time;
	//std::cout << "\n" << end_time - start_time << "ms | force";
	//std::cout << "\nDifference: " << std::fabsf(dif - dif2) << "ms" << " | " << "solve " << (dif > dif ? "<" : ">") << " force";
	//start_time = clock();
	//std::cout << "\n \n";
	//double x = 3, y = 11;
	//
	//std::cout << te_interp(exp2, 0);
	//for (int i = 0; i < 10000; i++) {
	//	//te_interp(exp2, 0);
	//}
	//end_time = clock();
	//std::cout << "\n" << end_time - start_time << "ms | tinyexpr" << " answer: " << te_interp(exp2, 0);
	////system("pause");
}

#include <string>

void f(std::string str, int i, std::vector<char> vars) {
	for (auto &elem : vars) {
		if (elem == str[i]) {
			return;
		}
	}
	std::cout << "¬ведите значение " << "\"" << str[i] << "\": ";
	CPS_TYPE var = 0;
	std::cin >> var;
	vars.push_back(str[i]);
	CPS::STORAGE::add_variable(CPS::VAR().create(str[i], var));
}

int main() {
	test();
	//CPS::STORAGE::add_func("sin", _sin);
	//CPS::STORAGE::add_func("cos", _cos);
	//CPS::STORAGE::add_func("sqrt", _sqrt);
	//CPS::STORAGE::add_func("plusall", plusall);
	//CPS::STORAGE::add_func("abs", _abs);
	//CPS::SETTENGS::FREE_SPACES = CPS::SETTENGS::MODE::correction;
	//CPS::SETTENGS::DOT_OUT_OF_NUMBER = CPS::SETTENGS::MODE::correction;
	//CPS::SETTENGS::REPLACE_ABS = CPS::SETTENGS::MODE::correction;
	//CPS::SETTENGS::FREE_BRACKETS = CPS::SETTENGS::MODE::correction;
	//setlocale(LC_ALL, "Russian");
	//std::vector<char> vars;
	//std::string str;
	//std::cout << "¬ведите выражение: ";
	//getline(std::cin, str, '\n');
	//int size = str.size();
	//if (CPS::SETTENGS::CHECKER::isLetter(str.front()) && !CPS::SETTENGS::CHECKER::isLetter(str[1])) {
	//	f(str, 0, vars);
	//}
	//for (int i = 1; i < size - 1; i++) {
	//	if (CPS::SETTENGS::CHECKER::isLetter(str[i]) && !CPS::SETTENGS::CHECKER::isLetter(str[i + 1]) && !CPS::SETTENGS::CHECKER::isLetter(str[i - 1])) {
	//		f(str, i, vars);
	//	}
	//	/*else if (CPS::SETTENGS::CHECKER::isLetter(str[i]) && i == 0) {
	//		f(str, i, vars);
	//	}*/
	//}
	//if (CPS::SETTENGS::CHECKER::isLetter(str.back())) {
	//	f(str, size-1, vars);
	//}
	//std::cout << "ќтвет: " << CPS::solve(str) << "\n";
	//system("pause");
	return 0;
}
