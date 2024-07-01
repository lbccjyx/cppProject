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

	void setPosition(const sf::Vector2f& position, const sf::Vector2f& offset) override
	{
		circle.setPosition(position + offset);
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

	float getRadius() const
	{
		return circle.getRadius();
	}

	sf::Vector2f getUpdatePosition(float deltaTime)
	{
		// Apply gravity   v=u+at
		if (circle.getPosition().y < GROUND_HEIGHT)
		{
			velocity.y += GRAVITY * deltaTime;
		}
		else
		{
			resetVelocity();
			return circle.getPosition();
		}

		if ((circle.getPosition() + velocity * deltaTime).y > GROUND_HEIGHT)
		{
			return sf::Vector2f(circle.getPosition().x, GROUND_HEIGHT); 
		}
		else
		{
			return circle.getPosition() + velocity * deltaTime;
		}

	}
	
	void resetVelocity()
	{
		velocity = sf::Vector2f(0, 0);
	}
	float GetVelocity()
	{
		return velocity.y;
	}
	void update(float deltaTime) override
	{
		setPosition(this->getUpdatePosition(deltaTime), sf::Vector2f(0, 0));		
	}

private:
	sf::CircleShape circle;
	sf::Vector2f velocity; //velocity.y 表示垂直方向的速度
};


#endif