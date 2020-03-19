#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
struct SnakeSegment
{
	SnakeSegment(int x, int y) { position.x = x; position.y = y; }
	sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;
enum class Direction {None, Up, Down, Left, Right };

class Snake
{

public:

	Snake(int l_BlockSize);
	~Snake();

	//Helper Methods
	int GetSpeed();
	sf::Vector2i GetPosition();
	int GetLives();
	int GetScore();
	void IncreaseScore();
	bool HasLost();
	Direction GetPhysicalDirection();
	void SetDirection(Direction direction);

	void Lose();
	void ToggleLost();

	void Extend();
	void Reset(); //Reset to starting position

	void Move(); 
	void Tick(); //Update method
	void Cut(int l_Segments); //Method for cutting snake
	void Render(sf::RenderWindow &l_Window);

private:
	void CheckCollision();

private:
	SnakeContainer m_SnakeBody;
	Direction m_Dir;
	int m_Size;
	int m_Speed;
	int m_Lives;
	int m_Scores;
	bool m_Lost;
	sf::RectangleShape m_BodyRect; //Shape use is Rendering
};

