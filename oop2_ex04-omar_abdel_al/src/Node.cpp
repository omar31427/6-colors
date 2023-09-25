#pragma once
#include "Node.h"

#include <iostream>
Node::Node(const sf::Vector2f pos,const float radius):m_pos(pos),m_radius(radius)
{

	m_shape = sf::CircleShape::CircleShape(radius,6);
	int randColor = rand() % 6;
	switch (randColor)
	{
	case 0:
		m_color = sf::Color::Yellow;
		break;
	case 1:
		m_color = sf::Color::Blue;
		break;
	case 2:
		m_color = sf::Color::Cyan;
		break;
	case 3:
		m_color = sf::Color::Green;
		break;
	case 4:
		m_color = sf::Color::Magenta;
		break;
	case 5:
		m_color = sf::Color::Red;
		break;
	default :
		m_color = sf::Color::White;
		break;
	}
	m_shape.setFillColor(m_color);
	m_shape.setPosition(m_pos);
	m_shape.setOutlineThickness(1);
	m_shape.setOutlineColor(sf::Color::Black);
}

sf::Vector2f Node::getPosition()
{
	return m_pos;
}

sf::CircleShape& Node::getShape()
{

	return m_shape;
}

sf::Color Node::getColor()
{
	return m_color;
}

void Node::setColor(sf::Color color)
{
	
	m_shape.setFillColor(color);
}

float Node::getRadius()
{
	return m_shape.getRadius();
}

std::string Node::getColorString()
{
	if (m_color == sf::Color::Yellow)
		return "Yellow";
	else if (m_color == sf::Color::Blue)
		return "Blue";
	else if (m_color == sf::Color::Cyan)
		return "Cyan";
	else if (m_color == sf::Color::Green)
		return "Green";
	else if (m_color == sf::Color::Magenta)
		return "Magenta";
	else if (m_color == sf::Color::Red)
		return "Red";
}




