#pragma once
#include "Button.h"

Button::Button(const sf::Vector2f pos, const sf::Vector2f size,const std::string text) :m_pos(pos), m_size(size)
{
	const Resources& res = Resources::instance();

	m_shape = sf::RectangleShape::RectangleShape(m_size);
	m_shape.setPosition(m_pos);

	m_name.setString(text);
	

	float charSize = (m_shape.getSize().x * m_shape.getSize().y) / (text.length() *25 );
	m_name.setCharacterSize(charSize);
	m_pos.x = pos.x;
	m_pos.y = pos.y + m_name.getCharacterSize()/2;
	m_name.setPosition(m_pos);

	m_name.setFont(res.instance().get_font(font));
	m_name.setFillColor(sf::Color::Black);


}

sf::RectangleShape& Button::getShape()
{
	return m_shape;
}

sf::Text& Button::getText()
{
	return m_name;
}

void Button::setColor(const sf::Color color)
{
	m_shape.setFillColor(color);
}

void Button::applyX()
{
	const Resources& res = Resources::instance();
	m_shape.setTexture(res.instance().getTexture(n_noPick));
	m_locked = true;
}



void Button::clearX()
{
	m_shape.setTexture(nullptr);
	m_locked = false;
}

bool Button::isLocked()
{
	return m_locked;
}

std::string Button::getColorString()
{
	if (m_shape.getFillColor() == sf::Color::Yellow)
		return "Yellow";
	else if (m_shape.getFillColor() == sf::Color::Blue)
		return "Blue";
	else if (m_shape.getFillColor() == sf::Color::Cyan)
		return "Cyan";
	else if (m_shape.getFillColor() == sf::Color::Green)
		return "Green";
	else if (m_shape.getFillColor() == sf::Color::Magenta)
		return "Magenta";
	else if (m_shape.getFillColor() == sf::Color::Red)
		return "Red";
}

Button::ColorName Button::getColorName(const int num)
{
	return static_cast<ColorName>(num);
}
