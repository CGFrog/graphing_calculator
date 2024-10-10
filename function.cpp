#include "function.h"

void function::initialize_operations(std::map<std::string, int>& operations) {
	operations["+"] = 0;
	operations["-"] = 1;
	operations["*"] = 2;
	operations["/"] = 3;
	operations["("] = 4;
	operations[")"] = 5;
	operations["x"] = 6;
	operations["^"] = 7;
	operations["$"] = 8;
	operations["ln"] = 9;
	operations["sin"] = 10;
	operations["cos"] = 11;
	operations["tan"] = 12;
	operations["sec"] = 13;
	operations["csc"] = 14;
	operations["cot"] = 15;
	operations["!"] = 16;
	operations["sqrt"] = 17;
	operations["log"] = 18;
	operations["pi"] = 19;
	operations["e"] = 20;
}

float function::conduct_operation(int hash_index) {
	switch (hash_index)
	{
	case 0:
		//Addition
		break;
	case 1:
		//Subtraction
		break;
	case 2:
		//Multiplication
		break;
	case 3:
		//Division
		break;
	case 4:
		//Open Parenthesis
		break;
	case 5:
		//Closed Parenthesis
		break;
	case 6:
		//Variable
		break;
	case 7:
		//Exponential
		break;
	case 8:
		//Use last computation
		break;
	case 9:
		//Natural Log
		break;
	case 10:
		//sin
		break;
	case 11:
		//cos
		break;
	case 12:
		//tan
		break;
	case 13:
		//sec
		break;
	case 14:
		//csc
		break;
	case 15:
		//cot
		break;
	case 16:
		//Factorial
		break;
	case 17:
		//Square root
		break;
	case 18:
		//Log base 10
		break;
	case 19:
		//pi
		break;
	case 20:
		//e
		break;
	}

}	

float function::traverse_operation_tree(Node* root) {
	if (root == nullptr) {
		return 0;
	}
	return 0;
}
