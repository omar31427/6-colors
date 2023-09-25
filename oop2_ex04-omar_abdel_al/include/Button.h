#pragma once
#include  <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "Resources.h"



class Button {
public:

	Button() {};
	Button(const sf::Vector2f pos, const sf::Vector2f size,const std::string text);
	sf::RectangleShape& getShape();
	sf::Text& getText();
	void setColor(const sf::Color color);
    enum class ColorName
    {
        Yellow,
        Blue,
        Cyan,
        Green,
        Magenta,
        Red
    };
    void applyX();
    void clearX();
    bool isLocked();

    std::unordered_map< ColorName, sf::Color> colorMap = {
        { ColorName::Yellow,sf::Color::Yellow},
        {ColorName::Blue,sf::Color::Blue},
        { ColorName::Cyan,sf::Color::Cyan},
        { ColorName::Green,sf::Color::Green},
        { ColorName::Magenta,sf::Color::Magenta},
        { ColorName::Red,sf::Color::Red}
    };
  
    std::string getColorString();
    ColorName getColorName(const int num);
private:
    bool m_locked = false;
 
	sf::Vector2f m_pos;
	sf::Vector2f m_size;
	sf::RectangleShape m_shape;
	sf::Text m_name;
};