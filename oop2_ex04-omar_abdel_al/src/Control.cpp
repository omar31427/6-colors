#pragma once
#include "Control.h"


Control::Control():m_playerCurColor()
{
	m_window.setFramerateLimit(60);
	m_window.create(sf::VideoMode(600,635), "6 colors");
	m_gameRec = sf::RectangleShape::RectangleShape(sf::Vector2f(600, 600*(std::sqrt(3)/2)));
	m_gameRec.setFillColor(sf::Color::White);
	m_gameRec.setPosition(sf::Vector2f(0, 0));
	ToolBar bar(sf::Vector2f(0, 600), sf::Vector2f(m_window.getSize().x, 40));
	m_toolBar = bar;
	m_playerCurColor = " " ;
	m_NPCcurColor = " ";
	m_playerOrigin = NUMBER_OF_NODES -1;
	m_NPCorigin = (NUMBER_OF_NODES * NUMBER_OF_NODES) - NUMBER_OF_NODES;

	ScoreBoard scoreBoard(sf::Vector2f(0, m_gameRec.getPosition().y + m_gameRec.getSize().x), sf::Vector2f(m_window.getSize().x, (m_gameRec.getPosition().y + m_gameRec.getSize().y) - m_toolBar.getShape().getPosition().y));;
	m_scoreBoard = scoreBoard;
	m_backGround = sf::RectangleShape::RectangleShape(sf::Vector2f(600, 635));
	m_backGround.setPosition(sf::Vector2f(0, 0));
	m_backGround.setFillColor(sf::Color::Green);

	m_npcDifficultyMap[0] = &Control::easyNpc;
	m_npcDifficultyMap[1] = &Control::mediumNpc;
	m_npcDifficultyMap[2] = &Control::hardNpc;
	
}

void Control::chooseDifficulty()
{
	const Resources& res = Resources::instance();
	


	std::vector<sf::Text> texts;
	std::vector<sf::RectangleShape> textRects;
	for (int i = 0; i < 3; i++)
	{
		sf::RectangleShape newRect(sf::Vector2f(100, 50));
		newRect.setPosition(sf::Vector2f(m_backGround.getPosition().x + (m_backGround.getSize().x/2) - 50, m_backGround.getPosition().y + 200 + (i*60)));
		newRect.setFillColor(sf::Color::Yellow);
		textRects.push_back(newRect);
	}
	for (int i = 0; i < 3; i++)
	{
		sf::Text newText;
		sf::Vector2f pos;
		pos.x = textRects[i].getPosition().x + (((i + 1) % 2) * 25);
		pos.y = textRects[i].getPosition().y + 12.5;
		newText.setPosition(pos);
		newText.setCharacterSize(25);
		newText.setFont(res.instance().get_font(font));
		newText.setFillColor(sf::Color::Green);
		texts.push_back(newText);
	}
	texts[0].setString("Easy");
	texts[1].setString("Medium");
	texts[2].setString("Hard");
	m_window.draw(m_backGround);
	for (auto& rect : textRects)
		m_window.draw(rect);
	for (auto& text : texts)
		m_window.draw(text);
	m_window.display();
	bool showMenu = true;
	while (showMenu)
	{
		int Difficulty = 0;
		if (auto event = sf::Event{}; m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case (sf::Event::EventType::KeyPressed):
				;
			case (sf::Event::EventType::Closed):

				m_window.close();
				break;

			case (sf::Event::EventType::MouseButtonPressed):
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					for (auto& rect : textRects)
					{
						if (rect.getGlobalBounds().contains(m_window.mapPixelToCoords
						(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))) ) {
							m_npcDifficulty = Difficulty;
							showMenu = false;
						}
						Difficulty++;
					}

				}
				break;

			}
		}

		m_window.clear();
		m_window.draw(m_backGround);
		for (auto& rect : textRects)
			m_window.draw(rect);
		for (auto& text : texts)
			m_window.draw(text);
		m_window.display();
	}

}
	
void Control::run()
{
	m_playerCluster.clear();
	m_NPCcluster.clear();
	m_freeCluster.clear();
	clearTheX();

	m_window.clear();
	chooseDifficulty();
	createNodes();
	
	
	m_playerCluster.push_back(m_nodes[m_playerOrigin]);
	m_NPCcluster.push_back(m_nodes[m_NPCorigin]);
	for (int i = 0; i < m_nodes.size(); i++)
	{
		if (i != m_playerOrigin && i != m_NPCorigin)
		{
			m_freeCluster.push_back(std::make_shared<Node>(*m_nodes[i].get()));
			visitedFreeNodes.insert(std::make_pair(m_freeCluster[m_freeCluster.size()-1], false));
		}
	}

	createAdjLists();
	
	draw();

	while (m_window.isOpen())
	{		

		if (auto event = sf::Event{}; m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case (sf::Event::EventType::KeyPressed):
				;
			case (sf::Event::EventType::Closed):

				m_window.close();
			
				break;

			case (sf::Event::EventType::MouseButtonPressed):
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					for (auto& node : m_toolBar.getButtons())
					{
						if (node.get()->getShape().getGlobalBounds().contains(m_window.mapPixelToCoords
						(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))) && !node.get()->isLocked()) {
							if (node.get()->getText().getString() == "New")
									run();
							else {

								clearTheX();
								node.get()->applyX();
								m_playerCurColor = node.get()->getColorString();
								auto k = m_npcDifficultyMap[m_npcDifficulty];
								(this->*k)();
								m_toolBar.applyXto(colorInToolBarIndex[m_NPCcurColor]);
								
								updateNode();
							}
							
						}
						
					}
				
				}
				break;

			}
		}
		draw();
		if (float(m_NPCcluster.size()) /(float)(NUMBER_OF_NODES * NUMBER_OF_NODES) >= 0.5
			|| float(m_playerCluster.size()) / (float)(NUMBER_OF_NODES * NUMBER_OF_NODES) >= 0.5)
			gameEnded();
	}
	
}

void Control::gameEnded()
{
	const Resources& res = Resources::instance();


	
	sf::RectangleShape textRect(sf::Vector2f(150, 50));
	textRect.setPosition(sf::Vector2f(m_backGround.getPosition().x + (m_backGround.getSize().x / 2) - 75, m_backGround.getPosition().y + (m_backGround.getSize().y / 2) - 25));
	textRect.setFillColor(sf::Color::Yellow);

	
	sf::Text endGameText;
	endGameText.setPosition(sf::Vector2f(textRect.getPosition().x ,textRect.getPosition().y - 50));
	endGameText.setCharacterSize(40);
	endGameText.setFont(res.instance().get_font(font));
	endGameText.setFillColor(sf::Color::Yellow);
	if (m_playerCluster.size() >= m_NPCcluster.size())
		endGameText.setString("You win!");
	else
		endGameText.setString("You lose!");

	sf::Text text;
	sf::Vector2f pos;
	pos.x = textRect.getPosition().x;
	pos.y = textRect.getPosition().y;
	text.setPosition(pos);
	text.setCharacterSize(25);
	text.setFont(res.instance().get_font(font));
	text.setFillColor(sf::Color::Green);
	
	
	text.setString("Play again");
	m_window.clear();
	m_window.draw(m_backGround);
	m_window.draw(textRect);
	m_window.draw(text);
	m_window.draw(endGameText);

	m_window.display();
	bool show = true;
	while (show)
	{
		int Difficulty = 0;
		if (auto event = sf::Event{}; m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case (sf::Event::EventType::KeyPressed):
				;
			case (sf::Event::EventType::Closed):

				m_window.close();
				
				break;

			case (sf::Event::EventType::MouseButtonPressed):
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					
					if (textRect.getGlobalBounds().contains(m_window.mapPixelToCoords
					(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
						show = false;
						run();
					}
				}
				break;

			}
		}

		m_window.clear();
		m_window.draw(m_backGround);
		m_window.draw(textRect);
		m_window.draw(text);
		m_window.draw(endGameText);
		m_window.display();
	}
}

void Control::draw()
{
	m_window.clear();
	int i = 0;
	m_window.draw(m_gameRec);
	m_window.draw(m_toolBar.getShape());
	m_window.draw(m_toolBar.getInstructions());

	for (int j = 0; j < m_toolBar.getButtons().size(); j++)
	{
		m_window.draw(m_toolBar.getButtons()[j].get()->getShape());
		m_window.draw(m_toolBar.getButtons()[j].get()->getText());
	}

	for (auto& playerNode : m_playerCluster)
		m_window.draw(playerNode.get()->getShape());
	for (auto& npcNode: m_NPCcluster)
		m_window.draw(npcNode.get()->getShape());
	for (auto& freeNode : m_freeCluster)
		m_window.draw(freeNode.get()->getShape());
	
	std::string str1 = "player : " + std::to_string((float)m_playerCluster.size() / (float)(NUMBER_OF_NODES*NUMBER_OF_NODES));
	std::string str2 = "npc : " + std::to_string((float)m_NPCcluster.size() / (float)(NUMBER_OF_NODES * NUMBER_OF_NODES));
	
	m_window.draw(m_scoreBoard.getShape());
	m_scoreBoard.getNpcScore().setString(str2);
	m_scoreBoard.getPlayerScore().setString(str1);

	m_window.draw(m_scoreBoard.getPlayerScore());
	m_window.draw(m_scoreBoard.getNpcScore());

	m_window.display();
}

void Control::createNodes()
{
	m_nodes.clear();
	float radius =   m_gameRec.getSize().x / (2 * NUMBER_OF_NODES);
	radius -= (radius/(2*NUMBER_OF_NODES));
	std::vector<std::vector<sf::Vector2f>> tile_positions;
	for (int i = 0; i < NUMBER_OF_NODES; i++)
	{
		std::vector<sf::Vector2f> rows;
		for (int j = 0; j < NUMBER_OF_NODES; j++)
		{
			sf::Vector2f temp((radius *i * 2) + (radius * (j%2)) + m_gameRec.getPosition().x,((radius   *1.75 *j ) + m_gameRec.getPosition().y));
			rows.push_back(temp);
		}
		tile_positions.push_back(rows);
	}
	for (int i = 0; i < NUMBER_OF_NODES; i++)
	{
		for (int j = 0; j < NUMBER_OF_NODES; j++)
		{
			
			m_nodes.push_back(std::make_shared<Node>(tile_positions[i][j], (2 / std::sqrt(3)) * radius));
			
		}
	}
	
	
}

void Control::createAdjLists()
{
	
	for (int i = 0 ; i < m_freeCluster.size() ; i++ )
	{
		std::list<std::shared_ptr<Node>> curNodeList;
		for (int j = 0; j < m_freeCluster.size(); j++)
		{
			if (i == j)
				continue;
			
			if (m_freeCluster[i].get()->getShape().getGlobalBounds().intersects(m_freeCluster[j].get()->getShape().getGlobalBounds())
				&& m_freeCluster[i].get()->getColor() == m_freeCluster[j].get()->getColor())
				curNodeList.push_back(m_freeCluster[j]);
		}

		m_adjLists.insert(std::make_pair(m_freeCluster[i],curNodeList));
	}
}
void Control::pushAdjIntoCluster(std::shared_ptr<Node> root, const int type)
{
	std::list<std::shared_ptr<Node>> list = m_adjLists[root];
	
	for (auto i = list.begin(); i != list.end(); i++)
	{

		if (visitedFreeNodes[*i])
			continue;

		visitedFreeNodes[*i] = true;
		
		if (type == 0)
			m_playerCluster.push_back(*i);
		else if (type == 1)
			m_NPCcluster.push_back(*i);

		int index = 0;
		for (auto& freeNode : m_freeCluster)
		{

			if (freeNode.get()->getPosition() == i->get()->getPosition())
			{
				m_freeCluster.erase(m_freeCluster.begin() + index);

				
				break;
			}
			index++;

		}
	}

}

void Control::updateNode()
{
	
	for (int i = 0; i < m_playerCluster.size() ; i++)
	{
		int index;
		for (int j = 0; j < m_freeCluster.size(); j++)
		{
	
			if (m_freeCluster[j] == nullptr)
				continue;

			sf::FloatRect rectero = m_freeCluster[j].get()->getShape().getGlobalBounds();
			sf::Color colero = m_freeCluster[j].get()->getColor();

			if (m_playerCluster[i].get()->getShape().getGlobalBounds().intersects(rectero)
				&& colero == stringToColorMap[m_playerCurColor] && !visitedFreeNodes[m_freeCluster[j]])
			{
				m_playerCluster.push_back(m_freeCluster[j]);
				visitedFreeNodes[m_freeCluster[j]] = true;
				
		
			
				index = j;
				std::shared_ptr<Node> newPlayerNode = m_freeCluster[j];
				m_freeCluster.erase(m_freeCluster.begin() + index);

				pushAdjIntoCluster(newPlayerNode,0);
				
			
				
				
			}
		
		}
		
	}

	for (int i = 0; i < m_playerCluster.size(); i++)
	{
		if(m_playerCluster.size() != 1)
			m_playerCluster[i].get()->setColor(stringToColorMap[m_playerCurColor]);
	}
	//===========================================================
	//====================npc turn===============================
	//===========================================================
	for (int i = 0; i < m_NPCcluster.size(); i++)
	{
		int index;
		for (int j = 0; j < m_freeCluster.size(); j++)
		{

			if (m_freeCluster[j] == nullptr)
				continue;

			sf::FloatRect rectero = m_freeCluster[j].get()->getShape().getGlobalBounds();
			sf::Color colero = m_freeCluster[j].get()->getColor();

			if (m_NPCcluster[i].get()->getShape().getGlobalBounds().intersects(rectero)
				&& colero == stringToColorMap[m_NPCcurColor] && !visitedFreeNodes[m_freeCluster[j]])
			{
				m_NPCcluster.push_back(m_freeCluster[j]);
				visitedFreeNodes[m_freeCluster[j]] = true;


				index = j;
				std::shared_ptr<Node> newNpcNode = m_freeCluster[j];
				m_freeCluster.erase(m_freeCluster.begin() + index);

				pushAdjIntoCluster(newNpcNode, 1);
			}

		}

	}

	for (int i = 0; i < m_NPCcluster.size(); i++)
	{
		if (m_NPCcluster.size() != 1)
			m_NPCcluster[i].get()->setColor(stringToColorMap[m_NPCcurColor]);
	}
}

void Control::clearTheX() 
{
	for (int i = 0; i < m_toolBar.getButtons().size(); i++)
		m_toolBar.getButtons()[i].get()->clearX();
}



void Control::easyNpc() 
{

	int npcColor = rand() % 6;
	std::string colorName;


	switch (npcColor)
	{
	case 0:
		colorName = "Yellow";
		break;
	case 1:
		colorName = "Blue";
		break;
	case 2:
		colorName = "Cyan";
		break;
	case 3:
		colorName = "Green";
		break;
	case 4:
		colorName = "Magenta";
		break;
	case 5:
		colorName = "Red";
		break;
	default:
		colorName = "White";
		break;
	}

	if (colorName == m_playerCurColor || colorName == m_NPCcurColor)
		easyNpc();
	else
		m_NPCcurColor = colorName;
}

void Control::mediumNpc()
{
	std::unordered_map<std::string, int> colorCount;
	std::vector<bool> visited;
	for (auto& freeNode : m_freeCluster)
		visited.push_back(false);

	for (const auto& npcNode : m_NPCcluster)
	{
		int visitedIndex = 0;
		for (const auto& freeNode : m_freeCluster)
		{
			if (npcNode.get()->getShape().getGlobalBounds().intersects(freeNode->getShape().getGlobalBounds())
				&& !visited[visitedIndex])
			{
				const std::string color = freeNode.get()->getColorString();

				if (colorCount.find(color) == colorCount.end())
				{
					colorCount[color] = 1;
				}
				else
				{
					colorCount[color]++;
				}
				visited[visitedIndex] = true;
			}
			visitedIndex++;
		}
	}

	// Find the color with the maximum count
	std::string mostFrequentColor;
	int maxCount = 0;

	for (const auto& entry : colorCount)
	{
		if (entry.second > maxCount && entry.first != m_playerCurColor)
		{
			mostFrequentColor = entry.first;
			maxCount = entry.second;
		}
	}
	m_NPCcurColor = mostFrequentColor;
}

void Control::lookForAdjWithSameColor(std::unordered_map<std::shared_ptr<Node>, bool>& visitedMap, std::unordered_map<std::string, int>& colorCount,std::shared_ptr<Node> root)
{
	std::list<std::shared_ptr<Node>> list = m_adjLists[root];

	for (auto i = list.begin(); i != list.end(); i++)
	{

		if (visitedMap[*i])
		{
		
			continue;
		}
		visitedMap[*i] = true;
		colorCount[(*i)->getColorString()]++;
		lookForAdjWithSameColor(visitedMap, colorCount, *i);
		
	}
}
void Control::hardNpc()
{
	std::unordered_map<std::string, int> colorCount;
	std::unordered_map<std::shared_ptr<Node>, bool> visited;
	
	for (auto& freeNode : m_freeCluster)
		visited.insert(std::make_pair(freeNode,false));
	int lengthOfList = 0;
	std::shared_ptr<Node> bestNode;
	for (const auto& npcNode : m_NPCcluster)
	{
		int visitedIndex = 0;
		for (const auto& freeNode : m_freeCluster)
		{
			if (npcNode.get()->getShape().getGlobalBounds().intersects(freeNode->getShape().getGlobalBounds())
				&& !visited[freeNode])
			{
		
				std::string color = freeNode.get()->getColorString();
				if (colorCount.find(color) == colorCount.end())
				{
					colorCount[color] = 1;
				}
				else
				{
					colorCount[color]++;
				}
				lookForAdjWithSameColor(visited, colorCount, freeNode);
				
				visited[freeNode] = true;
			}
			visitedIndex++;
		}
	}
	std::string mostFrequentColor;
	int maxCount = 0;

	for (const auto& entry : colorCount)
	{
		if (entry.second > maxCount && entry.first != m_playerCurColor)
		{
			mostFrequentColor = entry.first;
			maxCount = entry.second;
		}
	}

	m_NPCcurColor = mostFrequentColor;
}