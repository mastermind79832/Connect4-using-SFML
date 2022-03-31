#include "Coin.h"

Coin::Coin()
{
	m_Texture.loadFromFile("images/Coin.png");
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setScale(1.5f,1.5f);
	m_Type = CoinType::None;
	SetColor();
}

Coin::~Coin()
{
}

//Setter
void Coin::SetColor()
{
	if (m_Type == CoinType::Red)
	{
		//pinkish red color
		m_Sprite.setColor(Color(255, 80, 0, 255));
	}
	else if (m_Type == CoinType::Yellow)
	{
		//yellow color
		m_Sprite.setColor(Color(255, 200, 0, 255));
	}
	else
	{
		//White Color
		m_Sprite.setColor(Color(255, 255, 255, 0));
	}
}

void Coin::SetType(CoinType type)
{
	m_Type = type;
	SetColor();
}

void Coin::SetOffset(float value)
{
	m_Offset = value;
}

void Coin::SetPosition(float x, float y)
{
	m_Sprite.setPosition(x + m_Offset, y + m_Offset);
}

//Getter
CoinType Coin::GetType()
{
	return m_Type;
}

Sprite Coin::GetSprite()
{
	return m_Sprite;
}

