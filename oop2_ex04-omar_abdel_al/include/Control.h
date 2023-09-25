#pragma once
#include "Toolbar.h"
#include "Node.h"
#include "ScoreBoard.h"
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>

#include <algorithm>
const int NUMBER_OF_NODES = 40;
;

class Control{
public:
	Control();
	void chooseDifficulty();
	void run();
	void draw();
	void createNodes();
	void createAdjLists();
	void updateNode();
	void clearTheX();
	void pushAdjIntoCluster(std::shared_ptr<Node> root, const int type);
	void gameEnded();
	
	void easyNpc();
	void mediumNpc();

	void lookForAdjWithSameColor(std::unordered_map<std::shared_ptr<Node>, bool>& visitedMap, std::unordered_map<std::string, int>& colorCount, std::shared_ptr<Node> root);
	void hardNpc();
private:
	std::unordered_map<std::shared_ptr<Node>, bool> visitedFreeNodes;
	std::unordered_map< std::string, sf::Color> stringToColorMap = {
		{ "Yellow",sf::Color::Yellow},
		{ "Blue",sf::Color::Blue},
		{ "Cyan",sf::Color::Cyan},
		{ "Green",sf::Color::Green},
		{ "Magenta",sf::Color::Magenta},
		{ "Red",sf::Color::Red}
	};
	std::unordered_map<std::string, int> colorInToolBarIndex = {
		{"Yellow",1},
		{ "Blue",2},
		{ "Cyan",3},
		{ "Green",4},
		{ "Magenta",5},
		{ "Red",6}
	};
	std::unordered_map<std::shared_ptr<Node>, std::list<std::shared_ptr<Node>>> m_adjLists;
	std::unordered_map<int, void (Control::*)()> m_npcDifficultyMap;

	std::vector<std::shared_ptr<Node>> m_playerCluster;
	std::vector<std::shared_ptr<Node>> m_NPCcluster;
	std::vector<std::shared_ptr<Node>> m_freeCluster;
	sf::RenderWindow m_window;
	std::vector<std::shared_ptr<Node>> m_nodes;
	sf::RectangleShape m_gameRec;
	sf::RectangleShape m_backGround;
	ToolBar m_toolBar;
	ScoreBoard m_scoreBoard;
	int m_playerOrigin;
	int m_NPCorigin;
	std::string m_NPCcurColor;
	std::string m_playerCurColor;

	


	int m_npcDifficulty;
	
};