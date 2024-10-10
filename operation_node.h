#pragma once

struct Node {

protected:
	bool is_value;
	Node* Left;
	Node* Right;
	Node();
};

struct value : public Node {
	float data;
	value();
};

struct operand : public Node {
	int operand_hash;
	operand();
};