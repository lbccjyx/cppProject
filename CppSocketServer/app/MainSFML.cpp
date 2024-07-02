#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "ObjectThing/DraggableCircle.h"
#include "ObjectThing/DraggableRectangle.h"
#include "ObjectThing/DraggableCircle2.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, GROUND_HEIGHT+10), "Draggable Shapes with Gravity");
	std::vector<std::unique_ptr<Draggable>> shapes;

	//shapes.push_back(std::make_unique<DraggableCircle>(50));
	//shapes.back()->setPosition(sf::Vector2f(200, 200));

	//shapes.push_back(std::make_unique<DraggableRectangle>(sf::Vector2f(200, 100)));
	//shapes.back()->setPosition(sf::Vector2f(400, 300));

	shapes.push_back(std::make_unique<DraggableCircle3>(10, 200, 3));
	shapes.back()->setPosition(sf::Vector2f(400, 300), sf::Vector2f{0,0});

	bool isDragging = false;
	sf::Vector2f offset;
	Draggable* draggedShape = nullptr;

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
					for (auto& shape : shapes)
					{
						if (shape->contains(mousePos))
						{
							isDragging = true;
							shape->startDragging();
							offset = shape->getPosition() - mousePos;
							draggedShape = shape.get();
							break;
						}
					}
				}
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					for (auto& shape : shapes)
					{
						shape->stopDragging();
					}
					isDragging = false;
					draggedShape = nullptr;
				}
			}

			if (event.type == sf::Event::MouseMoved)
			{
				if (isDragging && draggedShape)
				{
					draggedShape->setPosition(sf::Vector2f(event.mouseMove.x, event.mouseMove.y),offset);
				}
			}
		}

		float deltaTime = clock.restart().asSeconds();

		for (auto& shape : shapes)
		{
			shape->update(deltaTime);
		}

		window.clear();
		for (auto& shape : shapes)
		{
			shape->draw(window);
		}
		window.display();
	}

	return 0;
}
