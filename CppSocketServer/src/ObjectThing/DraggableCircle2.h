#include "Draggable.h"
#include "DraggableCircle.h"
#ifndef _DRAGABLECIRCLE2_H_
#define  _DRAGABLECIRCLE2_H_

// Draggable Circle
class DraggableCircle2 : public Draggable
{
public:
	DraggableCircle2(float radius, float length)
		: leftCircle(radius), rightCircle(radius), length(length), m_isDragging(false)
	{
		leftCircle.setPosition(sf::Vector2f(0, GROUND_HEIGHT - radius), sf::Vector2f(0, 0));
		rightCircle.setPosition(sf::Vector2f(length, GROUND_HEIGHT - radius), sf::Vector2f(0, 0));

		connector.setSize(sf::Vector2f(length, radius * 2));
		connector.setOrigin(length / 2, radius);
		connector.setFillColor(sf::Color::Red);
		connector.setPosition((leftCircle.getPosition() + rightCircle.getPosition()) / 2.0f);

		velocity = sf::Vector2f(0, 0);
	}

	void setPosition(const sf::Vector2f& position, const sf::Vector2f& offset)
	{
		if (this->CenterContains(position)) 
		{
			this->setCenterPosition(position);
		}
		else
		{
			// 定义两个指针来指向被拖动的圆和另一个圆
			DraggableCircle* draggedCircle = nullptr;
			DraggableCircle* otherCircle = nullptr;

			// 判断具体是哪个圆被拖动，并设置指针
			if (leftCircle.getGlobalBounds().contains(position))
			{
				draggedCircle = &leftCircle;
				otherCircle = &rightCircle;
			}
			else
			{
				draggedCircle = &rightCircle;
				otherCircle = &leftCircle;
			}

			// 更新被拖动的圆的位置
			draggedCircle->setPosition(position , -offset);

			// 获取更新后两个圆的位置
			sf::Vector2f draggedPosition = draggedCircle->getPosition() + sf::Vector2f(draggedCircle->getRadius(), draggedCircle->getRadius());
			sf::Vector2f otherPosition = otherCircle->getPosition() + sf::Vector2f(otherCircle->getRadius(), otherCircle->getRadius());

			// 计算连接轴的方向并确保其长度保持不变
			sf::Vector2f direction = otherPosition - draggedPosition;
			float currentLength = std::sqrt(direction.x * direction.x + direction.y * direction.y);

			// 如果距离不等于连接轴的长度，则进行调整
			if (currentLength != length)
			{
				direction /= currentLength;
				otherPosition = draggedPosition + direction * length;
				otherCircle->setPosition(otherPosition ,-sf::Vector2f(otherCircle->getRadius(), otherCircle->getRadius()));
			}

			// 更新连接轴的位置和旋转
			sf::Vector2f newDraggedPosition = draggedCircle->getPosition() + sf::Vector2f(draggedCircle->getRadius(), draggedCircle->getRadius());
			sf::Vector2f newOtherPosition = otherCircle->getPosition() + sf::Vector2f(otherCircle->getRadius(), otherCircle->getRadius());
			connector.setPosition((newDraggedPosition + newOtherPosition) / 2.0f);
			float angle = std::atan2(newOtherPosition.y - newDraggedPosition.y, newOtherPosition.x - newDraggedPosition.x);
			connector.setRotation(angle * 180.0f / 3.14159265f);
		
		};
	}

	void setCenterPosition(const sf::Vector2f& position)
	{
		sf::Vector2f offset = position - connector.getPosition();
		connector.setPosition(position);
		leftCircle.setPosition(leftCircle.getPosition(), offset);
		rightCircle.setPosition(rightCircle.getPosition() , offset);
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
		return leftCircle.contains(point) || rightCircle.contains(point)|| CenterContains(point);
	}

	bool CenterContains(const sf::Vector2f& point) const
	{
		return false;
		return connector.getGlobalBounds().contains(point);
	}

	void update(float deltaTime)
	{
		if (leftCircle.getPosition().y >= GROUND_HEIGHT && rightCircle.getPosition().y >= GROUND_HEIGHT)
			return;

		if (!m_isDragging)
		{
			// Apply gravity to the left circle
			if (leftCircle.getPosition().y < GROUND_HEIGHT)
			{
				leftVelocity.y += GRAVITY * deltaTime;
			}
			else
			{
				leftVelocity.y = 0;
			}

			// Apply gravity to the right circle
			if (rightCircle.getPosition().y < GROUND_HEIGHT)
			{
				rightVelocity.y += GRAVITY * deltaTime;
			}
			else
			{
				rightVelocity.y = 0;
			}

		}
		
		// Update positions of the circles
		leftCircle.setPosition(leftCircle.getPosition(),leftVelocity * deltaTime);
		rightCircle.setPosition(rightCircle.getPosition(),rightVelocity * deltaTime);

		// Prevent circles from going below ground
		if (leftCircle.getPosition().y > GROUND_HEIGHT)
		{
			leftCircle.setPosition(sf::Vector2f(leftCircle.getPosition().x, GROUND_HEIGHT), sf::Vector2f(0,0));
			leftVelocity.y = 0;
		}

		if (rightCircle.getPosition().y > GROUND_HEIGHT)
		{
			rightCircle.setPosition(sf::Vector2f(rightCircle.getPosition().x, GROUND_HEIGHT), sf::Vector2f(0, 0));
			rightVelocity.y = 0;
		}

		// Update connector position
		sf::Vector2f leftPosition = leftCircle.getPosition();
		sf::Vector2f rightPosition = rightCircle.getPosition();

		// Ensure fixed length
		sf::Vector2f direction = rightPosition - leftPosition;
		float currentLength = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= currentLength;

		if (currentLength > length)
		{
			rightCircle.setPosition(leftPosition, direction * length);
			rightPosition = leftPosition + direction * length;
		}

		// Update the position of the connector to be between the two circles
		connector.setPosition((leftPosition + rightPosition) / 2.0f);

		// Calculate the angle of the connector based on the positions of the circles
		float angle = std::atan2(rightPosition.y - leftPosition.y, rightPosition.x - leftPosition.x);
		connector.setRotation(angle * 180.0f / 3.14159265f);
	}


	void startDragging() override
	{
		m_isDragging = true;
	};
	void stopDragging() override
	{
		m_isDragging = false;
	};


private:
	DraggableCircle leftCircle;
	DraggableCircle rightCircle;
	sf::RectangleShape connector;
	sf::Vector2f velocity;
	sf::Vector2f leftVelocity;
	sf::Vector2f rightVelocity;
	float length;
	bool m_isDragging = false;

};


#endif