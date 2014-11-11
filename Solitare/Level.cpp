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
#include "Column.h"

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

	// Create new deck, set as member
	m_pDeck = new CDeck();
	// Validate and intialise deck
	VALIDATE(m_pDeck->Initialise(0, 4));
	// Set deck x & y position
	m_pDeck->SetX(40);
	m_pDeck->SetY(40);

	// Create temp pointers for card and column
	CCard* _TempCard;
	CColumn* _TempColumn;

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




	return (true);
}

/***********************

 * Draw: Draw cards
 * @author: 

 ********************/
void CLevel::Draw()
{


	// Call draw recursively

	m_pDeck->Draw();
	// For each column
	for(int i=0; i<7; i++)
	{
		// Call draw
		m_pColumns[i]->Draw();
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
		// Start drag
		HandleMouseDrag();
	}

	else if (!m_pDraggedCards.empty())
	{
		HandleMouseDrop();
	}
	ProcessCheckForWin();

	//Process the deck
	m_pDeck->Process(_fDeltaTick);

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
	//TODO: this
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

	//Release on ace pile

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
 * @author: 

 ********************/
void CLevel::DrawScore()
{
	// Get handler from game
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

	// Create x & y pos
	const int kiX = 0;
	const int kiY = m_iHeight - 50;
	
	// Output text
	TextOut(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
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
 * @author: 

 ********************/
void CLevel::UpdateScoreText()
{
	// TODO: this
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
