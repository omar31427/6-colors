#pragma once
#include "Toolbar.h"
#include <iostream>
ToolBar::ToolBar(const sf::Vector2f pos, const sf::Vector2f size) :m_pos(pos), m_size(size)
{
	const Resources& res = Resources::instance();
	m_shape = sf::RectangleShape::RectangleShape(m_size);
	m_shape.setPosition(m_pos);
	m_shape.setFillColor(sf::Color::White);
	createButtons();
	
	m_instruction.setString("Pick a color:");

	
	m_instruction.setCharacterSize(20);
	m_instruction.setPosition(sf::Vector2f(80 , m_pos.y + 10));
	m_instruction.setFont(res.instance().get_font(font));
	m_instruction.setFillColor(sf::Color::Black);
}

sf::RectangleShape& ToolBar::getShape()
{
	return m_shape;
}
std::vector<std::shared_ptr<Button>>& ToolBar::getButtons()
{
	return m_buttons;
}

void ToolBar::createButtons()
{
	m_buttons.push_back(std::make_shared<Button>(m_pos, sf::Vector2f(m_size.x / 10, m_size.y-20), "New"));

	sf::Vector2f colorPos(m_pos.x + 200,m_pos.y);
	sf::Vector2f colorSize(m_size.y,m_size.y);
	for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
	{
		m_buttons.push_back(std::make_shared<Button>(colorPos, colorSize, std::to_string(i)));
		m_buttons[m_buttons.size() - 1].get()->setColor(m_buttons[m_buttons.size() - 1].get()->colorMap[m_buttons[m_buttons.size() - 1].get()->getColorName(i)]);;

		colorPos.x += (colorSize.x + 10);
	}
	
	
}

sf::Text& ToolBar::getInstructions()
{
	return m_instruction;
}

void ToolBar::applyXto(const int color)
{
	m_buttons[color].get()->applyX();
}
