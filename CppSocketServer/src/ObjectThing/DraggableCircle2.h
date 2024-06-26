#include "Draggable.h"
#include "DraggableCircle.h"
#ifndef _DRAGABLECIRCLE2_H_
#define  _DRAGABLECIRCLE2_H_

// Draggable Circle
class DraggableCircle2 : public Draggable
{
public:
	DraggableCircle2(float radius, float length)
		: leftCircle(radius), rightCircle(radius), length(length), isDragging(false)
	{
		leftCircle.setPosition(sf::Vector2f(0, GROUND_HEIGHT - radius));
		rightCircle.setPosition(sf::Vector2f(length, GROUND_HEIGHT - radius));

		connector.setSize(sf::Vector2f(length, radius * 2));
		connector.setOrigin(length / 2, radius);
		connector.setFillColor(sf::Color::Red);
		connector.setPosition((leftCircle.getPosition() + rightCircle.getPosition()) / 2.0f);

		velocity = sf::Vector2f(0, 0);
	}

	void setPosition(const sf::Vector2f& position)
	{
		this->startDragging();
		sf::Vector2f offset = position - leftCircle.getPosition();
		leftCircle.setPosition(position);
		rightCircle.setPosition(leftCircle.getPosition() + sf::Vector2f(length, 0));
		connector.setPosition((leftCircle.getPosition() + rightCircle.getPosition()) / 2.0f);
		this->stopDragging();
	}

	sf::Vector2f getPosition() const
	{
		return leftCircle.getPosition();
	}

	sf::FloatRect getGlobalBounds() const
	{
		sf::FloatRect leftBounds = leftCircle.getGlobalBounds();
		sf::FloatRect rightBounds = rightCircle.getGlobalBounds();
		sf::FloatRect connectorBounds = connector.getGlobalBounds();

		float left = std::min({ leftBounds.left, rightBounds.left, connectorBounds.left });
		float top = std::min({ leftBounds.top, rightBounds.top, connectorBounds.top });
		float right = std::max({ leftBounds.left + leftBounds.width, rightBounds.left + rightBounds.width, connectorBounds.left + connectorBounds.width });
		float bottom = std::max({ leftBounds.top + leftBounds.height, rightBounds.top + rightBounds.height, connectorBounds.top + connectorBounds.height });

		return sf::FloatRect(left, top, right - left, bottom - top);
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(connector);
		leftCircle.draw(window);
		rightCircle.draw(window);
	}

	bool contains(const sf::Vector2f& point) const
	{
		return leftCircle.contains(point) || rightCircle.contains(point);
	}

	void update(float deltaTime)
	{
		if (!isDragging)
		{
			// Apply gravity to the right circle
			if (rightCircle.getPosition().y < GROUND_HEIGHT)
			{
				velocity.y += GRAVITY * deltaTime;
			}
			else
			{
				velocity.y = 0;
			}

			// Update position of the right circle
			rightCircle.setPosition(rightCircle.getPosition() + velocity * deltaTime);

			// Prevent from going below ground
			if (rightCircle.getPosition().y > GROUND_HEIGHT)
			{
				rightCircle.setPosition(sf::Vector2f(rightCircle.getPosition().x, GROUND_HEIGHT));
			}
		}

		// Update connector position
		sf::Vector2f leftPosition = leftCircle.getPosition();
		sf::Vector2f rightPosition = rightCircle.getPosition();

		// Ensure fixed length
		sf::Vector2f direction = rightPosition - leftPosition;
		float currentLength = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= currentLength;
		rightPosition = leftPosition + direction * length;
		rightCircle.setPosition(rightPosition);

		// Update the position of the connector to be between the two circles
		connector.setPosition((leftPosition + rightPosition) / 2.0f);

		// Calculate the angle of the connector based on the positions of the circles
		float angle = std::atan2(rightPosition.y - leftPosition.y, rightPosition.x - leftPosition.x);
		connector.setRotation(angle * 180.0f / 3.14159265f);
	}

	void startDragging()
	{
		isDragging = true;
	}

	void stopDragging()
	{
		isDragging = false;
	}

private:
	DraggableCircle leftCircle;
	DraggableCircle rightCircle;
	sf::RectangleShape connector;
	sf::Vector2f velocity;
	bool isDragging;
	float length;
};


#endif