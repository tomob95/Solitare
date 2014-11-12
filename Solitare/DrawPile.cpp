//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: DrawPile.cpp
// Description	: Implementation for the Drawpile class
// Author		: Tom O'Brien, Kelsey Scheurich, Tom Butler
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// This include
#include "DrawPile.h"
#include "utils.h"

/***********************

 * CDeck: Deck constructor
 * @author: 

 ********************/
CDrawPile::CDrawPile(void)
{
}

/***********************

 * CDeck: Deck destructor
 * @author: 

 ********************/
CDrawPile::~CDrawPile(void)
{
}

/***********************

 * Initialise: Initialise the deck
 * @author: 
 * @parameters: int _iDrawX, draw position
 *				int _iDrawY, draw position

 ********************/
bool CDrawPile::Initialise( int _iDrawX, int _iDrawY )
{
	// Validate and initialise entitiy
	VALIDATE( CEntity::Initialise( _iDrawX, _iDrawY ) );

	return (true);
}

/***********************

 * Draw: Draw the deck
 * @author: 

 ********************/
void CDrawPile::Draw()
{
	// Call draw for entity
	CEntity::Draw();
}

/***********************

 * Process: Process the deck
 * @author: 
 * @parameters: float _fDeltaTick, delta time

 ********************/
void CDrawPile::Process( float _fDeltaTick )
{
	// Process the entity
	CEntity::Process( _fDeltaTick );

	// If the draw pile is empty
	if( DrawEmpty() )
	{
		//draw empty deck sprite
		SetDrawX( CARD_WIDTH * 6 );
		SetDrawY( CARD_HEIGHT * 4 );
	}
	else
	{
		//draw card front sprite
		//CEntity::Draw();
		SetDrawX( m_pDraw.top()->GetFace() * CARD_WIDTH );
		SetDrawY( m_pDraw.top()->GetFace() * CARD_HEIGHT );
	}
}

/***********************

 * DeckEmpty: Check if deck is empty
 * @author: 
 * @return: bool

 ********************/
bool CDrawPile::DrawEmpty()
{
	// Return if deck is empty
	return( m_pDraw.empty() );
}

/***********************

 * GetTopCard: Return the card at the top
 * @author: 
 * @return: CCard*

 ********************/
CCard* CDrawPile::GetTopCard()
{
	return( m_pDraw.top() );
}
