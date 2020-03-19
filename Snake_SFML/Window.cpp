#include "Window.h"
Window::Window()
{
	Setup("Window", sf::Vector2u(640, 480));
}

Window::Window(const std::string & title, const sf::Vector2u & size)
{
	Setup(title, size);
}


Window::~Window()
{
	Destroy();
}

void Window::BeginDraw()
{
	m_Window.clear(sf::Color::Black);
}

void Window::EndDraw()
{
	m_Window.display();
}

void Window::Update()
{
	sf::Event Event;
	while (m_Window.pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
		{
			m_isDone = true;
		}
		else if (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::F5)
		{
			ToggleFullScreen();
		}

		
	}
}

bool Window::isDone()
{
	return m_isDone;
}

bool Window::isFullScreen()
{
	return m_isFullScreen;
}

sf::Vector2u Window::GetWindowSize()
{
	return m_WindowSize;
}

sf::RenderWindow * Window::GetWindowRender()
{
	return &m_Window;
}

void Window::ToggleFullScreen()
{
	m_isFullScreen = true;
	Destroy();
	Create();
}

void Window::Draw(sf::Drawable & DrawableObj)
{
	m_Window.draw(DrawableObj);
}

void Window::Setup(const std::string & title, const sf::Vector2u & size)
{
	m_WindowTitle = title;
	m_WindowSize = size;
	m_isFullScreen = false;
	m_isDone = false;
	Create();
}

void Window::Destroy()
{
	m_Window.close();
}

void Window::Create()
{
	auto Style = m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default;
	sf::VideoMode VideoMode(m_WindowSize.x, m_WindowSize.y, 32);
	m_Window.create(VideoMode, m_WindowTitle, Style);
}
