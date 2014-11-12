//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: Column.cpp
// Description	: Implementation for the column class
// Author		: Tom O'Brien, Kelsey Scheurich, Tom Butler
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// Local includes
#include "utils.h"

// This includes
#include "Column.h"


/***********************

 * CColumn: Constructor
 * @author: 

 ********************/
CColumn::CColumn(void)
{
}

/***********************

 * ~CColumn: Destructor
 * @author: 

 ********************/
CColumn::~CColumn(void)
{
}

/***********************

 * Draw: Draw the column
 * @author: 

 ********************/
void CColumn::Draw()
{
	// If its empty
	if(IsEmpty())
	{
		// Draw for each entitiy
		CEntity::Draw();
	}
	else
	{
		//Draw each card in the column
		for (unsigned int i = 0; i<m_pPile.size(); i++)
		{
			m_pPile[i]->Draw();
		}
	}
}

/***********************

 * Initialise: Initialise the column
 * @author: 
 * @parameter: int _iDrawX, x position 
 *				int _iDrawY, y position
 * @return: bool

 ********************/
bool CColumn::Initialise(int _iDrawX, int _iDrawY)
{
	// Validate and initialise entity
	VALIDATE(CEntity::Initialise(_iDrawX, _iDrawY));

	return 0;
}

/***********************

 * Process: Process the column
 * @author: 
 * @parameter: float _fDeltaTick, delta time 

 ********************/
void CColumn::Process(float _fDeltaTick)
{
	// If its empty
	if (IsEmpty())
	{
		//Set Sprite to the empty sprite
		CEntity::SetDrawX(6 * CARD_WIDTH);
		CEntity::SetDrawY(4 * CARD_HEIGHT);

	}
	else
	{
		//Draw each card in the column
		for (unsigned int i = 0; i<m_pPile.size(); i++)
		{
			// If the card is not face up
			if (!m_pPile[i]->GetFaceUp())
			{
				// Draw the back
				m_pPile[i]->SetDrawX(BACK_X);
				m_pPile[i]->SetDrawY(BACK_Y);
			}

			else
			{
				// Draw the front
				m_pPile[i]->SetDrawX(m_pPile[i]->GetFace() * CARD_WIDTH);
				m_pPile[i]->SetDrawY(m_pPile[i]->GetSuit() * CARD_HEIGHT);
			}

			// Set x & y position
			m_pPile[i]->SetX(static_cast<int>(GetX()));
			m_pPile[i]->SetY(static_cast<int>(GetY() + (i * 58)));
			m_pPile[i]->Process(_fDeltaTick);
		}
	}
	// Process the entitiy
	CEntity::Process(_fDeltaTick);
}

/***********************

 * IsEmpty: Check if the column is empty
 * @author:
 * @return: bool

 ********************/
bool CColumn::IsEmpty()
{
	// Return if the pile is empty
	return (m_pPile.empty());
}

/***********************

 * GetTopCard: Return the card at the top
 * @author: 
 * @return: CCard*

 ********************/
CCard* CColumn::GetTopCard()
{
	return (m_pPile.back());
}