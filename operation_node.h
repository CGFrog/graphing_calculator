#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <cmath>

struct Node {
	enum symbol {
		add, subtract, // Primary
		multiply, divide, // Secondary
		exponent,  // exponential
		log, ln, sin, cos, tan, sec, csc, cot, sqrt, //singular
		val, var, equals //status
	};

	Node(std::string);
	Node() = default;

	//SETTERS

	void set_value(float);
	void set_symb(symbol);
	void set_left(Node*);
	void set_right(Node*);
	void set_function_left(std::string);
	void set_function_right(std::string);
	void set_singular(bool);
	//GETTERS

	float get_value();
	symbol get_symbol();
	Node* get_left();
	Node* get_right();
	std::string get_function_left();
	std::string get_function_right();
	bool get_singular();
	int parse_function_for_primary_operators(std::string);
	bool is_primary(char);
	bool is_secondary(char);
	bool is_singular(std::string);
	bool is_tertiary(char);
	std::string zero_out_front(std::string);
	void create_node(std::string);
	float find_value(std::string, symbol& );
	symbol find_symbol(std::string, bool&);
	std::string remove_parenthesis(std::string func);
	float evaluate_function(float);




protected:

	std::string func_l;
	std::string func_r;
	int index;
	float value = 1;
	symbol symb;
	Node* Left = nullptr;
	Node* Right = nullptr;
	bool singular;
};
