#include "Game.h"

//Initializations
void Game::CreateWindow()
{
	p_Window = new RenderWindow(m_ScreenSize,"Connect 4");
	p_Window->setFramerateLimit(30);
}

//Update
void Game::UpdateEvents()
{
	Event event;
	while (p_Window->pollEvent(event))
	{
		//Window closed Event
		if (event.type == Event::Closed 
			|| Keyboard::isKeyPressed(Keyboard::Escape))
		{
			p_Window->close();
		}

		// Mouse clicked Event
		if (event.type == Event::MouseButtonPressed
			&& !m_GameOver)
		{
			if (event.key.code == Mouse::Left)
			{
				m_GameOver = p_Board->PlayMove(Mouse::getPosition(*p_Window));
			}
		}
	}
}

void Game::UpdateAll()
{
	UpdateEvents();
}

//Render
void Game::RenderAll()
{
	p_Window->clear(Color(30,30,30,255));

	//All draws here
	p_Board->Render(p_Window);

	p_Window->display();
}

//Constructor and Destructor
Game::Game()
{
	p_Board = new Board();
	
	m_ScreenSize.height = p_Board->GetBoardSize().x;
	m_ScreenSize.width = p_Board->GetBoardSize().y;
	CreateWindow();

	m_GameOver = false;
}

Game::~Game()
{
	delete p_Board;
	delete p_Window;
}

//game LOOP
void Game::Run()
{
	while (p_Window->isOpen())
	{
		UpdateAll();
		RenderAll();
	}
}
