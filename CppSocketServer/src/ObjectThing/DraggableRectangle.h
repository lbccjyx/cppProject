#include "Draggable.h"

#ifndef _DRAGABLERECTANGLE_H_
#define  _DRAGABLERECTANGLE_H_
// Draggable Rectangle
class DraggableRectangle : public Draggable
{
public:
	DraggableRectangle(const sf::Vector2f& size)
	{
		rectangle.setSize(size);
		rectangle.setFillColor(sf::Color::Blue);
		rectangle.setOrigin(size.x / 2, size.y / 2); // Set origin to the center for easier positioning
		velocity = sf::Vector2f(0, 0);
	}

	void setPosition(const sf::Vector2f& position, const sf::Vector2f& offset) override
	{
		rectangle.setPosition(position + offset);
	}

	sf::Vector2f getPosition() const override
	{
		return rectangle.getPosition();
	}

	sf::FloatRect getGlobalBounds() const override
	{
		return rectangle.getGlobalBounds();
	}

	void draw(sf::RenderWindow& window) override
	{
		window.draw(rectangle);
	}

	bool contains(const sf::Vector2f& point) const override
	{
		return rectangle.getGlobalBounds().contains(point);
	}


	void update(float deltaTime) override
	{
		// Apply gravity
		if (rectangle.getPosition().y + rectangle.getSize().y / 2 < GROUND_HEIGHT)
		{
			velocity.y += GRAVITY * deltaTime;
		}
		else
		{
			velocity.y = 0;
		}

		// Update position
		setPosition(rectangle.getPosition(), velocity * deltaTime);

		// Prevent from going below ground
		if (rectangle.getPosition().y + rectangle.getSize().y / 2 > GROUND_HEIGHT)
		{
			setPosition(sf::Vector2f(rectangle.getPosition().x, GROUND_HEIGHT - rectangle.getSize().y / 2), sf::Vector2f(0, 0));
		}
	}

private:
	sf::RectangleShape rectangle;
	sf::Vector2f velocity;
};


#endif
