#include "fileinit.h"
#include <SFML/Graphics.hpp>


#ifndef _DRAGABLE_H_
#define  _DRAGABLE_H_

const float GRAVITY = 980.0f; // �������ٶ� ͨ����9.8m/s^2 ��������û��mֻ��980px/s^2
const float GROUND_HEIGHT = 550.0f; // ����߶�
class Draggable
{
public:
	virtual ~Draggable() = default;
	virtual void setPosition(const sf::Vector2f& position) = 0;
	virtual sf::Vector2f getPosition() const = 0;
	virtual sf::FloatRect getGlobalBounds() const = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual bool contains(const sf::Vector2f& point) const = 0;
	virtual void update(float deltaTime) = 0;
};

#endif