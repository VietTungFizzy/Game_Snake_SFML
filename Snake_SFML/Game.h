#pragma once
#include"World.h"
#include"Window.h"
#include"TextBox.h"
class Game
{
public:
	Game();
	~Game();
	void HandleInput();
	void Update();
	void Render();
	Window * GetWindow();

	sf::Time GetElapsedTime();
	void RestartClock();

private:

	sf::Clock m_Clock;
	sf::Time m_ElapsedTime;
	Window m_Window;
	TextBox m_TextBox;

	World m_World;
	Snake m_Snake;
};

