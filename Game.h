#pragma once



#include "Board.h"

using namespace sf;

class Game
{
private:
//Variables
	//Window settings
	RenderWindow* p_Window;
	VideoMode m_ScreenSize;

	//GameObject
	Board* p_Board;

	//gameOverCheck
	bool m_GameOver;

//Functions

	//Initializations
	void CreateWindow();

	//Update
	void UpdateEvents();
	void UpdateAll();

	//Render
	void RenderAll();

public:
	//Constructor and destructor
	Game();
	virtual ~Game();

	//game LOOP
	void Run();

};

