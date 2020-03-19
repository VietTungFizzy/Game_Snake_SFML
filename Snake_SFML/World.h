#pragma once
#include"Snake.h"
#include"TextBox.h"
class World
{
public:
	World(sf::Vector2u l_WindSize);
	~World();

	int GetBlockSize();
	
	void RespawnApple();

	void Update(Snake & l_Player, TextBox & l_TextBox);
	void Render(sf::RenderWindow & l_Window);

private:
	sf::Vector2u m_WindowSize;
	sf::Vector2i m_Item;
	int m_BlockSize;

	sf::CircleShape m_AppleShape;
	sf::RectangleShape m_Bounds[4];


};

