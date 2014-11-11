// Library Includes
#include <locale>
#include <codecvt>
#include <algorithm>
// Local Includes
#include "Game.h"
#include "resource.h"
#include "utils.h"
#include "backbuffer.h"
#include "Deck.h"
#include "Column.h"
#include "Home.h"
// This Include
#include "Level.h"
// Static Variables

// Static Function Prototypes

// Implementation

#define CHEAT_BOUNCE_ON_BACK_WALL

CLevel::CLevel()
: m_pDeck(0)
, m_iWidth(0)
, m_iHeight(0)
, m_bMouseDown(false){}

CLevel::~CLevel()
{
	/*
	while (m_vecBricks.size() > 0)
	{
		CBrick* pBrick = m_vecBricks[m_vecBricks.size() - 1];
		m_vecBricks.pop_back();
		delete pBrick;
	}
	delete m_pPaddle;
	m_pPaddle = 0;
	delete m_pBall;
	m_pBall = 0;
	*/
}

bool CLevel::Initialise(int _iWidth, int _iHeight)
{
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	const float fBallVelX = 200.0f;
	const float fBallVelY = 75.0f;

	m_pDeck = new CDeck();
	VALIDATE(m_pDeck->Initialise(0, 4));
	m_pDeck->SetX(40);
	m_pDeck->SetY(40);

	CCard* _TempCard;
	CColumn* _TempColumn;

	//Initialise the cards here
	
	//Create a card of each face and suit
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			_TempCard = new CCard(j, i);
			_TempCard->Initialise(j, i);
			m_pDeck->m_pDeck.push_back(_TempCard);
		}
	}

	//Create each column
	for(int i=0; i<7; i++)
	{
		_TempColumn = new CColumn();
		_TempColumn->Initialise(0,5);
		m_pColumns.push_back(_TempColumn);
		_TempColumn->SetX(40 + (i * 165));
		_TempColumn->SetY(300);
	}
	//Shuffle the cards in the deck
	std::random_shuffle(m_pDeck->m_pDeck.begin(), m_pDeck->m_pDeck.end());


	for(int i = 0; i < 7; i++)
	{
		//deal cards into the columns
		for(int j=0; j < i+1; j++)
		{
			_TempCard = m_pDeck->m_pDeck.back();
			m_pDeck->m_pDeck.pop_back();
			m_pColumns[i]->m_pPile.push_back(_TempCard);
			if(j == i)
			{
				_TempCard->SetFaceUp(true);
			}
			else
			{
				_TempCard->SetFaceUp(false);
			}
		}
	}

	CHome* _TempHome;
	//Create each Ace Pile
	for(int i = 0; i < 4; i++)
	{
		_TempHome = new CHome();
		_TempHome->Initialise(6, 4);
		m_pAceHomes.push_back(_TempHome);
		_TempHome->SetX(150 + (i * 165));
		_TempHome->SetY(40);
	}

	/*
	m_pPaddle = new CPaddle();
	VALIDATE(m_pPaddle->Initialise());

	// Set the paddle's position to be centered on the x,
	// and a little bit up from the bottom of the window.
	m_pPaddle->SetX(_iWidth / 2.0f);
	m_pPaddle->SetY(_iHeight - ( 4 * m_pPaddle->GetHeight()));

	const int kiNumBricks = 36;
	const int kiStartX = 20;
	const int kiGap = 5;

	int iCurrentX = kiStartX;
	int iCurrentY = kiStartX;

	for (int i = 0; i < kiNumBricks; ++i)
	{
		CBrick* pBrick = new CBrick();
		VALIDATE(pBrick->Initialise());
		pBrick->SetX(static_cast<float>(iCurrentX));
		pBrick->SetY(static_cast<float>(iCurrentY));
		iCurrentX += static_cast<int>(pBrick->GetWidth()) + kiGap;
		if (iCurrentX > _iWidth)
		{
			iCurrentX = kiStartX;
			iCurrentY += 20;
		}
		m_vecBricks.push_back(pBrick);
	}
	SetBricksRemaining(kiNumBricks);
	*/
	return (true);
}

void CLevel::Draw()
{
	/*
	for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
	{
		m_vecBricks[i]->Draw();
	}
	m_pPaddle->Draw();
	m_pBall->Draw();
	DrawScore();
	*/
	m_pDeck->Draw();
	// Draw the columns
	for(int i=0; i<7; i++)
	{
		m_pColumns[i]->Draw();
	}
	// Draw the Ace Homes
	for(int i=4; i<4; i++)
	{
		m_pAceHomes[i]->Draw();
	}

	if(!m_pDraggedCards.empty())
	{
		for(int i=m_pDraggedCards.size()-1; i>=0; i--)
		{
			m_pDraggedCards[i]->Draw();
		}
	}
}

void CLevel::Process(float _fDeltaTick)
{
	if(m_bMouseDown)
	{
		HandleMouseDrag();
	}
	ProcessCheckForWin();

	m_pDeck->Process(_fDeltaTick);

	for (int i = 0; i < 7; i++)
	{
		m_pColumns[i]->Process(_fDeltaTick);
	}

	for (int j = 0; j < 4; j++)
	{
		m_pAceHomes[j]->Process(_fDeltaTick);
	}

	for(unsigned int i=0; i<m_pDraggedCards.size(); i++)
	{
		m_pDraggedCards[i]->SetX(m_fMouseX - (CARD_WIDTH / 2));
		m_pDraggedCards[i]->SetY(m_fMouseY - 29 + (m_pDraggedCards.size() -1 - i) * 58);
		m_pDraggedCards[i]->Process(_fDeltaTick);
	}
	//for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
	//{
	//	m_vecBricks[i]->Process(_fDeltaTick);
	//}

	//m_pPaddle->Process(_fDeltaTick);
	//m_pBall->Process(_fDeltaTick);
}

void CLevel::ProcessCheckForWin()
{
	//for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
	//{
	//	if (!m_vecBricks[i]->IsHit())
	//	{
	//		return;
	//	}
	//}
	//CGame::GetInstance().GameOverWon();
}

void CLevel::HandleMouseDrag()
{

	//Iterate through all columns
	//if top card
		//See if the mouse is within the bounds of the top card
//	MessageBox(0, L"Mouse is being dragged", L"Debug", MB_OK);
	if(m_pDraggedCards.empty())
	{
		for(int i=0; i<7; i++)
		{
			for(unsigned int j=0; j<m_pColumns[i]->m_pPile.size()-1; j++)
			{
				//Get current card's X and Y
				int _CardX = m_pColumns[i]->m_pPile[j]->GetX();
				int _CardY = m_pColumns[i]->m_pPile[j]->GetY();

				//Make sure the card is face up 
				if(m_pColumns[i]->m_pPile[j]->GetFaceUp())
				{
					//See if the mouse is within the cards's bounds (only the showing part)
					if((m_fMouseX >= _CardX) && (m_fMouseX < _CardX+CARD_WIDTH)
					&& (m_fMouseY >= _CardY) && (m_fMouseY < _CardY+58))
					{
						//Iterate through the cards beneath, adding them to the dragging vector
						for(unsigned int k = j; k<m_pColumns[i]->m_pPile.size(); k++)
						{
							m_pColumns[i]->m_pPile[k]->SetDragged(true);
							m_pDraggedCards.insert(m_pDraggedCards.begin(), m_pColumns[i]->m_pPile[k]);
						}
					
						//Remove the cards that are being dragged
						m_pColumns[i]->m_pPile.erase(m_pColumns[i]->m_pPile.begin() + j, m_pColumns[i]->m_pPile.end());
						m_iDraggedCardsLastColumn = i;
						return;
					}
				}
			}
			int _FrontCardX = m_pColumns[i]->GetTopCard()->GetX();
			int _FrontCardY = m_pColumns[i]->GetTopCard()->GetY();
			if((m_fMouseX >= _FrontCardX) && (m_fMouseX < _FrontCardX+CARD_WIDTH)
				&& (m_fMouseY >= _FrontCardY) && (m_fMouseY < _FrontCardY+CARD_HEIGHT))
			{
				//MessageBox(0, L"Mouse is being dragged", L"Debug", MB_OK);

				m_pColumns[i]->GetTopCard()->SetDragged(true);
				//m_pDraggedCards.insert(m_pDraggedCards.begin(), m_pColumns[i]->GetTopCard());
				m_pDraggedCards.push_back(m_pColumns[i]->m_pPile.back());
				m_pColumns[i]->m_pPile.pop_back();
				m_iDraggedCardsLastColumn = i;
				return;
			
			}

		}
	}
}

void CLevel::DrawScore()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();
	const int kiX = 0;
	const int kiY = m_iHeight - 50;
	
	TextOut(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
}

void CLevel::SetMouseCoords(int _x, int _y)
{
	m_fMouseX = _x;
	m_fMouseY = _y;
}


void CLevel::UpdateScoreText()
{
	//std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	//m_strScore = L"Bricks Remaining: ";
	//m_strScore += converter.from_bytes(ToString(GetBricksRemaining()));
}

void CLevel::SetMouseDown(bool _bMouseDown)
{
	m_bMouseDown = _bMouseDown;
}