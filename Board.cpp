#include "Board.h"

//Initializations
void Board::InitSlot()
{
	m_SlotTexture.loadFromFile("images/slot.png");
	m_Slot.setTexture(m_SlotTexture);
	
	m_SlotScale = 1.f/2.f;
	m_SlotSize = 256 * m_SlotScale;
	m_Slot.setScale(m_SlotScale, m_SlotScale);
	
	//Light Blue shade
	m_SlotColor = Color(0, 160, 255, 255);
	m_Slot.setColor(m_SlotColor);
}

void Board::InitBoard()
{
	m_BoardSize = Vector2i(6, 7);
	m_Coin.SetOffset(m_SlotSize/9.f);
}

void Board::InitCoins()
{
	m_CoinCount = 0;
	m_Coins = new CoinType*[m_BoardSize.x];
	for (int i = 0; i < m_BoardSize.x; i++)
	{
		m_Coins[i] = new CoinType[m_BoardSize.y];
	}

	for (int i = 0; i < m_BoardSize.x; i++)
	{
		for (int j = 0; j < m_BoardSize.y; j++)
		{
			m_Coins[i][j] = CoinType::None;
		}
	}
}

void Board::InitGameOverText()
{
	m_GameOverFont.loadFromFile("fonts/kenvector_future.ttf");
	m_GameOverText.setFont(m_GameOverFont);
	m_GameOverText.setString("");
	m_GameOverText.setCharacterSize(50);
	ReCenterText();
}

//Constructor and destructor
Board::Board()
{
	InitSlot();
	InitBoard();
	InitCoins();
	InitGameOverText();
}

Board::~Board()
{
	for (int i = 0; i < m_BoardSize.y; i++)
	{
		delete[] m_Coins[i];
	}
	delete[] m_Coins;
}

//Getter
Vector2f Board::GetBoardSize()
{
	return Vector2f(m_BoardSize.y * m_SlotSize, m_BoardSize.x * m_SlotSize);
}

CoinType Board::GetTurnType()
{
	return (m_IsRedTurn) ? (CoinType::Red) : (CoinType::Yellow);
}

//Functions
bool Board::PlayMove(Vector2i mousePos)
{
	// convert mousePosition to slot position
	int x = mousePos.x / m_SlotSize;
	int y;
	if (FreeSlotAvailable(x))
	{
		y = GetFreeSlot(x);
		m_Coins[x][y] = GetTurnType();
		m_CoinCount++;
		if (GameOver(x,y) || Draw())
		{
			return true;
		}

		m_IsRedTurn = !m_IsRedTurn;
	}

	return false;
}

bool Board::CheckCoinType(int x, int y)
{
	if (x >= m_BoardSize.x
		|| y >= m_BoardSize.y
		|| x < 0
		|| y < 0)
	{
		return false;
	}
	return m_Coins[x][y] == GetTurnType();
}

bool Board::CheckVertical(int x, int y)
{
	int count = 1;
	bool top, down;
	top = down = true;
	// Vertical Search
	for (int i = 1; i <= 4; i++)
	{
		if (CheckCoinType(x, y - i) && top)
			count++;
		else
			top = false;

		if (CheckCoinType(x, y + i) && down)
			count++;
		else
			down = false;

		if (!top && !down)
			break;
	}

	return count >= 4;
}

void Board::ReCenterText()
{
	m_GameOverText.setOrigin(m_GameOverText.getGlobalBounds().width / 2,
		m_GameOverText.getGlobalBounds().height);
	m_GameOverText.setPosition(GetBoardSize().y / 2, GetBoardSize().x / 2);
}

bool Board::CheckHorizontal(int x, int y)
{
	int count = 1;
	bool right, left;
	right = left = true;
	// Horizontal Search
	for (int i = 1; i <= 4; i++)
	{
		if (CheckCoinType(x + i, y) && right)
			count++;
		else
			right = false;

		if (CheckCoinType(x - i, y) && left)
			count++;
		else
			left = false;

		if (!right && !left)
			break;
	}

	return count >= 4;
}

bool Board::CheckDiagonal(int x, int y)
{
	int count = 1;
	bool right, left;
	right = left = true;
	// Left Horizontal Search
	for (int i = 1; i <= 4; i++)
	{
		if (CheckCoinType(x + i, y + i) && right)
			count++;
		else
			right = false;

		if (CheckCoinType(x - i, y - i) && left)
			count++;
		else
			left = false;

		if (!right && !left)
			break;
	}

	if (count >= 4)
		return true;

	count = 1;
	right = left = true;
	// right Horizontal Search
	for (int i = 1; i <= 4; i++)
	{
		if (CheckCoinType(x + i, y - i) && right)
			count++;
		else
			right = false;

		if (CheckCoinType(x - i, y + i) && left)
			count++;
		else
			left = false;

		if (!right && !left)
			break;
	}

	return count >= 4;
}

bool Board::GameOver(int x, int y)
{
	if (CheckVertical(x, y) ||
		CheckHorizontal(x, y) ||
		CheckDiagonal(x, y))
	{
		m_GameOverText.setString(m_IsRedTurn ? "Red Wins" : "Yellow Wins");
		ReCenterText();
		return true;
	}
	return false;
}

bool Board::Draw()
{
	if (IsBoardFull())
	{
		m_GameOverText.setString("DRAW");
		ReCenterText();
		return true;
	}
	return false;
}

bool Board::IsBoardFull()
{
	return m_CoinCount == (m_BoardSize.x * m_BoardSize.y);
}

bool Board::FreeSlotAvailable(int x)
{
	return m_Coins[x][0] == CoinType::None;
}

int Board::GetFreeSlot(int x)
{
	for (int i = m_BoardSize.y-1; i >= 0; i--)
	{
		if (m_Coins[x][i] == CoinType::None)
			return i;
	}
}

//Render
void Board::RenderBoard(RenderWindow* window)
{
	for (int i = 0; i < m_BoardSize.x; i++)
	{
		for (int j = 0; j < m_BoardSize.y; j++)
		{
			//Render Board
			m_Slot.setPosition(i * m_SlotSize, j *m_SlotSize);
			window->draw(m_Slot);

			//Render Coins
			m_Coin.SetType(m_Coins[i][j]);
			m_Coin.SetPosition(i * m_SlotSize, j * m_SlotSize);
			window->draw(m_Coin.GetSprite());
		}
	}
}

void Board::Render(RenderWindow* window)
{
	RenderBoard(window);
	window->draw(m_GameOverText);
}
