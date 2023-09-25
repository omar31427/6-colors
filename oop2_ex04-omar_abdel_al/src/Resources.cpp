#pragma once
#include "Resources.h"



using std::vector;


Resources::Resources()
{

	load_texture("x.png", n_noPick);
	load_font("milkyroad.otf", font);
	int num_of_lvls = 0;

}
void Resources::load_texture(std::string texture_path, obj_types_names objtype)
{

	if (!m_textures[objtype].loadFromFile(texture_path))
	{
		std::cerr << texture_path << " ";
		throw (std::exception("error loading texture"));
	}

}
void Resources::load_font(std::string font_path, fontnames name)
{

	sf::Font tempfont;
	tempfont.loadFromFile(font_path);
	m_fonts[name] = tempfont;
}

int Resources::getTextsNum()
{
	return m_textures.size();
}
sf::Font& Resources::get_font(const fontnames name)
{
	return m_fonts[name];
}

sf::Texture* Resources::getTexture(const obj_types_names name)
{
	return &(m_textures[name]);
}


Resources& Resources::instance()
{
	static Resources inst;
	return inst;

}



using std::vector;

