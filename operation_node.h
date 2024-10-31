#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <memory>
#include <limits>
#include <unordered_map>

// Used a lot of information from this series https://www.youtube.com/watch?v=KiB0vRi2wlc
// Design idea from https://www.partow.net/programming/exprtk/index.html#design
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
	void set_left(std::unique_ptr<Node>);
	void set_right(std::unique_ptr<Node>);
	void set_function(const std::string&);
	void set_singular(bool);
	//GETTERS

	float get_value() const;
	symbol get_symbol() const;
	Node* get_left() const;
	Node* get_right() const;
	std::string get_function() const;
	bool get_singular() const;
	
	int parse_function_for_primary_operators(const std::string&);
	bool is_primary(char);
	bool is_secondary(char);
	bool is_singular(const std::string&);
	bool is_tertiary(char);
	std::string zero_out_front(const std::string&);
	void create_node(std::string);
	float find_value(std::string, symbol& );
	symbol find_symbol(const std::string&, bool&);
	std::string remove_parenthesis(std::string);
	float evaluate_function(float);



protected:
	std::string function;
	float value = 1;
	symbol symb;
	std::unique_ptr<Node> Left = nullptr;
	std::unique_ptr<Node> Right = nullptr;
	bool singular;
};
