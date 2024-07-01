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
	}

	void setConnPosition(DraggableCircle* draggedCircle, DraggableCircle* otherCircle, const sf::Vector2f& position, const sf::Vector2f& offset)
	{
		if(draggedCircle->getPosition() == position && offset == sf::Vector2f(0, 0))
			return;
		// ���±��϶���Բ��λ��
		draggedCircle->setPosition(position, offset);

		// ��ȡ���º�����Բ��λ��
		sf::Vector2f draggedPosition = draggedCircle->getPosition();
		sf::Vector2f otherPosition = otherCircle->getPosition();

		// ����������ķ���ȷ���䳤�ȱ��ֲ���
		sf::Vector2f direction = otherPosition - draggedPosition;
		float currentLength = std::sqrt(direction.x * direction.x + direction.y * direction.y);

		// ������벻����������ĳ��ȣ�����е���
		if (currentLength != length)
		{
			direction /= currentLength;
			sf::Vector2f newOtherPosition = draggedPosition + direction * length;

			// ��� newOtherPosition �Ƿ�ᳬ������
			if (newOtherPosition.y > GROUND_HEIGHT)
			{
				// ������λ��
				float deltaY = GROUND_HEIGHT - draggedPosition.y;
				float deltaX = std::sqrt(length * length - deltaY * deltaY);
				if (newOtherPosition.x > draggedPosition.x)
					newOtherPosition.x = draggedPosition.x + deltaX;
				else
					newOtherPosition.x = draggedPosition.x - deltaX;

				newOtherPosition.y = GROUND_HEIGHT;
			}
			
			// ���� otherCircle λ��
			otherCircle->setPosition(newOtherPosition, sf::Vector2f(0, 0));
			
		}

		// �����������λ�ú���ת
		sf::Vector2f newDraggedPosition = draggedCircle->getPosition() ;
		sf::Vector2f newOtherPosition = otherCircle->getPosition() ;
		connector.setPosition((newDraggedPosition + newOtherPosition) / 2.0f);
		float angle = std::atan2(newOtherPosition.y - newDraggedPosition.y, newOtherPosition.x - newDraggedPosition.x);
		connector.setRotation(angle * 180.0f / 3.14159265f);
	}

	void setPosition(const sf::Vector2f& position, const sf::Vector2f& offset)
	{
		if (this->CenterContains(position)) 
		{
			this->setCenterPosition(position);
		}
		else
		{
			// ��������ָ����ָ���϶���Բ����һ��Բ
			DraggableCircle* draggedCircle = nullptr;
			DraggableCircle* otherCircle = nullptr;

			// �жϾ������ĸ�Բ���϶���������ָ��
			if (leftCircle.getGlobalBounds().contains(position))
			{
				this->setConnPosition(&leftCircle, &rightCircle, position, offset);
			}
			else
			{
				this->setConnPosition(&rightCircle, &leftCircle, position, offset);
			}
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
		return this->getGlobalBounds().contains(point);
	}

	bool CenterContains(const sf::Vector2f& point) const
	{
		return connector.getGlobalBounds().contains(point);
	}

	void update(float deltaTime)
	{
		// ϵͳƽ�⣬����Ҫ�ƶ�
		if (leftCircle.getPosition().y >= GROUND_HEIGHT && rightCircle.getPosition().y >= GROUND_HEIGHT)
			return;

		if (leftCircle.getPosition().x == rightCircle.getPosition().x 
			&& (leftCircle.getPosition().y >= GROUND_HEIGHT || rightCircle.getPosition().y >= GROUND_HEIGHT))
			return;
		
		if (!m_isDragging)
		{
			if (rightCircle.GetVelocity() > leftCircle.GetVelocity())
			{
				this->setConnPosition(&rightCircle, &leftCircle, rightCircle.getUpdatePosition(deltaTime), sf::Vector2f(0, 0));
				this->setConnPosition(&leftCircle, &rightCircle, leftCircle.getUpdatePosition(deltaTime), sf::Vector2f(0, 0));
			}
			else
			{
				this->setConnPosition(&leftCircle, &rightCircle, leftCircle.getUpdatePosition(deltaTime), sf::Vector2f(0, 0));
				this->setConnPosition(&rightCircle, &leftCircle, rightCircle.getUpdatePosition(deltaTime), sf::Vector2f(0, 0));
			}
		}

	}


	void startDragging() override
	{
		m_isDragging = true;
	};
	void stopDragging() override
	{
		rightCircle.resetVelocity();
		leftCircle.resetVelocity();
		m_isDragging = false;
	};
	DraggableCircle2() = delete;

	void setLeftCirPosition(const sf::Vector2f& position)
	{
		setConnPosition(&leftCircle, &rightCircle, position, sf::Vector2f(0, 0));
		//leftCircle.setPosition(position, sf::Vector2f(0, 0));
	}
	sf::Vector2f getLeftCirPosition()
	{
		return leftCircle.getPosition();
	}

	void setRightCirPosition(const sf::Vector2f& position)
	{
		setConnPosition(&rightCircle, &leftCircle, position, sf::Vector2f(0, 0));
		//rightCircle.setPosition(position, sf::Vector2f(0, 0));
	}
	sf::Vector2f getRightCirPosition()
	{
		return rightCircle.getPosition();
	}
private:
	DraggableCircle leftCircle;
	DraggableCircle rightCircle;
	sf::RectangleShape connector;
	sf::Vector2f leftVelocity;
	sf::Vector2f rightVelocity;
	float length;
	bool m_isDragging = false;

};


class DraggableCircle3: public DraggableCircle2
{
public:
	DraggableCircle3(float radius, float length):DraggableCircle2(radius, length)
	{
		m_Circle2A = new DraggableCircle2(radius, length);
		m_Circle2B = new DraggableCircle2(radius, length);
	}

	~DraggableCircle3()
	{
		if(m_Circle2A)
			delete m_Circle2A;
		if(m_Circle2B)
			delete m_Circle2B;
	}

	void update(float deltaTime) override
	{
		m_Circle2A->update(deltaTime);
		m_Circle2B->setRightCirPosition(m_Circle2A->getLeftCirPosition());
		m_Circle2B->update(deltaTime);
		m_Circle2A->setLeftCirPosition(m_Circle2B->getRightCirPosition());
	}
	void draw(sf::RenderWindow& window) override
	{
		m_Circle2A->draw(window);
		m_Circle2B->draw(window);
	}

	bool contains(const sf::Vector2f& point) const
	{
		return m_Circle2A->getGlobalBounds().contains(point) || 
			m_Circle2B->getGlobalBounds().contains(point);
	}

	void startDragging() override
	{
		m_Circle2A->startDragging();
		m_Circle2B->startDragging();
	};
	void stopDragging() override
	{
		m_Circle2A->stopDragging();
		m_Circle2B->stopDragging();
	};

	void setPosition(const sf::Vector2f& position, const sf::Vector2f& offset) override
	{
		if (m_Circle2A->contains(position))
		{
			m_Circle2A->setPosition(position, offset);
			m_Circle2B->setRightCirPosition(m_Circle2A->getLeftCirPosition());
		}
		else if (m_Circle2B->contains(position))
		{
			m_Circle2B->setPosition(position, offset);
			m_Circle2A->setLeftCirPosition(m_Circle2B->getRightCirPosition());
		}
	}

private:
	DraggableCircle2* m_Circle2A;
	DraggableCircle2* m_Circle2B;
};

#endif