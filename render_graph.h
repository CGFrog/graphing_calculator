#pragma once
#include <SFML/Graphics.hpp>
#include "operation_node.h"

struct Graph {

	Graph(const std::string&);
	const unsigned short WINDOW_SIZE_X = 800;
	const unsigned short WINDOW_SIZE_Y = 600;
	const float GRID_SPACING = 10.0f;
	const float ZOOM_FACTOR = .05f;
	const float POINT_SIZE = 1.f;
	void plotted_points(Node*);

	void display_grid(sf::RenderWindow&, sf::View&);
	void render_graph();
	void set_tree_outputs(std::vector <float>);
	void zoom_zoom(sf::RenderWindow&, sf::View&);
	void display_points(sf::RenderWindow&);
private:
	std::vector <float> tree_outputs; // With current use case, should be static array however for scalability using vector.
};