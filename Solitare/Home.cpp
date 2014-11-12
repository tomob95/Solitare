//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: Home.cpp
// Description	: Implementation for the Home class
// Author		: Tom O'Brien, Kelsey Scheurich, Tom Butler
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// Library includes
#include <list>

// Local includes
#include "Card.h"
#include "Level.h"

// This includes
#include "Home.h"


/***********************

 * CHome: Constructor
 * @author: 

 ********************/
CHome::CHome()
{
}


/***********************

 * ~CHome: Destructor
 * @author: 

 ********************/
CHome::~CHome()
{
}

/***********************

 * Initialise: Initialise the home piles
 * @author: 
 * @parameter: int _iDrawX, x pos 
 *				int _iDrawY, y pos
 * @return: bool

 ********************/
bool CHome::Initialise(int _iDrawX, int _iDrawY)
{
	// Validate and initialise entitiy
	VALIDATE(CEntity::Initialise(_iDrawX, _iDrawY));
	return true;
}

/***********************

 * Draw: Draw the home piles
 * @author: 

 ********************/
void CHome::Draw()
{
	// If piles are empty
	if(IsEmpty())
	{
		// Draw entitiy
		CEntity::Draw();
	}
	else
	{
		// Get top card and draw that
		GetTopCard()->Draw();
	}
}

/***********************

 * GetTopCard: Get the top card of the home pile
 * @author: 
 * @return: CCard*

 ********************/
CCard* CHome::GetTopCard()
{
	// return back of vector
	return (m_pHome.back());
}

/***********************

 * Process: Process the pile
 * @author: 

 ********************/
void CHome::Process( float _fDeltaTick )
{
	// Call process for entity
	CEntity::Process( _fDeltaTick );
}

/***********************

 * GetTopCard: Check if pile is empty
 * @author: 
 * @return: bool

 ********************/
bool CHome::IsEmpty()
{
	return (m_pHome.empty());
}