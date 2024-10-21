#include "operation_node.h"
#include <iostream>

int main() {
	std::string function;
	function = "x^2*(3+x*4)";
	Node* Tree = new Node(function);
	std::cout << Tree->evaluate_function(2) << std::endl;
	// Use smart pointers or write a function to delete all pointers as this will only delete the root.	delete Tree;
	return 0;
}