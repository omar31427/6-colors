#pragma once
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include "Resources.h"
const int NUMBER_OF_PLAYERS = 2;
class ScoreBoard {
public:
	enum ScoreOf {
		n_player,
		n_npc
	};
	ScoreBoard() {};
	ScoreBoard(const sf::Vector2f pos, const sf::Vector2f size);
	void createButtons();

	sf::RectangleShape& getShape();
	sf::Text& getPlayerScore();
	sf::Text& getNpcScore();
private:
	std::vector<sf::Text> m_scores;
	sf::Text m_playerScore;
	sf::Text m_npcScore;
	sf::RectangleShape m_shape;
	sf::Vector2f m_pos;
	sf::Vector2f m_size;
};