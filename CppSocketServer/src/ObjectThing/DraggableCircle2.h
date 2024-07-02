#include "Draggable.h"
#include "DraggableCircle.h"
#ifndef _DRAGABLECIRCLE2_H_
#define  _DRAGABLECIRCLE2_H_

// Draggable Circle
class DraggableCircle2 : public Draggable
{
public:
	//  Pos1  sf::Vector2f(0, GROUND_HEIGHT)  Pos2 sf::Vector2f(length, GROUND_HEIGHT)
	DraggableCircle2(float radius, float length, sf::Vector2f Pos1, sf::Vector2f Pos2)
		: leftCircle(radius), rightCircle(radius), length(length), m_isDragging(false)
	{
		leftCircle.setPosition(Pos1, sf::Vector2f(0, 0));
		rightCircle.setPosition(Pos2, sf::Vector2f(0, 0));

		connector.setSize(sf::Vector2f(length, radius * 2));
		connector.setOrigin(length / 2, radius);
		connector.setFillColor(sf::Color::Red);
		connector.setPosition((leftCircle.getPosition() + rightCircle.getPosition()) / 2.0f);
	}

	void setConnPosition(DraggableCircle* draggedCircle, DraggableCircle* otherCircle, const sf::Vector2f& position, const sf::Vector2f& offset)
	{
		if (draggedCircle->getPosition() == position && offset == sf::Vector2f(0, 0))
			return;

		// 更新被拖动的圆的位置
		draggedCircle->setPosition(position, offset);

		// 获取更新后两个圆的位置
		sf::Vector2f draggedPosition = draggedCircle->getPosition();
		sf::Vector2f otherPosition = otherCircle->getPosition();

		// 计算连接轴的方向并确保其长度保持不变
		sf::Vector2f direction = otherPosition - draggedPosition;
		float currentLength = std::sqrt(direction.x * direction.x + direction.y * direction.y);

		// 如果距离不等于连接轴的长度，则进行调整
		if (currentLength != length)
		{
			direction /= currentLength;
			sf::Vector2f newOtherPosition = draggedPosition + direction * length;

			// 检查 newOtherPosition 是否会超过地面
			if (newOtherPosition.y > GROUND_HEIGHT)
			{
				// 计算新位置
				float deltaY = GROUND_HEIGHT - draggedPosition.y;
				float deltaX = std::sqrt(length * length - deltaY * deltaY);
				if (newOtherPosition.x > draggedPosition.x)
					newOtherPosition.x = draggedPosition.x + deltaX;
				else
					newOtherPosition.x = draggedPosition.x - deltaX;

				newOtherPosition.y = GROUND_HEIGHT;
			}

			// 如果其中一个圆在地面 那么这个圆的位置不变，另一个圆的位置更新
			if (draggedPosition.y >= GROUND_HEIGHT)
			{
				// 仅调整 otherCircle 的位置
				otherCircle->setPosition(newOtherPosition, sf::Vector2f(0, 0));
			}
			else if (otherPosition.y >= GROUND_HEIGHT)
			{
				// 计算 newDraggedPosition 以维持连接的距离
				sf::Vector2f newDraggedPosition = otherPosition - direction * length;
				draggedCircle->setPosition(newDraggedPosition, sf::Vector2f(0, 0));
			}
			else
			{
				// 设置 otherCircle 位置
				otherCircle->setPosition(newOtherPosition, sf::Vector2f(0, 0));
			}
		}

		// 更新连接轴的位置和旋转
		sf::Vector2f newDraggedPosition = draggedCircle->getPosition();
		sf::Vector2f newOtherPosition = otherCircle->getPosition();
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
			// 定义两个指针来指向被拖动的圆和另一个圆
			DraggableCircle* draggedCircle = nullptr;
			DraggableCircle* otherCircle = nullptr;

			// 判断具体是哪个圆被拖动，并设置指针
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
		// 系统平衡，不需要移动
		if (leftCircle.getPosition().y >= GROUND_HEIGHT && rightCircle.getPosition().y >= GROUND_HEIGHT)
			return;

		if (leftCircle.getPosition().x == rightCircle.getPosition().x 
			&& (leftCircle.getPosition().y >= GROUND_HEIGHT || rightCircle.getPosition().y >= GROUND_HEIGHT))
			return;
		
		if (!m_isDragging)
		{
			// 更新左圆的位置
			sf::Vector2f newLeftPosition = leftCircle.getUpdatePosition(deltaTime); 
			sf::Vector2f newRightPosition = rightCircle.getUpdatePosition(deltaTime);
			setConnPosition(&leftCircle, &rightCircle, newLeftPosition, sf::Vector2f(0, 0));
			setConnPosition(&rightCircle, &leftCircle, newRightPosition, sf::Vector2f(0, 0));
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

	void resetVelocity()
	{
		leftCircle.resetVelocity();
		rightCircle.resetVelocity();
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
	//  Pos1  sf::Vector2f(0, GROUND_HEIGHT)  Pos2 sf::Vector2f(length, GROUND_HEIGHT)
	DraggableCircle3(float radius, float length, int nNum):DraggableCircle2(radius, length, sf::Vector2f(0, GROUND_HEIGHT), sf::Vector2f(length, GROUND_HEIGHT))
	{
		for (int i = 0; i < nNum; i++)
		{
			DraggableCircle2* pCircle = new DraggableCircle2(radius, length, sf::Vector2f(i * length, 0.5 * GROUND_HEIGHT), sf::Vector2f((i + 1) * length, 0.5 * GROUND_HEIGHT));
			m_listCircle.push_back(pCircle);
		}
	}

	~DraggableCircle3()
	{
		if (m_listCircle.size() > 0)
		{
			for (auto pCircle : m_listCircle)
			{
				delete pCircle;
			}
			m_listCircle.clear();
		}
	}

	void update(float deltaTime) override
	{
		for (auto pCircle : m_listCircle)
		{
			pCircle->update(deltaTime);
		}

		auto it = m_listCircle.begin();
		auto end = std::prev(m_listCircle.end());
		for (; it != end; ++it)
		{
			auto next = std::next(it);
			(*it)->setRightCirPosition((*next)->getLeftCirPosition());
			(*next)->setLeftCirPosition((*it)->getRightCirPosition());
		}

	}
	void draw(sf::RenderWindow& window) override
	{
		for (auto pCircle : m_listCircle)
		{
			pCircle->draw(window);
		}
	}

	bool contains(const sf::Vector2f& point) const
	{
		bool bRet = false;
		for (auto pCircle : m_listCircle)
		{
			if (pCircle->getGlobalBounds().contains(point))
			{
				bRet = true;
				break;
			}
		}
		return bRet;
	}

	void startDragging() override
	{
		for (auto pCircle : m_listCircle)
		{
			pCircle->startDragging();
		}
	};
	void stopDragging() override
	{
		for (auto pCircle : m_listCircle)
		{
			pCircle->stopDragging();
		}
	};

	void setPosition(const sf::Vector2f& position, const sf::Vector2f& offset) override
	{
		for (auto it = m_listCircle.begin(); it != m_listCircle.end(); ++it)
		{
			if ((*it)->contains(position))
			{
				(*it)->setPosition(position, offset);

				auto next = std::next(it);
				if (next != m_listCircle.end())
					(*next)->setLeftCirPosition((*it)->getRightCirPosition());

				if (it != m_listCircle.begin())
					(*std::prev(it))->setRightCirPosition((*it)->getLeftCirPosition());
				// 不再使用 break 语句
			}
		}

		for (auto pCircle : m_listCircle)
		{
			pCircle->resetVelocity();
		}
	}

private:
	std::list<DraggableCircle2*> m_listCircle;
};

#endif