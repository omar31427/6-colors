#pragma once
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
class Node {
public:
	Node(Node* node) { *this = node; };
	Node(const sf::Vector2f pos,const float radius);
	sf::Vector2f getPosition();
	sf::CircleShape& getShape();
	sf::Color getColor();
	void setColor(sf::Color color);
	float getRadius();//this is for debugging pruposes, can be used in the future
	std::string getColorString();
private:
	float m_radius;
	sf::CircleShape m_shape;
	sf::Vector2f m_pos;
	sf::Color m_color;
};