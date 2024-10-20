#pragma once
#include <string>
#include <cmath>
#include "operation_node.h"


class function {

public:
	//SETTERS
	void set_function(std::string func);
	void set_root(Node* root);
	
	//GETTERS
	std::string get_function();
	Node* get_root();

	Node* create_root(std::string func);

private:
	std::string function;
	Node* root = nullptr;

};

/*
TEST CASES : (BE CAREFUL FOR DIVISION BY 0)
f(x) = x
f(x) = x+ln(x)
f(x) = x^2 + x + 1
f(x) = x/((x+2)*(x-2))
f(x) = sin(x)/cos(x)
f(x) = sin(x^2*4*ln(3x))
f(x) = tan(x^2+6*(ln(x)+7))/(pi*(x^3-5)*(sec(x)))


ABSTRACT SEARCH TREES

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
		^    x
	  /  \
	 x    2 

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
		 x  2 6   /
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


Regular Expression regex
*/


/*
   x^2 + 3*x - 4
Parse for addition or subtraction beyond parenthesis from left to right

parse left to find operator of next highest precedence, in this case ^
	if ^ parse expression on left and right and assign to left node and right node respectively

parse right to find operator of next highest precedence, in this case '-'
	parse left to find the immediate operator to left in this case it is *
		parse left to find immediate operand on left in this case it is 3
		parse right to find immediate operand on right in this case it is x
	parse right to find the immediate operand on the right in this case it is 4


	 +
   /   \
  ^     -
 / \   / \
x  2  *   4
	 / \
	3   x

This will be recursive, we start with our parse function, we parse function until we find our highest operator
call the parse function again, this time limited to the left half of the string and assigning it to the left pointer of our root
Once the left side of our function is fully parsed the right side is evaluated the same way, breaking the function into smaller pieces
If there is no more string to return, we set the pointer of the lowest node to NUL

PRIORITY
 + -
 * /
 () ^ log trig


x + 2 + 5 - 4

	+
   / \
  x   +
     / \
	2   -
	   /  \
 	  5    4


*/