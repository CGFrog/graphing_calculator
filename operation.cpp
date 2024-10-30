#include "operation_node.h"

Node::Node(std::string function) {
	create_node(function);
}

//SETTERS
void Node::set_value(float value) {
	this->value = value;
}
void Node::set_symb(symbol symb) {
	this->symb = symb;
}
void Node::set_left(std::unique_ptr<Node> left) {
	this->Left = std::move(left);
}

void Node::set_right(std::unique_ptr<Node> right) {
	this->Right = std::move(right);
}
void Node::set_function(const std::string& function) {
	this->function = function;
}
void Node::set_singular(bool singular) {
	this->singular = singular;
}
//GETTERS

float Node::get_value() const{
	return value;
}
Node::symbol Node::get_symbol() const{
	return symb;
}
Node* Node::get_left() const{
	return Left.get();
}
Node* Node::get_right() const{
	return Right.get();
}
std::string Node::get_function() const{
	return function;
}
bool Node::get_singular() const{
	return singular;
}

bool Node::is_primary(char index) {
	return index == '+' || index == '-';
}

bool Node::is_secondary(char index) {
	return index == '*' || index == '/';
}

bool Node::is_tertiary(char index) {
	return index == '^';
}

bool Node::is_singular(const std::string& index) {
	std::string bi_string = index.substr(0, 2);
	std::string tri_string = index.substr(0, 3);	
	// Could use map here.
	if (index[0] == '!')	{
		return true;
	}
	if (bi_string == "ln") {
		return true;
	}
	if (tri_string == "log" || tri_string == "sin" || tri_string == "tan" || tri_string == "cos") {
		return true;
	}
	if (tri_string == "sec" || tri_string == "csc" || tri_string == "cot") {
		return true;
	}
	if (index == "sqrt") {
		return true;
	}
	return false;
}

std::string Node::zero_out_front(const std::string& func) {
	//If function starts with negative number, adds a 0 out front to accomodate.
	if (func[0] == '-') {
		int parenthesis_insert = parse_function_for_primary_operators(func.substr(1, func.length()-1));
		if (parenthesis_insert == -1) return '0' + func;
		return "(0" + func.substr(0, parenthesis_insert - 1) + ')' + func.substr(parenthesis_insert - 1, func.length() - parenthesis_insert + 1);
	}
	return func;
}

Node::symbol Node::find_symbol(const std::string& symb_str, bool& singular) {
	static const std::unordered_map<std::string, Node::symbol> symbol_map = {
		{"+", add},
		{"-", subtract},
		{"*", multiply},
		{"/", divide},
		{"^", exponent},
		{"log", log},
		{"ln", ln},
		{"sin", sin},
		{"cos", cos},
		{"tan", tan},
		{"sec", sec},
		{"csc", csc},
		{"cot", cot},
		{"sqrt", sqrt}
	};

	if (symbol_map.count(symb_str.substr(0, 1))) {
		return symbol_map.at(symb_str.substr(0, 1));
	}
	singular = true;
	if (symbol_map.count(symb_str.substr(0, 3)))
		return symbol_map.at(symb_str.substr(0, 3));
	if (symbol_map.count(symb_str.substr(0, 2)))
		return symbol_map.at(symb_str.substr(0, 2));
	if (symbol_map.count(symb_str.substr(0, 4)))
		return symbol_map.at(symb_str.substr(0, 4));

	return val;
}

float Node::find_value(std::string func,symbol& value_symb) {
	value_symb = val;
		if (func == "x") {
			value_symb = var;
			return 1;
		}
		if (func == "pi")
			return 3.14159265;
		if (func == "e")
			return 2.71828;
		return stod(func);
}

std::string Node::remove_parenthesis(std::string func) {
	if (func.front() == '(' && func.back() == ')') {
		int balance = 0;
		for (int i = 0; i < func.length() - 1; ++i) {
			if (func[i] == '(') {
				++balance;
			}
			else if (func[i] == ')') {
				--balance;
			}
			if (balance == 0 && i != func.length() - 2) {
				return func;
			}
		}
		if (balance == 1) {
			return func.substr(1, func.length() - 2);
		}
	}
	return func;
}

int find_length(Node::symbol operator_symbol) {
	switch (operator_symbol) {
	case Node::sin:
		return 3;
		break;
	case Node::cos:
		return 3;
		break;
	case Node::tan:
		return 3;
		break;
	case Node::csc:
		return 3;
		break;
	case Node::sec:
		return 3;
		break;
	case Node::log:
		return 3;
		break;
	case Node::ln:
		return 2;
		break;
	case Node::sqrt:
		return 4;
		break;
	}
	return 1;
}

void Node::create_node(std::string func) {
	if (!func.length()) {
		return;
	}
	func = remove_parenthesis(func);
//	std::cout << func << std::endl;
	func = zero_out_front(func);

	int operator_index = parse_function_for_primary_operators(func);
	if (operator_index == -1) {
		symbol value_symb;
		set_value(find_value(func, value_symb));
		set_symb(value_symb);
		return;
	}

	bool is_singular = false;
	Node::symbol operator_symbol = find_symbol(func.substr(operator_index, func.length()-1), is_singular);
	int length = find_length(operator_symbol);
	this->set_singular(is_singular);
	this->set_symb(operator_symbol);
	this->set_function(func);
	std::string func_l = func.substr(0, operator_index);
	std::string func_r = func.substr(operator_index + length, func.length() - 1);
	this->set_left(std::make_unique <Node>(func_l));
	this->set_right(std::make_unique <Node>(func_r));
}

int Node::parse_function_for_primary_operators(const std::string& func) {
	int balance = 0;
	int first_secondary = -1;
	int first_tertiary = -1;
	int first_singular = -1;

	for (int i = 0; i < func.length(); i++) {
		char c = func[i];
		if ((c >= '0' && c <= '9') || c == 'x' || c == 'e' || c == '.') {
			continue;
		}
		if (c == '(') {
			balance++;
			continue;
		}
		if (c == ')') {
			balance--;
			continue;
		}
		if (balance == 0) {
			if (is_primary(c)) {
				return i;
			}
			else if (is_secondary(c) && first_secondary == -1) {
				first_secondary = i;
			}
			else if (is_tertiary(c) && first_tertiary == -1) {
				first_tertiary = i;
			}
			else if (is_singular(func.substr(i, 4)) && first_singular == -1) {
				first_singular = i;
				i += 1;
			}
		}
	}
	if (first_secondary != -1) return first_secondary;
	if (first_tertiary != -1) return first_tertiary;
	if (first_singular != -1) return first_singular;

	return -1; // No operator found
}

float match_operators(float num_l, float num_r, Node::symbol symb) {
	constexpr float NaN = std::numeric_limits<float>::quiet_NaN();
	switch (symb) {
	case Node::add:
		return num_l + num_r;
	case Node::subtract:
		return num_l - num_r;
	case Node::multiply:
		return num_l * num_r;
	case Node::divide:
		return num_r != 0 ? num_l / num_r : NaN;
	case Node::exponent:
		return pow(num_l, num_r);
	case Node::log:
		return num_r > 0 ? log10(num_r) : NaN;
	case Node::ln:
		return num_r > 0 ? log(num_r) : NaN;
	case Node::sin:
		return sin(num_r);
	case Node::cos:
		return cos(num_r);
	case Node::tan:
		return tan(num_r);
	case Node::sec:
		return cos(num_r) != 0 ? 1 / cos(num_r) : NaN;
	case Node::csc:
		return sin(num_r) != 0 ? 1 / sin(num_r) : NaN;
	case Node::cot:
		return tan(num_r) != 0 ? 1 / tan(num_r) : NaN;
	case Node::sqrt:
		return num_r >= 0 ? sqrt(num_r) : NaN;
	default:
		return NaN;
	}
}


float Node::evaluate_function(float x) {
	if (get_symbol() == val) {
		return get_value();
	}
	if (get_symbol() == var) {
		return x;
	}
	if (get_singular())
		return match_operators(0, get_right()->evaluate_function(x), get_symbol());
	return match_operators(get_left()->evaluate_function(x), get_right()->evaluate_function(x), get_symbol());
}