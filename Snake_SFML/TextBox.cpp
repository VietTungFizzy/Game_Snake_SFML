#include "TextBox.h"

TextBox::TextBox()
{
	Setup(5, 9, 200, sf::Vector2f(0, 0));
}

TextBox::TextBox(int l_Visible, int l_CharSize, int l_Width, sf::Vector2f l_ScreenPos)
{
	Setup(l_Visible, l_CharSize, l_Width, l_ScreenPos);
}


TextBox::~TextBox()
{
}

void TextBox::Setup(int l_Visible, int l_CharSize, int l_Width, sf::Vector2f l_ScreenPos)
{
	m_NumVisible = l_Visible;

	sf::Vector2f l_Offset(2.0f, 2.0f);
	m_Font.loadFromFile("Lora.ttf");

	m_Content.setFont(m_Font);
	m_Content.setString("");
	m_Content.setCharacterSize(l_CharSize);
	m_Content.setFillColor(sf::Color::White);
	m_Content.setPosition(l_ScreenPos + l_Offset);

	m_Backdrop.setSize(sf::Vector2f(l_Width, l_Visible * (l_CharSize * 1.2f)));
	m_Backdrop.setFillColor(sf::Color(90, 90, 90, 90));
	m_Backdrop.setPosition(l_ScreenPos);
}

void TextBox::Add(std::string l_Message)
{
	m_Message.push_back(l_Message);
	if (m_Message.size() < 6) return;
	m_Message.erase(m_Message.begin());
}

void TextBox::Clear()
{
	m_Message.clear();
}

void TextBox::Render(sf::RenderWindow & l_Wind)
{
	std::string l_Content;
	for (auto & i : m_Message)
	{
		l_Content.append(i + "\n");
	}

	if (l_Content != "")
	{
		m_Content.setString(l_Content);
		l_Wind.draw(m_Backdrop);
		l_Wind.draw(m_Content);
	}
}
