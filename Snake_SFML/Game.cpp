#include "Game.h"

Game::Game() : m_Window("Snake", sf::Vector2u(800, 600)) , 
				m_Snake(m_World.GetBlockSize()), m_World(sf::Vector2u(800, 600))
{
	m_TextBox.Setup(5, 14, 350, sf::Vector2f(225, 0));
	m_TextBox.Add("Seeded random number generator with: " + std::to_string(time(0)));


}


Game::~Game()
{
}

void Game::HandleInput()
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_Snake.GetPhysicalDirection() != Direction::Down)
	{
		m_Snake.SetDirection(Direction::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_Snake.GetPhysicalDirection() != Direction::Up)
	{
		m_Snake.SetDirection(Direction::Down);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_Snake.GetPhysicalDirection() != Direction::Right)
	{
		m_Snake.SetDirection(Direction::Left);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_Snake.GetPhysicalDirection() != Direction::Left)
	{
		m_Snake.SetDirection(Direction::Right);
	}
}

Window * Game::GetWindow()
{
	return &m_Window;
}

sf::Time Game::GetElapsedTime()
{
	return m_ElapsedTime;
}

void Game::RestartClock()
{
	m_ElapsedTime += m_Clock.restart();

}

void Game::Update()
{
	float SnakeSpeed = m_Snake.GetSpeed();
	float TimeStep = 1.0f / SnakeSpeed;


	if (m_ElapsedTime.asSeconds() >= TimeStep)
	{
		m_Snake.Tick();
		m_World.Update(m_Snake, m_TextBox);
		
		m_ElapsedTime -= sf::seconds(TimeStep);
		if (m_Snake.HasLost())
		{
			m_Snake.Reset();
		}
	}

}

void Game::Render()
{
	m_Window.BeginDraw();

	m_World.Render(*m_Window.GetWindowRender());
	m_Snake.Render(*m_Window.GetWindowRender());
	m_TextBox.Render(*m_Window.GetWindowRender());
	
	m_Window.EndDraw();
}
