#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

enum class CoinType
{
	None = 0,
	Red = 1,
	Yellow = 2
};

class Coin
{
private:
	//Variables
	Texture m_Texture;
	Sprite m_Sprite;

	CoinType m_Type;
	
	float m_Offset;
	
	//Setter
	void SetColor();
public:
	//Constructor and destructor
	Coin();
	virtual ~Coin();
	
	//Setter
	void SetType(CoinType type);
	void SetOffset(float value);
	void SetPosition(float x,float y);

	//Getter
	CoinType GetType();
	Sprite GetSprite();
};

