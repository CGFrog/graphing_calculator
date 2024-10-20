#include "function.h"

void function::set_function(std::string func) {
	this->function = func;
}
void function::set_root(Node* root) {
	this->root = root;
}

std::string function::get_function() {
	return function;
}
Node* function::get_root() {
	return root;
}

Node* function::create_root(std::string func) {
	Node* root = new Node(0, Node::equals, func);
	root->create_tree();
	return root;
}