#include "Snake.h"

Snake::Snake(int l_BlockSize)
{
	m_Size = l_BlockSize;
	m_BodyRect.setSize(sf::Vector2f(m_Size - 1, m_Size - 1));
	Reset();
}

Snake::~Snake()
{
}

int Snake::GetSpeed()
{
	return m_Speed;
}

sf::Vector2i Snake::GetPosition()
{
	return (!m_SnakeBody.empty() ? m_SnakeBody.front().position : sf::Vector2i(1,1));
}

int Snake::GetLives()
{
	return m_Lives;
}

int Snake::GetScore()
{
	return m_Scores;
}

void Snake::IncreaseScore()
{
	m_Scores += 10;
}

bool Snake::HasLost()
{
	return m_Lost;
}

Direction Snake::GetPhysicalDirection()
{
	if (m_SnakeBody.size() <= 1)
	{
		return Direction::None;
	}

	SnakeSegment &Head = m_SnakeBody[0];
	SnakeSegment &Neck = m_SnakeBody[1];

	if (Head.position.x == Neck.position.x)
	{
		return (Head.position.y > Neck.position.y ? Direction::Down : Direction::Up);
	}
	else if (Head.position.y == Neck.position.y)
	{
		return (Head.position.x > Neck.position.x ? Direction::Right : Direction::Left);
	}

	return Direction::None;
}

void Snake::SetDirection(Direction direction)
{
	m_Dir = direction;
}

void Snake::Lose()
{
	m_Lost = true;
}

void Snake::ToggleLost()
{
	m_Lost = !m_Lost;
}

void Snake::Extend()
{
	if (m_SnakeBody.empty()) { return; }
	SnakeSegment & tail_head = m_SnakeBody[m_SnakeBody.size() - 1];

	if (m_SnakeBody.size() > 1)
	{
		SnakeSegment & tail_bone = m_SnakeBody[m_SnakeBody.size() - 2];
		if (tail_head.position.x == tail_bone.position.x)
		{
			if (tail_head.position.y > tail_bone.position.y)
				m_SnakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
			else
				m_SnakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
		}
		else
		{
			if (tail_head.position.y == tail_bone.position.y)
			{
				if (tail_head.position.x > tail_bone.position.x)
				{
					m_SnakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y ));
				}
				else
				{
					m_SnakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
				}
			}
		}
	}
	else
	{
		switch (m_Dir)
		{
		case Direction::Up:
		{
			m_SnakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
		}break;
		case Direction::Down:
		{
			m_SnakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
		}break;
		case Direction::Left:
		{
			m_SnakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
		}break;
		case Direction::Right:
		{
			m_SnakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
		}break;
		default:
			break;
		}
	}
	
}

void Snake::Reset()
{
	m_SnakeBody.clear();

	m_SnakeBody.push_back(SnakeSegment(5, 7));
	m_SnakeBody.push_back(SnakeSegment(5, 6));
	m_SnakeBody.push_back(SnakeSegment(5, 5));

	m_Dir = Direction::None;
	m_Speed = 15;
	m_Lives = 3;
	m_Scores = 0;
	m_Lost = false;
}

void Snake::Move()
{
	for (int i = m_SnakeBody.size() -1; i > 0 ; i--)
	{
		m_SnakeBody[i].position = m_SnakeBody[i - 1].position;
	}

	switch (m_Dir)
	{
	case Direction::Up:
	{
		--m_SnakeBody[0].position.y;
	}break;
	case Direction::Down:
		++m_SnakeBody[0].position.y;
	{
	}break;
	case Direction::Left:
	{
		--m_SnakeBody[0].position.x; 
	}break;
	case Direction::Right:
	{
		++m_SnakeBody[0].position.x;
	}	break;
	default:
		break;
	}
}

void Snake::Tick()
{
	if (m_SnakeBody.empty()) return;
	if (m_Dir == Direction::None) return;

	Move();
	CheckCollision();
}

void Snake::Cut(int l_Segments)
{
	for (int i = 0; i < l_Segments; i++)
	{
		m_SnakeBody.pop_back();
	}
	--m_Lives;

	if (!m_Lives)
	{
		Lose();
		return;
	}
}

void Snake::Render(sf::RenderWindow & l_Window)
{
	if (m_SnakeBody.empty()) return;

	auto head = m_SnakeBody.begin();
	m_BodyRect.setFillColor(sf::Color::Yellow);
	m_BodyRect.setPosition(head->position.x * m_Size, head->position.y * m_Size);
	l_Window.draw(m_BodyRect);

	m_BodyRect.setFillColor(sf::Color::Green);
	for (auto i = m_SnakeBody.begin() + 1; i != m_SnakeBody.end(); i++)
	{
		m_BodyRect.setPosition(i->position.x * m_Size, i->position.y * m_Size);
		l_Window.draw(m_BodyRect);
	}
}

void Snake::CheckCollision()
{
	if (m_SnakeBody.size() < 5) return;

	SnakeSegment &head = m_SnakeBody.front();
	for (auto i = m_SnakeBody.begin() + 1; i !=  m_SnakeBody.end(); i++)
	{
		if (i->position == head.position)
		{
			int segments = m_SnakeBody.end() - i;
			Cut(segments);
			break;
		}
	}
}
