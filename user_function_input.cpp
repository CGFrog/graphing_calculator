#include "operation_node.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

int main() {
	std::string function;
	function = "e^x";
	Node* Tree = new Node(function);
	//Use smart pointers or write a function to delete all pointers as this will only delete the root.	delete Tree;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graphing Calculator - Ian Cooper");

    std::vector <sf::CircleShape>;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for (int x = -500; x < 500; x++) {
            sf::CircleShape shape(5.f,5);
            shape.setOrigin(-400, -300);
            shape.setFillColor(sf::Color::Green);
            shape.setPosition(x*.2, -Tree->evaluate_function(x)*.2);
            window.draw(shape);
        }
        window.display();
    }

	return 0;
}