#pragma once
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <fstream>
#include <unordered_map>






using std::ifstream;
using std::vector;
enum obj_types_names
{
	n_noPick
};
enum fontnames
{
	font
};
class Resources
{
public:
	static Resources& instance();



	sf::Font& get_font(const fontnames name);
	sf::Texture* getTexture(const obj_types_names);
	int getTextsNum();
private:
	Resources();
	void load_texture(std::string texture_path, obj_types_names obtype);
	void load_font(std::string font_path, fontnames name);

	Resources(const Resources&) = default;
	Resources& operator=(const Resources&) = default;
	std::unordered_map <obj_types_names, sf::Texture> m_textures;

	std::unordered_map <fontnames, sf::Font> m_fonts;
	sf::Texture temp;
};