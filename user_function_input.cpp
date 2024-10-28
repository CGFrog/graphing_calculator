#include "operation_node.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

int main() {
    std::cout << "Enter a polynomial." << std::endl;
	std::string function;
    std::getline(std::cin, function);
	Node* Tree = new Node(function);
    const int window_size_x = 800;
    const int window_size_y = 600;
    sf::RenderWindow window(sf::VideoMode(window_size_x, window_size_y), "Graphing Calculator - Ian Cooper");
    sf::View view = window.getDefaultView();
    int start_x = -window_size_x/2;
    float zoomFactor = 1.5f;  // Adjust zoom level to your needs
    view.zoom(zoomFactor);
    window.setView(view);
    std::vector <float> tree_outputs;
    for (int i = start_x; i < window_size_x / 2; i++) {
        tree_outputs.push_back( - Tree->evaluate_function(i));
    }

    sf::Font font;
    if (!font.loadFromFile("LEMONMILK-Regular.otf")) {
        // Handle error
        return -1;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.delta > 0)
                    view.zoom(0.9f);
                else if (event.mouseWheelScroll.delta < 0)
                    view.zoom(1.1f);
            }
            window.setView(view);
        }

        window.clear();
        window.setView(view);

        for (int x = 0; x < tree_outputs.size(); x++)
        {
            sf::CircleShape shape(2.f, 5);
            shape.setOrigin(-400, -300);
            shape.setFillColor(sf::Color::Green);
            shape.setPosition(x-window_size_x/2, tree_outputs[x]);
            window.draw(shape);

            sf::Text label;
            label.setFont(font);
            label.setCharacterSize(12*zoomFactor);
            label.setFillColor(sf::Color::White);
            label.setOrigin(-400, -300);

            std::string coordinates = "(" + std::to_string(x-window_size_x/2) + ", " + std::to_string(static_cast<int>(tree_outputs[x])) + ")";
            label.setString(coordinates);
            label.setPosition(x - window_size_x / 2 + 5, tree_outputs[x] - 10);
            window.draw(label);
        }

        window.display();
    }
    delete Tree; //All child nodes are unique ptrs and are deleted automatically.
    return 0;
}