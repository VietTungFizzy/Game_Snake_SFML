#include "World.h"

World::World(sf::Vector2u l_WindSize)
{
	m_BlockSize = 16;
	m_WindowSize = l_WindSize;
	RespawnApple();
	m_AppleShape.setFillColor(sf::Color::Red);
	m_AppleShape.setRadius(m_BlockSize / 2);

	for (int i = 0; i < 4; i++)
	{
		m_Bounds[i].setFillColor(sf::Color(150, 0, 0));
		if (!((i + 1) % 2))
		{
			m_Bounds[i].setSize(sf::Vector2f(m_WindowSize.x, m_BlockSize));
		}
		else
		{
			m_Bounds[i].setSize(sf::Vector2f( m_BlockSize, m_WindowSize.y));
		}
		if (i < 2)
		{
			m_Bounds[i].setPosition(0, 0);
		}
		else
		{
			m_Bounds[i].setOrigin(m_Bounds[i].getSize());
			m_Bounds[i].setPosition(sf::Vector2f(m_WindowSize));
		}
	}

}

World::~World()
{
}

int World::GetBlockSize()
{
	return m_BlockSize;
}

void World::RespawnApple()
{
	int MaxX = (m_WindowSize.x / m_BlockSize) - 2;
	int MaxY = (m_WindowSize.y / m_BlockSize) - 2;
	
	m_Item = sf::Vector2i(rand() % MaxX + 1, rand() % MaxY + 1);
	m_AppleShape.setPosition(m_Item.x * m_BlockSize, m_Item.y * m_BlockSize);


}

void World::Update(Snake & l_Player,TextBox & l_TextBox)
{
	if (l_Player.GetPosition() == m_Item)
	{
		l_Player.Extend();
		l_Player.IncreaseScore();
		RespawnApple();
		l_TextBox.Add("You ate an apple. Score: " + std::to_string(l_Player.GetScore()));
	}

	int GridSize_X = m_WindowSize.x / m_BlockSize;
	int GridSize_Y = m_WindowSize.y / m_BlockSize;
	
	sf::Vector2i PlayerPosition = l_Player.GetPosition();
	if (PlayerPosition.x <= 0 || PlayerPosition.y <= 0 ||
		PlayerPosition.x >= GridSize_X - 1 || PlayerPosition.y >= GridSize_Y - 1)
	{
		l_Player.Lose();
		l_TextBox.Add("Game Over! Score: " + std::to_string(l_Player.GetScore()));
	}
}

void World::Render(sf::RenderWindow & l_Window)
{
	for (int i = 0; i < 4; i++)
	{
		l_Window.draw(m_Bounds[i]);
	}
	l_Window.draw(m_AppleShape);
}
