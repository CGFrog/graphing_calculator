#include "operation_node.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "render_graph.h"


int main() {
    std::cout << "Enter a function." << std::endl;
	std::string function;
    std::getline(std::cin, function);

    Graph Graph(function);

    return 0;
}