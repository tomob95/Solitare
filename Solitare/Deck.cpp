//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: BackBuffer.cpp
// Description	: Implementation for the BackBuffer class
// Author		: Tom O'Brien, Kelsey Scheurich, Tom Butler
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// Local includes
#include "utils.h"

// This includes
#include "Deck.h"

/***********************

 * CDeck: Deck constructor
 * @author: 

 ********************/
CDeck::CDeck(void)
{
}

/***********************

 * CDeck: Deck destructor
 * @author: 

 ********************/
CDeck::~CDeck(void)
{
}

/***********************

 * Initialise: Initialise the deck
 * @author: 
 * @parameters: int _iDrawX, draw position
 *				int _iDrawY, draw position

 ********************/
bool CDeck::Initialise(int _iDrawX, int _iDrawY)
{
	// Validate and initialise entitiy
	VALIDATE(CEntity::Initialise(_iDrawX, _iDrawY));
	return (true);
}

/***********************

 * Draw: Draw the deck
 * @author: 

 ********************/
void CDeck::Draw()
{
	// Call draw for entity
	CEntity::Draw();
}

/***********************

 * Process: Process the deck
 * @author: 
 * @parameters: float _fDeltaTick, delta time

 ********************/
void CDeck::Process(float _fDeltaTick)
{
	// Process the entity
	CEntity::Process(_fDeltaTick);

	// If the deck is empty
	if (DeckEmpty())
	{
		//draw empty deck sprite
		SetDrawX(CARD_WIDTH * 6);
		SetDrawY(CARD_HEIGHT * 4);
	}
	else
	{
		//draw card back sprite
		SetDrawX(BACK_X);
		SetDrawY(BACK_Y);
	}
}

/***********************

 * DeckEmpty: Check if deck is empty
 * @author: 
 * @return: bool

 ********************/
bool CDeck::DeckEmpty()
{
	// Return if deck is empty
	return (m_pDeck.empty());
}

/***********************

 * GetTopCard: Return the card at the top
 * @author: 
 * @return: CCard*

 ********************/
CCard* CDeck::GetTopCard()
{
	return (m_pDeck.back());
}