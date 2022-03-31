#pragma once

#include <iostream>
#include <map>
#include "Coin.h"

using namespace sf;

class Board
{
private:
//Variables
	//Slot settings
	Texture m_SlotTexture;
	Sprite m_Slot;
	Color m_SlotColor;
	float m_SlotSize;
	float m_SlotScale;

	//Board Setting
	Vector2i m_BoardSize ;

	//Coin
	int m_CoinCount;
	CoinType** m_Coins;
	Coin m_Coin;

	//Turn
	bool m_IsRedTurn = true;

	//GameOver
	Font m_GameOverFont;
	Text m_GameOverText;

	//Initializations
	void InitSlot();
	void InitBoard();
	void InitCoins();
	void InitGameOverText();

public:
	//Constructor and destructor
	Board();
	virtual ~Board();
	
	//Getter
	Vector2f GetBoardSize();
	CoinType GetTurnType();

	//gameOverText
	void ReCenterText();

	//Checking
	bool CheckVertical(int x, int y);
	bool CheckHorizontal(int x, int y);
	bool CheckDiagonal(int x, int y);
	
	//Functions
	bool PlayMove(Vector2i mousePos);
	bool CheckCoinType(int x,int y);
	bool GameOver(int x, int y);
	bool Draw();
	bool IsBoardFull();
	bool FreeSlotAvailable(int x);
	int GetFreeSlot(int x);

	//Render
	void RenderBoard(RenderWindow* window);
	void Render(RenderWindow* window);

};

