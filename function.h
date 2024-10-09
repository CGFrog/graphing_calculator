#pragma once
#include <string>
#include <cmath>
#include <vector>
#include <map>

class function {

public:
	
	std::map<std::string, int> operations;
	function(std::string user_function);
	
	//GETTERS
	std::string get_user_function();
	std::vector<std::string> get_tokenized_function();
	std::vector<int> get_solutions();
	float get_previous_calculation();
	float get_total_calculation();
	float get_current_calculation();

	//SETTERS
	void set_user_function(std::string user_function);
	void set_tolkenized_function(std::vector<std::string>tolkenized_function);
	float set_previous_calculation();
	float set_total_calculation();
	float set_current_calculation();
	
	//TOLKENIZE
	std::vector<std::string> tolkenize(std::string func);
	std::vector <int> parenthesis_parse();

	//OPERATIONS
	void initialize_operations(std::map<std::string, int>& operations);
	float conduct_operation(int hash_index);
	
private:
	std::string user_function;
	std::vector<std::string> tokenized_function;
	std::vector<int> solutions;
	
	float previous_calculation;
	float total_calculation;
	float current_calculation;

	// All opening parenthesis will be even index '(' = 0,2,4,6,...,n-1 and all clossing parenthesis will be odd index ')' = 1,3,5,...,n
	// Storing their index number we can find that the parenthesis with the smallest distances to each other will be done first.
	std::vector <int> parenthesis_index; 

	};