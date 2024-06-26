#include "fileinit.h"
#include <SFML/Graphics.hpp>


#ifndef _DRAGABLE_H_
#define  _DRAGABLE_H_

const float GRAVITY = 980.0f; // 重力加速度 通常是9.8m/s^2 但是这里没有m只有980px/s^2
const float GROUND_HEIGHT = 550.0f; // 地面高度
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