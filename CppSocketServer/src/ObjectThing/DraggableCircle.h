#include "Draggable.h"

#ifndef _DRAGABLECIRCLE_H_
#define  _DRAGABLECIRCLE_H_

// Draggable Circle
class DraggableCircle : public Draggable
{
public:
	DraggableCircle(float radius)
	{
		circle.setRadius(radius);
		circle.setFillColor(sf::Color::Green);
		circle.setOrigin(radius, radius); // Set origin to the center for easier positioning
		velocity = sf::Vector2f(0, 0);
	}

	void setPosition(const sf::Vector2f& position) override
	{
		circle.setPosition(position);
	}

	sf::Vector2f getPosition() const override
	{
		return circle.getPosition();
	}

	sf::FloatRect getGlobalBounds() const override
	{
		return circle.getGlobalBounds();
	}

	void draw(sf::RenderWindow& window) override
	{
		window.draw(circle);
	}

	bool contains(const sf::Vector2f& point) const override
	{
		return circle.getGlobalBounds().contains(point);
	}

	void update(float deltaTime) override
	{
		if (isDragging)
		{
			return;
		}
		// Apply gravity   v=u+at
		if (circle.getPosition().y + circle.getRadius() < GROUND_HEIGHT)
		{
			velocity.y += GRAVITY * deltaTime;
		}
		else
		{
			velocity.y = 0;
		}
		// Update position  s = s0 + vt
		setPosition(circle.getPosition() + velocity * deltaTime);

		// Prevent from going below ground
		if (circle.getPosition().y + circle.getRadius() > GROUND_HEIGHT)
		{
			setPosition(sf::Vector2f(circle.getPosition().x, GROUND_HEIGHT - circle.getRadius()));
		}
	}

private:
	sf::CircleShape circle;
	sf::Vector2f velocity; //velocity.y 表示垂直方向的速度
};


#endif