#pragma once
#include "ScoreBoard.h"
#include <sstream>
#include <iomanip>
ScoreBoard::ScoreBoard(const sf::Vector2f pos, const sf::Vector2f size): m_pos(pos),m_size(size)
{
	const Resources& res = Resources::instance();
	m_shape = sf::RectangleShape::RectangleShape(m_size);
	m_shape.setPosition(m_pos);
	m_shape.setFillColor(sf::Color::Green);
	
	createButtons();

	
}

void ScoreBoard::createButtons()
{
	const Resources& res = Resources::instance();

	
	m_playerScore.setString("Player's score :");
	m_playerScore.setCharacterSize(20);
	m_playerScore.setPosition(sf::Vector2f(0,520));
	m_playerScore.setFont(res.instance().get_font(font));
	m_playerScore.setFillColor(sf::Color::White);
	
	sf::Vector2f newPos;
	newPos.x = m_shape.getPosition().x + (m_shape.getSize().x/2);
	newPos.y = 520;
	m_npcScore.setString("Computer's score :");
	m_npcScore.setCharacterSize(20);
	m_npcScore.setPosition(newPos);
	m_npcScore.setFont(res.instance().get_font(font));
	m_npcScore.setFillColor(sf::Color::White);

}



sf::RectangleShape& ScoreBoard::getShape()
{
	return m_shape;
}

sf::Text& ScoreBoard::getPlayerScore()
{
	return m_playerScore;
}

sf::Text& ScoreBoard::getNpcScore()
{
	return m_npcScore;
}

