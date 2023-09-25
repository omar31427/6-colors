#pragma once
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include <memory>

const int NUMBER_OF_BUTTONS = 6;
class ToolBar {
public:
	ToolBar() {};
	ToolBar(const sf::Vector2f pos, const sf::Vector2f size);
	sf::RectangleShape& getShape();
	std::vector<std::shared_ptr<Button>>& getButtons();
	void createButtons();
	float getWidth() { return m_shape.getSize().x; };
	sf::Text& getInstructions();
	void applyXto(const int color);
private:
	sf::Text m_instruction;
	sf::Vector2f m_pos;
	sf::Vector2f m_size;
	sf::RectangleShape m_shape;
	std::vector<std::shared_ptr<Button>> m_buttons;
};