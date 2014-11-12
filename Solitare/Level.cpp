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
#include "Clock.h"

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
 * @return: bool

 ********************/
bool CLevel::Initialise(int _iWidth, int _iHeight)
{
	// Set width and height
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	// Initialise score to 0
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
	// Comment out to test win
	std::random_shuffle(m_pDeck->m_pDeck.begin(), m_pDeck->m_pDeck.end());

	// Loop through each column
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
		// Create new home object & initialise
		_TempHome = new CHome();
		_TempHome->Initialise(6, 4);
		// Push to ace homes
		m_pAceHomes.push_back(_TempHome);
		// Set x & y, draw
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
	// Check if game is won
	ProcessCheckForWin();

	//Process the deck
	m_pDeck->Process(_fDeltaTick);
	m_pDraw->Process( _fDeltaTick );
	
	// For each column
	for (int i = 0; i < 7; i++)
	{
		// Process
		m_pColumns[i]->Process(_fDeltaTick);
	}

	//For each home cell
	for (int j = 0; j < 4; j++)
	{
		// If home is empty
		if(m_pAceHomes[j]->IsEmpty())
		{
			// Draw empty sprites & process
			m_pAceHomes[j]->SetDrawX((2 + j) * CARD_WIDTH);
			m_pAceHomes[j]->SetDrawY(4 * CARD_HEIGHT);
			m_pAceHomes[j]->Process(_fDeltaTick);
		}
		else
		{
			// Draw the cards
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
	int iCheck = 0;
	// Loop through all homes
	for( int i = 0; i < 4; ++i )
	{
		// If each home is full
		if( m_pAceHomes[ i ]->m_pHome.size() == 13 )
		{
			// Add to check
			iCheck++;
		}
	}

	// If all homes are full
	if( iCheck == 4 )
	{
		// Get instance
		HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

		// Create x & y pos
		int kiX = 60;
		int kiY = m_iHeight - 600;

		// Create string
		string _strGO = "You won, game over!";

		// Create string, set x & y
		RECT _rTextPos;
		_rTextPos.top = kiY;
		_rTextPos.left = kiX;

		// Output text
		DrawText(hdc, _strGO.c_str(), _strGO.size(),&_rTextPos, DT_SINGLELINE);
		DrawScore();

	}
}

/***********************

 * IsMouseDraggingCards: Check if the mouse is dragging cards
 * @author: 
 * @return: bool

 ********************/
bool CLevel::IsMouseDraggingCards()
{
	return (!m_pDraggedCards.empty());
}

/***********************

 * IsMouseDraggingCards: Check if the mouse is dragging cards
 * @author: 
 * @parameter: int _ColumnNo, 

 ********************/
void CLevel::DragFromColumn(int _ColumnNo)
{
	// TODO: Do we need this?
}

/***********************

 * HandleMouseDrag: Function to handle dragging mouse
 * @author: 

 ********************/
void CLevel::HandleMouseDrag()
{

	//Make sure none of the cards are already being dragged
	if(!IsMouseDraggingCards())
	{
		//Detect dragging the draw pile
		int _iDrawPileX = m_pDraw->GetX();
		int _iDrawPileY = m_pDraw->GetY();

		// If the mouse is on a pile
		if((m_fMouseX >= _iDrawPileX) && (m_fMouseX < _iDrawPileX + CARD_WIDTH)
			&& (m_fMouseY >= _iDrawPileY) && (m_fMouseY < _iDrawPileY + CARD_HEIGHT))
		{
			// Set card to dragged
			m_pDraw->GetTopCard()->SetDragged(true);
			// Push draw card onto drag pile
			m_pDraggedCards.push_back(m_pDraw->GetTopCard());
			// Pop off draw
			m_pDraw->m_pDraw.pop();
			m_iDraggedCardsLastColumn = 8;
		}

		//Detect dragging the from the home piles
		for(int i=0; i<4; i++)
		{
			// If homes are not empty
			if(!m_pAceHomes[i]->IsEmpty())
			{
				// Get x & y
				int _iPileX = m_pAceHomes[i]->GetX();
				int _iPileY = m_pAceHomes[i]->GetY();

				// If mouse is over pile
				if((m_fMouseX >= _iPileX) && (m_fMouseX < _iPileX+CARD_WIDTH)
					&& (m_fMouseY >= _iPileY) && (m_fMouseY < _iPileY+CARD_HEIGHT))
				{
					// Get top card and set dragged to true
					m_pAceHomes[i]->GetTopCard()->SetDragged(true);
					// Put dragged card at the beginning of drag pile
					m_pDraggedCards.insert(m_pDraggedCards.begin(), m_pAceHomes[i]->GetTopCard());
										
					//Remove the cards that are being dragged
					m_pAceHomes[i]->m_pHome.pop_back();
					m_iDraggedCardsLastColumn = 9+i;
					return;
				}
			}
		}


		// Iterate through all columns
		for(int i=0; i<7; i++)
		{
			// If columns are not empty
			if(!m_pColumns[i]->IsEmpty())
			{
				//See if they have selected a stack of cards
				for(unsigned int j=0; j<m_pColumns[i]->m_pPile.size()-1; j++)
				{
					//Get clicked card's X and Y
					int _CardX = m_pColumns[i]->m_pPile[j]->GetX();
					int _CardY = m_pColumns[i]->m_pPile[j]->GetY();

					//See if the mouse is within the cards's bounds (only the showing part)
					if((m_fMouseX >= _CardX) && (m_fMouseX < _CardX+CARD_WIDTH)
					&& (m_fMouseY >= _CardY) && (m_fMouseY < _CardY+58))
					{
						//Make sure the card is face up 
						if(m_pColumns[i]->m_pPile[j]->GetFaceUp())
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
						return;
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
}

/***********************

 * HandleMouseDrop: Function to handle drop mouse
 * @author: 

 ********************/
void CLevel::HandleMouseDrop()
{
	// Create int for x & y pos
	int _iColumnX;
	int _iColumnY;

	//Go through all the columns and see if the mouse is on the column
	for(unsigned int i = 0; i < 7; i++)
	{
		//Get screen coords of front card of column
		if(!m_pColumns[i]->m_pPile.empty())
		{
			// Set pos as top card's x & y
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
				if(CheckCardToColumn(m_pDraggedCards.back(), m_pColumns[i]->GetTopCard()))
				{
					//The cards are valid and need to be moved to the destination column
					while(!m_pDraggedCards.empty())
					{
						//Iterate through the dragged cards and add them to the target column
						CCard* _pTemp = m_pDraggedCards.back();
						m_pDraggedCards.pop_back();
						_pTemp->SetDragged(false);
						m_pColumns[i]->m_pPile.push_back(_pTemp);
						_pTemp = nullptr;
						//Update the score for putting a card onto a column
						UpdateScoreText(CARD_TO_COLUMNS);
					}
					// If its one of the game columns
					if(m_iDraggedCardsLastColumn < 8)
					{
						// If the last column is not empty
						if(!m_pColumns[m_iDraggedCardsLastColumn]->IsEmpty())
						{
							// Set top card to face up
							m_pColumns[m_iDraggedCardsLastColumn]->GetTopCard()->SetFaceUp(true);
							//Update the score for putting a card on the ace pile
							UpdateScoreText(FLIP_CARD);
						}
					}
				}
			}

			//If not, make sure you are trying to move a king into the empty space
			else if(m_pDraggedCards.back()->GetFace() == 12)
			{
				//Move all cards onto the pile
				while(!m_pDraggedCards.empty())
				{
					CCard* _pTemp = m_pDraggedCards.back();
					m_pDraggedCards.pop_back();
					_pTemp->SetDragged(false);
					m_pColumns[i]->m_pPile.push_back(_pTemp);
					_pTemp = nullptr;
					//Update the score for putting a card onto a column
					UpdateScoreText(CARD_TO_COLUMNS);
				}
				//make the old column's top card face up
				if(m_iDraggedCardsLastColumn < 8)
				{
					// If last column is not empty
					if(!m_pColumns[m_iDraggedCardsLastColumn]->IsEmpty())
					{
						// Get top card set to face up
						m_pColumns[m_iDraggedCardsLastColumn]->GetTopCard()->SetFaceUp(true);
						//Update the score for putting a card on the ace pile
						UpdateScoreText(FLIP_CARD);
					}
				}
			}

			break;
		}
	}

	//Release one card onto the ace pile
	if(m_pDraggedCards.size() == 1)
	{
		// For each home
		for(unsigned int i = 0; i < 4; i++)
		{
			// Set xy pos as home xy pos
			_iColumnX = m_pAceHomes[i]->GetX();
			_iColumnY = m_pAceHomes[i]->GetY();

			//Mouse is within the bounds of the home pile
			if ((m_fMouseX >= _iColumnX) && (m_fMouseX < _iColumnX + CARD_WIDTH)
			&& (m_fMouseY >= _iColumnY) && (m_fMouseY < _iColumnY + CARD_HEIGHT))
			{
				//Make sure the ace home is empty and you are dropping an ace of the correct type
				if(m_pAceHomes[i]->IsEmpty() && (m_pDraggedCards.back()->GetFace() == 0) && (m_pDraggedCards.back()->GetSuit() == i))
				{
					CCard* _pTemp = m_pDraggedCards.back();
					m_pDraggedCards.pop_back();
					_pTemp->SetDragged(false);
					m_pAceHomes[i]->m_pHome.push_back(_pTemp);
					_pTemp = nullptr;
					//Update the score for putting a card on the ace pile
					UpdateScoreText(CARD_TO_ACE_HOME);

					// If column is less than 8
					if(m_iDraggedCardsLastColumn < 8)
					{
						// If last column is not empty
						if(!m_pColumns[m_iDraggedCardsLastColumn]->IsEmpty())
						{
							// Set faceup
							m_pColumns[m_iDraggedCardsLastColumn]->GetTopCard()->SetFaceUp(true);
							// Update the score for flipping a card
							UpdateScoreText(FLIP_CARD);
						}
					}
					return;
				}
				//the card is not an ace of the correct suit
				else if(!m_pAceHomes[i]->IsEmpty())
				{
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
						//Update the score for putting a card on the ace pile
						UpdateScoreText(CARD_TO_ACE_HOME);

						// If column is less than 8
						if(m_iDraggedCardsLastColumn < 8)
						{
							// If last column is not empty
							if(!m_pColumns[m_iDraggedCardsLastColumn]->IsEmpty())
							{
								// Get top card set to face up
								m_pColumns[m_iDraggedCardsLastColumn]->GetTopCard()->SetFaceUp(true);
								// Update the score for flipping a card
								UpdateScoreText(FLIP_CARD);
							}
						}
						return;
					}
				}
			}
		}
	}

	//The mouse wasnt released on anything
	//Return cards to their previous pile
	while(!m_pDraggedCards.empty())
	{
		// Create temp to hold dragged cards
		CCard* _pTemp = m_pDraggedCards.back();
		m_pDraggedCards.pop_back();
		_pTemp->SetDragged(false);

		// Switch depending on last position, push back to appropriate column
		switch(m_iDraggedCardsLastColumn)
		{
		case 8:
			{
				m_pDraw->m_pDraw.push(_pTemp);
			}
			break;
		case 9:
		case 10:
		case 11:
		case 12:
			{
				m_pAceHomes[m_iDraggedCardsLastColumn - 9]->m_pHome.push_back(_pTemp);
			}
			break;
		default:
			{
				m_pColumns[m_iDraggedCardsLastColumn]->m_pPile.push_back(_pTemp);
			}
			break;
		}
	
		_pTemp = nullptr;
	}
	
}

/***********************

 * CheckCardToColumn: Function to check if card can go to column
 * @author: 
 * @parameter: CCard* _pSource, source card
 *				CCard* _pDestination, destination card
 * @return: bool

 ********************/
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

	// Create string out of score value
	std::string _strScore;
	_strScore = "Score: " + ToString(m_iScore);

	// Create rectangle using x & y
	RECT _rTextPos;
	_rTextPos.top = kiY;
	_rTextPos.left = kiX;

	// Output text
		//--- this works with visual studio 2012 ---//
		//DrawText(hdc, _strScore.c_str(), _strScore.size(), &_rTextPos, DT_SINGLELINE);
	TextOut(hdc,kiX,235, _strScore.c_str(), _strScore.size());

	
}

/***********************

 * SetMouseCoords: Set the x & y pos of the mouse
 * @author: 
 * @parameter: int _x, x position
 *				int _y, y position

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
 * @parameter: int _iScore, score to update

 ********************/
void CLevel::UpdateScoreText(int _iScore)
{
	m_iScore = m_iScore + _iScore;
}

/***********************

 * SetMouseDown: Set the mouse down as true or false
 * @author: 
 * @parameter: bool _bMouseDown, bool to set member variable as

 ********************/
void CLevel::SetMouseDown(bool _bMouseDown)
{
	m_bMouseDown = _bMouseDown;
}

/***********************

 * GetMouseDown: Return if the mouse is down
 * @author: 
 * @return: bool

 ********************/
bool CLevel::GetMouseDown()
{
	return m_bMouseDown;
}

/*******************

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
		m_pDeck->m_pDeck.pop_back();
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

/*******************

 * GetDeckX: Return the X position of the Deck
 * @author: 
 * @return: int

 ********************/
int CLevel::GetDeckX()
{
	return m_pDeck->GetX();
}
/*******************

 * GetDeckY: Return the Y position of the Deck
 * @author: 
 * @return: int

 ********************/
int CLevel::GetDeckY()
{
	return m_pDeck->GetY();
}
