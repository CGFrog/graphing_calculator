#include "render_graph.h"

Graph::Graph(const std::string& function) {
    Node* Tree = new Node(function);
    plotted_points(Tree);
    render_graph();

    delete Tree;
    std::cout << "Program Shutdown. All memory freed.\n";
}

void Graph::plotted_points(Node* Tree) {
    int start_x = -WINDOW_SIZE_X / 2;
    int end_x = WINDOW_SIZE_X / 2;
    std::vector<float> outputs;

    outputs.reserve((end_x - start_x) * 1/INCREMENT_SIZE);

    for (double x = start_x; x < end_x; x += INCREMENT_SIZE) {
        outputs.emplace_back(-Tree->evaluate_function(x)); // Emplace is always preferable to pusb_back as it creates the object in place.
    }
    set_tree_outputs(outputs);
}


void Graph::set_tree_outputs(const std::vector <float>& tree_outputs) {
    this->tree_outputs.reserve(tree_outputs.size());
    this->tree_outputs = tree_outputs;
}

//Used AI for this function.
void Graph::zoom_zoom(sf::RenderWindow& window, sf::View& view) {
    sf::Event event;
    static bool is_dragging = false;
    static sf::Vector2i drag_start_pos;
    static float zoom_level = 1.0f;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
        }
        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.delta > 0 && zoom_level > min_zoom) {
                view.zoom(0.9f);
                zoom_level *= 0.9f;
            }
            else if (event.mouseWheelScroll.delta < 0 && zoom_level < max_zoom) {
                view.zoom(1.1f);
                zoom_level *= 1.1f;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            is_dragging = true;
            drag_start_pos = sf::Mouse::getPosition(window);
        }

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            is_dragging = false;
        }

        if (is_dragging) {
            sf::Vector2i current_pos = sf::Mouse::getPosition(window);
            sf::Vector2f offset(
                (drag_start_pos.x - current_pos.x) * view.getSize().x / window.getSize().x,
                (drag_start_pos.y - current_pos.y) * view.getSize().y / window.getSize().y
            );

            view.move(offset);
            drag_start_pos = current_pos;
        }
        window.setView(view);
    }
}

void Graph::display_points(sf::RenderWindow& window) {
    int midpoint = tree_outputs.size() / 2;

    sf::VertexArray lines(sf::LinesStrip, tree_outputs.size());

    for (int i = 0; i < tree_outputs.size(); i++) {
        float posX = (i - midpoint) + (WINDOW_SIZE_X / 2);
        float posY = 20*tree_outputs[i] + (WINDOW_SIZE_Y / 2);

        lines[i].position = sf::Vector2f(posX, posY);
        lines[i].color = sf::Color::Green;
    }

    window.draw(lines);
}

void Graph::render_graph() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Graphing Calculator - Ian Cooper");
    sf::View view = window.getDefaultView();
    view.zoom(ZOOM_FACTOR); // Set initial zoom level
    window.setView(view);
    while (window.isOpen())
    {
        zoom_zoom(window, view); // Controls viewport movement
        window.clear(sf::Color::Blue); //Sets background to blue
        window.setView(view); // Sets the viewport position
        display_grid(window, view); // Displays the gridlines
        display_points(window); // Plots the function onto the graph
        window.display(); // Renders to screen
    }
}

void Graph::display_grid(sf::RenderWindow& window, sf::View& view) {
    // Draw horizontal grid lines
    for (float y = 0; y < WINDOW_SIZE_Y * GRID_SCALING_FACTOR; y += GRID_SPACING) {
        sf::Vertex horizontal_line[] = {
            sf::Vertex(sf::Vector2f(0, y), sf::Color::Black),
            sf::Vertex(sf::Vector2f(WINDOW_SIZE_X * GRID_SCALING_FACTOR, y), sf::Color::Black)
        };
        window.draw(horizontal_line, 2, sf::Lines);
    }

    // Draw vertical grid lines
    for (float x = 0; x <= WINDOW_SIZE_X * GRID_SCALING_FACTOR; x += GRID_SPACING) {
        sf::Vertex vertical_line[] = {
            sf::Vertex(sf::Vector2f(x, 0), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x, WINDOW_SIZE_Y * GRID_SCALING_FACTOR), sf::Color::Black)
        };
        window.draw(vertical_line, 2, sf::Lines);
    }
    //Draw origin
    sf::CircleShape origin_marker(5);
    origin_marker.setFillColor(sf::Color::Red);
    origin_marker.setPosition((WINDOW_SIZE_X / 2) - origin_marker.getRadius(),(WINDOW_SIZE_Y / 2) - origin_marker.getRadius());
    window.draw(origin_marker);
    // Create axis markings
    float axis_marker_radius = 3.0f;
    sf::CircleShape axis_marker(axis_marker_radius);
    axis_marker.setFillColor(sf::Color::Blue);

    for (float x = GRID_SPACING; x <= WINDOW_SIZE_X / 2; x += GRID_SPACING) {
        axis_marker.setPosition((WINDOW_SIZE_X / 2) + x - axis_marker_radius,(WINDOW_SIZE_Y / 2) - axis_marker_radius);
        window.draw(axis_marker);

        axis_marker.setPosition((WINDOW_SIZE_X / 2) - x - axis_marker_radius,(WINDOW_SIZE_Y / 2) - axis_marker_radius);
        window.draw(axis_marker);
    }

    for (float y = GRID_SPACING; y <= WINDOW_SIZE_Y / 2; y += GRID_SPACING) {
        axis_marker.setPosition((WINDOW_SIZE_X / 2) - axis_marker_radius,(WINDOW_SIZE_Y / 2) + y - axis_marker_radius);
        window.draw(axis_marker);

        axis_marker.setPosition((WINDOW_SIZE_X / 2) - axis_marker_radius,(WINDOW_SIZE_Y / 2) - y - axis_marker_radius);
        window.draw(axis_marker);
    }
}
