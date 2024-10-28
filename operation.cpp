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
void Node::set_function_left(std::string func_l) {
	this->func_l = func_l;
}
void Node::set_function_right(std::string func_r) {
	this->func_r = func_r;
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
std::string Node::get_function_left() const{
	return func_l;
}
std::string Node::get_function_right() const{
	return func_r;
}
bool Node::get_singular() const{
	return singular;
}

bool Node::is_primary(char index) {
	if (index == '+' || index == '-') {
		return true;
	}
	return false;
}

bool Node::is_secondary(char index) {
	if (index == '*' || index == '/') {
		return true;
	}
	return false;
}

bool Node::is_tertiary(char index) {
	if (index == '^') {
		return true;
	}
	return false;
}

bool Node::is_singular(const std::string& index) {
	//Ensure the passed string is 4 characters
	std::string bi_string = index.substr(0, 2);
	std::string tri_string = index.substr(0, 3);	
	//Later if time make an array with these strings and adjust the length of the index to match the length
	//of the comparing string. Im too strapped for time to do this now.
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
	std::string new_func;
	//If function starts with negative number, adds a 0 out front to accomodate.
	if (func[0] == '-') {
		new_func = "0" + func;
	}
	return new_func;
}

Node::symbol Node::find_symbol(std::string symb_str, bool& singular) {
	//Change this to a map if time permits.
	std::string symb_str_2 = symb_str.substr(0, 2);
	std::string symb_str_3 = symb_str.substr(0, 3);
	std::string symb_str_4 = symb_str.substr(0, 4);
	if (symb_str[0] == '+')
		return add;
	if (symb_str[0] == '-')
		return subtract;
	if (symb_str[0] == '*')
		return multiply;
	if (symb_str[0] == '/')
		return divide;
	if (symb_str[0] == '^')
		return exponent;
	singular = true;
	if (symb_str_3 == "log")
		return log;
	if (symb_str_2 == "ln")
		return ln;
	if (symb_str_3 == "sin") {
		return sin;
	}
	if (symb_str_3 == "cos")
		return cos;
	if (symb_str_3 == "tan")
		return tan;
	if (symb_str_3 == "sec")
		return sec;
	if (symb_str_3 == "csc")
		return csc;
	if (symb_str_3 == "cot")
		return cot;
	if (symb_str_4 == "sqrt")
		return sqrt;
	std::cout << symb_str;
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
	if (func[0] == '(' && func[func.length() - 1] == ')'){
		return func.substr(1, func.length() - 2);
	}
	return func;
}

void Node::create_node(std::string func) {
	if (!func.length()) {
		return;
	}
	func = remove_parenthesis(func);
	int operator_index = parse_function_for_primary_operators(func);
	if (operator_index == -1) {
		symbol value_symb;
		set_value(find_value(func, value_symb));
		set_symb(value_symb);
		return;
	}
	//Greater than 0 Indicates a function is still parsable.
	std::string func_l = func.substr(0, operator_index);
	std::string func_r = func.substr(operator_index+1, func.length() - 1);
	//Must send in exact substr
	bool is_singular = false;
	Node::symbol operator_symbol = find_symbol(func.substr(operator_index, func.length()-1), is_singular);
	this->set_singular(is_singular);
	this->set_symb(operator_symbol);
	this->set_function_left(func_l); // These might be redundant and useless but keep them for now in case, delete when working
	this->set_function_right(func_r);
	this->set_left(std::make_unique <Node>(func_l));
	this->set_right(std::make_unique <Node>(func_r));
}

int Node::parse_function_for_primary_operators(const std::string& func) {
	int open_par = 0;
	int closed_par = 0;
	int first_secondary = -2;
	int first_tertiary = -2;
	int first_singular = -2;
	for (int i = 0; i < func.length(); i++) {
		if ((func[i] > '0' && func[i] < '9') || func[i] == 'x' || func[i] == 'e' || func[i] == '.') {
			continue;
		}
		else if (func[i] == '(') {
			closed_par++;
		}
		else if (func[i] == ')') {
			open_par++;
		}
		else if (closed_par != open_par) {
			continue; // Skips over values inside of parenthesis
		}
		else if (is_primary(func[i])) {
			return i;
		}
		else if (is_secondary(func[i]) && first_secondary == -2) {
			first_secondary = i;
		}
		else if (is_tertiary(func[i]) && first_tertiary == -2) {
			first_tertiary = i;
		}
		else if (is_singular(func.substr(i,4)) && first_singular == -2) {
			first_singular = i;
			//We will need to skip the following letters if it turns out it is a singular function
		}
	}
	if (first_secondary != -2) {
		return first_secondary;
	}
	else if (first_tertiary != -2) {
		return first_tertiary;
	}
	else if (first_singular != -2) {
		return first_singular;
	}
	return -1;
}

float match_operators(float num_l,float num_r, Node::symbol symb) {
	switch (symb){
		case Node::add:
			return num_l + num_r;
		case Node::subtract:
			return num_l - num_r;
		case Node::multiply:
			return num_l* num_r;
		case Node::divide:
			//Lets find a way to just ignore attempts when we are dividing by zero entirely
			if (num_r == 0)
				num_r = .0000000001;
			return  num_l / num_r;
		case Node::exponent:
			return pow(num_l, num_r);
		case Node::log:
			return log10(num_r);
		case Node::ln:
			return log(num_r);
		case Node::sin:
			return sin(num_r);
		case Node::cos:
			return cos(num_r);
		case Node::tan:
			return tan(num_r);
		case Node::sec:
			return 1/cos(num_r);
		case Node::csc:
			return 1/sin(num_r);
		case Node::cot:
			return 1/tan(num_r);
		case Node::sqrt:
			return sqrt(num_r);
	}
	return 1;
}

float Node::evaluate_function(float x) {
	if (get_symbol() == val) {
		return get_value();
	}
	if (get_symbol() == var) {
		return x;
	}
	return match_operators(get_left()->evaluate_function(x), get_right()->evaluate_function(x), get_symbol());
}