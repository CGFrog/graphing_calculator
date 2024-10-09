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
	void set_tokenized_function(std::vector<std::string>tolkenized_function);
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

	/*
	TEST CASES : (BE CAREFUL FOR DIVISION BY 0)
	f(x) = x
	f(x) = x+ln(x)
	f(x) = x^2 + x + 1
	f(x) = x/((x+2)*(x-2))
	f(x) = sin(x)/cos(x)
	f(x) = sin(x^2*4*ln(3x))	
	f(x) = tan(x^2+6*(ln(x)+7))/(pi*(x^3-5)*(sec(x)))
	*/

	/*
	CASE 1: f(x) = x

		  =
		/  \
	f(x)	x
	
	CASE 2: f(x) = x+ln(x)

		=
	   / \
	f(x)  + 
		 / \
		x  ln
			|
			x
	
	CASE 3:	f(x) = x^2 + x + 1
	
		 =
		/  \
	f(x)	+
		   / \
		 1    +
			 /  \
			x^2  x
	
	CASE 4: f(x) = x/((x+2)*(x-2))

		=
	   / \
	f(x)   /
		 /  \
		x    *
			/ \		
		   +   -
		   /\  /\
		  x 2  x 2



	CASE 4: f(x) = sin(x)/cos(x)
	
		=
	  /   \
	f(x)   /
		  / \
	    sin  cos
		 |    |
		 x    x

	CASE 5: f(x) = sin(x^2*4*ln(3x))	
		
		=
	 /     \
	f(x)   sin
			|
			*
		   / \
		 ln   *
		 |   / \
		 *  4   ^
		/ \    / \
		3 x   x   2
		 



	CASE 6: f(x) = tan(x^2+6*(ln(x)+7))/(pi*(x^3-5)*(sec(x)))

			=
		/       \
	  f(x)      tan
				 |
				 +
				/ \
			   ^   *
			  / \ / \
			 x  2 6  /
			        /    \
				   + 
				 /  \	      *
				            /    \
				ln    7    *     sec
				 |        / \     |
				 x      pi   -    x
						   /  \
						  ^    5
						 / \
						x	3



	*/

	};