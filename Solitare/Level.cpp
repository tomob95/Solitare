//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: Level.cpp
// Description	: Implementation for the level class
// Author		: Tom O'Brien, Kelsey Scheurich, Tom Butler
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

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
#include "DrawPile.h"
#include "Column.h"

#include "Home.h"

// This Include
#include "Level.h"

// Implementation


#define CHEAT_BOUNCE_ON_BACK_WALL

/***********************

 * CLevel: Class constructor
 * @author: Kelsey Scheurich

 ********************/

CLevel::CLevel()
	: m_pDeck(0),	// Default all to 0
	  m_iWidth(0),
	  m_iHeight(0),
	  m_bMouseDown(false)
{
}

/***********************

 * ~CLevel: Class destructor
 * @author: 

 ********************/
CLevel::~CLevel()
{
}

/***********************

 * Initialise: Initialise level
 * @author: 
 * @parameter: int _iWidth, width of level
 *				int _iHeight, height of level

 ********************/
bool CLevel::Initialise(int _iWidth, int _iHeight)
{
	// Set width and height
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	m_iScore = 0;
	
	// Create new deck, set as member
	m_pDeck = new CDeck();
	m_pDraw = new CDrawPile();
	// Validate and intialise deck
	VALIDATE(m_pDeck->Initialise(0, 4));
	VALIDATE(m_pDraw->Initialise(6, 4));
	// Set deck x & y position
	m_pDeck->SetX(40);
	m_pDeck->SetY(40);
	m_pDraw->SetX(204);
	m_pDraw->SetY(40);

	// Create temp pointers for card, column and the home piles
	CCard* _TempCard;
	CColumn* _TempColumn;
	CHome* _TempHome;

	//Initialise the cards here
	
	//Create a card of each face and suit
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			// Create new card, initialise and add to deck
			_TempCard = new CCard(j, i);
			_TempCard->Initialise(j, i);
			m_pDeck->m_pDeck.push_back(_TempCard);
		}
	}

	//Create each column
	for(int i=0; i<7; i++)
	{
		// Create new column, initialise and set x & y
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
			// Set temp card to back of deck
			_TempCard = m_pDeck->m_pDeck.back();
			// Pop
			m_pDeck->m_pDeck.pop_back();
			// Push temp card to the column piles
			m_pColumns[i]->m_pPile.push_back(_TempCard);
			// If its the last card of the column
			if(j == i)
			{
				// Set as face up
				_TempCard->SetFaceUp(true);
			}
			else
			{
				// Set as face down
				_TempCard->SetFaceUp(false);
			}
		}
	}


	//Create each Ace Pile
	for(int i = 0; i < 4; i++)
	{
		_TempHome = new CHome();
		_TempHome->Initialise(6, 4);
		m_pAceHomes.push_back(_TempHome);
		_TempHome->SetX(535 + (i * 165));
		_TempHome->SetY(40);
		_TempHome->SetDrawX((2 + i) * CARD_WIDTH);
		_TempHome->SetDrawY(4 * CARD_HEIGHT);
	}

	return (true); 
}

/***********************

 * Draw: Draw cards
 * @author: 

 ********************/
void CLevel::Draw()
{
	// Call draw
	m_pDeck->Draw();
	m_pDraw->Draw();
	DrawScore();

	// Draw the columns
	for(int i=0; i<7; i++)
	{
		// Call draw
		m_pColumns[i]->Draw();
	}

	// Draw the Ace Homes
	for(int i=0; i<4; i++)
	{
		m_pAceHomes[i]->Draw();
	}


	// If the dragged cards pile is not empty

	if(!m_pDraggedCards.empty())
	{
		// For each card in the pile
		for(int i=m_pDraggedCards.size()-1; i>=0; i--)
		{
			// Call draw
			m_pDraggedCards[i]->Draw();
		}
	}
}

/***********************

 * Process: Process level
 * @author: 
 * @parameters: float _fDeltaTick, current delta tick value

 ********************/
void CLevel::Process(float _fDeltaTick)
{
	// If the mouse is down
	if(m_bMouseDown)
	{
		// If mouse is over deck
		if( ( m_fMouseX >= m_pDeck->GetX() ) && ( m_fMouseX < m_pDeck->GetX()+CARD_WIDTH )
			&& ( m_fMouseY >= m_pDeck->GetY() ) && ( m_fMouseY < m_pDeck->GetY()+CARD_HEIGHT ) )
		{
			// Call deck click function
			DeckClick();
		}
		else
		{
			// Start drag
			HandleMouseDrag();
		}
	}
	// Else if cards are being dragged
	else if (!m_pDraggedCards.empty())
	{
		HandleMouseDrop();
	}

	ProcessCheckForWin();

	//Process the deck
	m_pDeck->Process(_fDeltaTick);
	m_pDraw->Process( _fDeltaTick );

	//Process the columns

	// Check if game is over
	ProcessCheckForWin();

	// Call process recursively
	m_pDeck->Process(_fDeltaTick);
	
	// For each column
	for (int i = 0; i < 7; i++)
	{
		// Process
		m_pColumns[i]->Process(_fDeltaTick);
	}

	//For each home cell
	for (int j = 0; j < 4; j++)
	{
		if(m_pAceHomes[j]->IsEmpty())
		{
			m_pAceHomes[j]->SetDrawX((2 + j) * CARD_WIDTH);
			m_pAceHomes[j]->SetDrawY(4 * CARD_HEIGHT);
			m_pAceHomes[j]->Process(_fDeltaTick);
		}
		else
		{
			for(unsigned int i = 0; i<m_pAceHomes[j]->m_pHome.size(); i++)
			{
				m_pAceHomes[j]->m_pHome[i]->SetX(m_pAceHomes[j]->GetX());
				m_pAceHomes[j]->m_pHome[i]->SetY(m_pAceHomes[j]->GetY());
				m_pAceHomes[j]->m_pHome[i]->Process(_fDeltaTick);
			}
		};
	}

	//Process the cards that are being dragged
	// For each card being dragged
	for(unsigned int i=0; i<m_pDraggedCards.size(); i++)
	{
		// Update x & y pos
		m_pDraggedCards[i]->SetX(m_fMouseX - (CARD_WIDTH / 2));
		m_pDraggedCards[i]->SetY(m_fMouseY - 29 + (m_pDraggedCards.size() -1 - i) * 58);
		// Process
		m_pDraggedCards[i]->Process(_fDeltaTick);
	}
}

/***********************

 * ProcessCheckForWin: Check if game is over
 * @author: 

 ********************/
void CLevel::ProcessCheckForWin()
{
	//TODO: this (m_strScore)
}

/***********************

 * HandleMouseDrag: Function to handle dragging mouse
 * @author: 

 ********************/
void CLevel::HandleMouseDrag()
{

	//Make sure none of the cards are already being dragged
	if(m_pDraggedCards.empty())
	{
		// Iterate through all columns
		for(int i=0; i<7; i++)
		{
			//See if they have selected a stack of cards
			for(unsigned int j=0; j<m_pColumns[i]->m_pPile.size()-1; j++)
			{
				//Get clicked card's X and Y
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


			// Set int as x & y pos of top card in column
			int _FrontCardX = m_pColumns[i]->GetTopCard()->GetX();
			int _FrontCardY = m_pColumns[i]->GetTopCard()->GetY();

			// If mouse is within bounds
			if((m_fMouseX >= _FrontCardX) && (m_fMouseX < _FrontCardX+CARD_WIDTH)
				&& (m_fMouseY >= _FrontCardY) && (m_fMouseY < _FrontCardY+CARD_HEIGHT))
			{
				// Drag the card, add to dragged pile vector

				m_pColumns[i]->GetTopCard()->SetDragged(true);
				m_pDraggedCards.push_back(m_pColumns[i]->m_pPile.back());
				m_pColumns[i]->m_pPile.pop_back();
				m_iDraggedCardsLastColumn = i;

				return;
			
			}

		}
	}
}

void CLevel::HandleMouseDrop()
{
	int _iColumnX;
	int _iColumnY;
	//Go through all the columns and see if the mouse is on the column
	for(unsigned int i = 0; i < 7; i++)
	{
		//Get screen coords of front card of column
		if(!m_pColumns[i]->m_pPile.empty())
		{
			_iColumnX = m_pColumns[i]->GetTopCard()->GetX();
			_iColumnY = m_pColumns[i]->GetTopCard()->GetY();
		}
		else
		{
			//Get the coords of the placeholder sprite for the column
			_iColumnX = m_pColumns[i]->GetX();
			_iColumnY = m_pColumns[i]->GetY();
		}

		//Mouse is within the bounds of the front card
		if ((m_fMouseX >= _iColumnX) && (m_fMouseX < _iColumnX + CARD_WIDTH)
		&& (m_fMouseY >= _iColumnY - (CARD_HEIGHT / 2)) && (m_fMouseY < _iColumnY + CARD_HEIGHT))
		{
			//If there are cards in the column
			if(!m_pColumns[i]->IsEmpty())
			{
				if(CheckCardToColumn(m_pDraggedCards.front(), m_pColumns[i]->GetTopCard()))
				{
					//The cards are valid and need to be moved to the destination column
					for(unsigned int j=0; j<m_pDraggedCards.size(); j++)
					{
						//Iterate through the dragged cards and add them to the target column
						CCard* _pTemp = m_pDraggedCards.back();
						m_pDraggedCards.pop_back();
						_pTemp->SetDragged(false);
						m_pColumns[i]->m_pPile.push_back(_pTemp);
						_pTemp = nullptr;
					}
					if(!m_pColumns[m_iDraggedCardsLastColumn]->IsEmpty())
					{
						m_pColumns[m_iDraggedCardsLastColumn]->GetTopCard()->SetFaceUp(true);	
					}
				}
			}
			//If not, make sure you are trying to move a king into the empty space
			else if(m_pDraggedCards.back()->GetFace() == 12)
			{
				for(unsigned int j=0; j<m_pDraggedCards.size(); j++)
				{
					CCard* _pTemp = m_pDraggedCards.back();
					m_pDraggedCards.pop_back();
					_pTemp->SetDragged(false);
					m_pColumns[i]->m_pPile.push_back(_pTemp);
					_pTemp = nullptr;
				}
				if(!m_pColumns[m_iDraggedCardsLastColumn]->IsEmpty())
				{
					m_pColumns[m_iDraggedCardsLastColumn]->GetTopCard()->SetFaceUp(true);	
				}
			}

			return;
		}
	}

	//Release one card onto the ace pile
	if(m_pDraggedCards.size() == 1)
	{
		for(unsigned int i = 0; i < 4; i++)
		{
			_iColumnX = m_pAceHomes[i]->GetX();
			_iColumnY = m_pAceHomes[i]->GetY();

			//Mouse is within the bounds of the home pile
			if ((m_fMouseX >= _iColumnX) && (m_fMouseX < _iColumnX + CARD_WIDTH)
			&& (m_fMouseY >= _iColumnY) && (m_fMouseY < _iColumnY + CARD_HEIGHT))
			{
				if(m_pAceHomes[i]->IsEmpty() && (m_pDraggedCards.back()->GetFace() == 0) && (m_pDraggedCards.back()->GetSuit() == i))
				{
					CCard* _pTemp = m_pDraggedCards.back();
					m_pDraggedCards.pop_back();
					_pTemp->SetDragged(false);
					m_pAceHomes[i]->m_pHome.push_back(_pTemp);
					_pTemp = nullptr;
					if(!m_pColumns[m_iDraggedCardsLastColumn]->IsEmpty())
					{
						m_pColumns[m_iDraggedCardsLastColumn]->GetTopCard()->SetFaceUp(true);	
					}
					return;
				}
				CCard* _TempCard = m_pAceHomes[i]->GetTopCard();
				//If the card is one higher than the current top of the pile
				//AND if it is the correct suit
				if((_TempCard->GetFace() == m_pDraggedCards.front()->GetFace()-1) && (m_pDraggedCards.back()->GetSuit() == i))
				{
					CCard* _pTemp = m_pDraggedCards.back();
					m_pDraggedCards.pop_back();
					_pTemp->SetDragged(false);
					m_pAceHomes[i]->m_pHome.push_back(_pTemp);
					_pTemp = nullptr;
					if(!m_pColumns[m_iDraggedCardsLastColumn]->IsEmpty())
					{
						m_pColumns[m_iDraggedCardsLastColumn]->GetTopCard()->SetFaceUp(true);	
					}
					return;
				}
			}
		}
	}
		




	//The mouse wasnt released on anything
	//Return cards to their previous pile
	for(unsigned int j=0; j<m_pDraggedCards.size(); j++)
	{
		CCard* _pTemp = m_pDraggedCards.back();
		m_pDraggedCards.pop_back();
		_pTemp->SetDragged(false);
		m_pColumns[m_iDraggedCardsLastColumn]->m_pPile.push_back(_pTemp);
		_pTemp = nullptr;
	}
	
}

bool CLevel::CheckCardToColumn(CCard* _pSource, CCard* _pDestination)
{
	//Get the card values of the source card
	int _iSourceSuit = _pSource->GetSuit();
	int _iSourceFace = _pSource->GetFace();

	//Get the card values of the destination card
	int _iDestSuit = _pDestination->GetSuit();
	int _iDestFace = _pDestination->GetFace();

	//Make sure the card is less than the target column's card
	if(_iSourceFace == _iDestFace - 1)
	{
		//Check that the cards have opposite suits
		if((_iDestSuit < 2 && _iSourceSuit > 1) || (_iDestSuit > 1 && _iSourceSuit < 2))
		{
			//The Card is valid and may be moved
			return true;
		}
	}
	return false;

}

/***********************

 * DrawScore: Draw the score to the screen
 * @author: Tom Butler

 ********************/
void CLevel::DrawScore()
{
	// Get handler from game
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

	// Create x & y pos
	int kiX = 60;
	int kiY = m_iHeight - 660;

	UpdateScoreText(10);	
	std::string _strScore;
	_strScore = ToString(m_iScore);

	RECT _rTextPos;
	_rTextPos.top = kiY;
	_rTextPos.left = kiX;

	// Output text
	DrawText(hdc, _strScore.c_str(), _strScore.size(),&_rTextPos, DT_SINGLELINE);
}

/***********************

 * SetMouseCoords: Set the x & y pos of the mouse
 * @author: 

 ********************/
void CLevel::SetMouseCoords(int _x, int _y)
{
	// Set as member variables
	m_fMouseX = _x;
	m_fMouseY = _y;
}

/***********************

 * UpdateScoreText: Update the score text
 * @author: Tom Butler

 ********************/
void CLevel::UpdateScoreText(int _iScore)
{
	m_iScore = m_iScore + _iScore;
}

/***********************

 * SetMouseDown: Set the mouse down as ture
 * @author: 
 * @parameter: bool _bMouseDown, bool to set member variable as

 ********************/
void CLevel::SetMouseDown(bool _bMouseDown)
{
	m_bMouseDown = _bMouseDown;
}

/***********************

 * DeckClick: Draws another card on deck click
 * @author: 

 ********************/
void CLevel::DeckClick()
{
	// If the deck is not empty
	if( !m_pDeck->DeckEmpty() )
	{
		// Get top card and put into draw pile
		CCard* temp = m_pDeck->GetTopCard();
		temp->SetFaceUp( true );
		m_pDraw->m_pDraw.push( temp );

	}
	else // The deck is empty
	{
		// Get draw pile
		while( !m_pDraw->DrawEmpty() )
		{
			// Create temp, set as top of draw
			CCard* temp = m_pDraw->GetTopCard();
			// Set face up to false
			temp->SetFaceUp( false );
			// Push to deck
			m_pDeck->m_pDeck.push_back( temp );
			// Pop off draw
			m_pDraw->m_pDraw.pop();
		}
	}
}
