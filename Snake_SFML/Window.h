#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
class Window
{
public:
	Window();
	Window(const std::string & title, const sf::Vector2u & size);
	~Window();

	void BeginDraw();
	void EndDraw();
	void Update();

	bool isDone();
	bool isFullScreen();
	sf::Vector2u GetWindowSize();
	sf::RenderWindow * GetWindowRender();

	void ToggleFullScreen();
	void Draw(sf::Drawable & DrawableObj);
private:
	void Setup(const std::string & title, const sf::Vector2u & size);
	void Destroy();
	void Create();

	sf::RenderWindow m_Window;
	sf::Vector2u m_WindowSize;
	std::string m_WindowTitle;
	bool m_isDone;
	bool m_isFullScreen;
};

