#pragma once
#include<SFML/Graphics.hpp>

using MessageContainer = std::vector<std::string>;

class TextBox
{
public:
	TextBox();
	TextBox(int l_Visible, int l_CharSize, int l_Width, sf::Vector2f l_ScreenPos);
	~TextBox();

	void Setup(int l_Visible, int l_CharSize, int l_Width, sf::Vector2f l_ScreenPos);
	void Add(std::string l_Message);
	void Clear();

	void Render(sf::RenderWindow & l_Wind);

private:
	MessageContainer m_Message;
	int m_NumVisible;

	sf::RectangleShape m_Backdrop;
	sf::Font m_Font;
	sf::Text m_Content;
};

