#include "render_graph.h"

Graph::Graph(const std::string& function) {
    Node* Tree = new Node(function);
    plotted_points(Tree);
    render_graph();
}

void Graph::plotted_points(Node* Tree) {
    int start_x = -WINDOW_SIZE_X / 2;
    std::vector <float> outputs;
    outputs.reserve(WINDOW_SIZE_X);

    for (int i = start_x; i < WINDOW_SIZE_X / 2; i++) {
        outputs.emplace_back(-Tree->evaluate_function(i));
    }
    set_tree_outputs(outputs);
}

void Graph::set_tree_outputs(std::vector <float> tree_outputs) {
    this->tree_outputs.reserve(tree_outputs.size());
    this->tree_outputs = tree_outputs;
}
void Graph::zoom_zoom(sf::RenderWindow& window, sf::View& view) {
    sf::Event event;
    static bool is_dragging = false;
    static sf::Vector2i drag_start_pos;
    static float zoom_level = 1.0f;
    const float min_zoom = 0.5f;
    const float max_zoom = 2.0f;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

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
    for (int i = 0; i < tree_outputs.size(); i++) {
        sf::CircleShape shape(POINT_SIZE, 5);
        shape.setOrigin(POINT_SIZE / 2, POINT_SIZE / 2);
        shape.setFillColor(sf::Color::Green);

        float posX = (i - midpoint) + (WINDOW_SIZE_X / 2);
        float posY = tree_outputs[i] + (WINDOW_SIZE_Y / 2);
        shape.setPosition(posX, posY);

        window.draw(shape);
    }
}

void Graph::render_graph() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Graphing Calculator - Ian Cooper");
    sf::View view = window.getDefaultView();
    view.zoom(ZOOM_FACTOR);
    window.setView(view);
    while (window.isOpen())
    {
        zoom_zoom(window, view);
        window.clear(sf::Color::Blue);
        window.setView(view);
        display_grid(window, view);
        display_points(window);
        window.display();
    }
}

void Graph::display_grid(sf::RenderWindow& window, sf::View& view) {
    for (float y = 0; y < WINDOW_SIZE_Y; y += GRID_SPACING)
    {
        sf::Vertex horizontal_line[] =
        {
            sf::Vertex(sf::Vector2f(0, y), sf::Color::Black),
            sf::Vertex(sf::Vector2f(WINDOW_SIZE_X, y), sf::Color::Black)
        };
        window.draw(horizontal_line, 2, sf::Lines);
    }
    for (float x = 0; x <= WINDOW_SIZE_X; x += GRID_SPACING)
    {
        sf::Vertex vertical_line[] =
        {
            sf::Vertex(sf::Vector2f(x, 0), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x, WINDOW_SIZE_Y), sf::Color::Black)
        };
        window.draw(vertical_line, 2, sf::Lines);
    }
}