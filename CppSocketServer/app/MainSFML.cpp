#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
using namespace std;

// Function to convert degrees to radians
float degreesToRadians(float degrees) {
    return degrees * (3.14159265 / 180.0);
}

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "2D Simulation");

    // Circle properties
    sf::CircleShape circle(50); // Circle with radius 50
    circle.setFillColor(sf::Color::Green);
    circle.setOrigin(50, 50); // Center the circle at its origin
    circle.setPosition(400, 300); // Center of the window

    // Line properties
    sf::RectangleShape line(sf::Vector2f(200, 5)); // Line with length 200 and thickness 5
    line.setFillColor(sf::Color::Red);
    line.setOrigin(0, 2.5); // Set origin to the center of the line's thickness
    line.setPosition(400, 300); // Start at the circle's center

    // Rotation angle
    float angle = 0.0;

    // Run the main loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update
        angle += 0.1; // Rotate the line
        if (angle > 360) angle = 0;
        line.setRotation(angle);

        // Calculate the end position of the line
        float lineLength = 200;
        float endX = 400 + lineLength * std::cos(degreesToRadians(angle));
        float endY = 300 + lineLength * std::sin(degreesToRadians(angle));

        // Draw everything
        window.clear();
        window.draw(circle);
        window.draw(line);
        window.display();
    }

    return 0;
}
