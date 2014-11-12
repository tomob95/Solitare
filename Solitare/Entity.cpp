//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: Entitiy.cpp
// Description	: Implementation for the entitiy class
// Author		: Tom O'Brien, Kelsey Scheurich, Tom Butler
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// Local Includes
#include "resource.h"
#include "Sprite.h"
#include "utils.h"

// This Include
#include "entity.h"

// Implementation

/***********************

 * CEntity: Constructor
 * @author: 

 ********************/
CEntity::CEntity()
{
}

/***********************

 * CEntity: Destructor
 * @author: 

 ********************/
CEntity::~CEntity()
{
	delete m_pSprite;
	m_pSprite = 0;
}

/***********************

 * Initialise: Initialise the sprite
 * @author: 
 * @parameter: int _iDrawX, x pos
 *				int _iDrawY, y pos
 * @return: bool

 ********************/
bool CEntity::Initialise(int _iDrawX, int _iDrawY)
{
	// Create new sprite, set as member
	m_pSprite = new CSprite();
	// Validate and initialise with input
	VALIDATE(m_pSprite->Initialise(_iDrawX, _iDrawY));

	return (true);
}

/***********************

 * Draw: Draw the sprite
 * @author: 

 ********************/
void CEntity::Draw()
{
	// Call draw for sprite
	m_pSprite->Draw();
}

/***********************

 * Process: Process the sprite
 * @author: 
 * @parameter: float _fDeltaTick, delta time

 ********************/
void CEntity::Process(float _fDeltaTick)
{
	// Call process for sprite
	m_pSprite->Process(_fDeltaTick);
}

/***********************

 * GetX: Get the x position of the entitiy
 * @author: 
 * @return: int

 ********************/
int CEntity::GetX() const
{
	// Return y pos of sprite
	return (m_pSprite->GetX());
}

/***********************

 * GetY: Get the y position of the entitiy
 * @author: 
 * @return: int

 ********************/
int CEntity::GetY() const
{
	// Return y pos of sprite
	return (m_pSprite->GetY());
}

/***********************

 * GetWidth: Get the width of the entitiy
 * @author: 
 * @return: float

 ********************/
float CEntity::GetWidth() const
{
	// Return width of sprite cast to float
	return (static_cast<float>(m_pSprite->GetWidth()));
}

/***********************

 * GetWidth: Get the width of the entitiy
 * @author: 
 * @return: float

 ********************/
float CEntity::GetHeight() const
{
	// Return height of sprite cast to float
	return (static_cast<float>(m_pSprite->GetHeight()));
}

/***********************

 * SetX: Set the x position of the entitiy
 * @author: 
 * @parameter: int _f, xpos

 ********************/
void CEntity::SetX(int _f)
{
	// Set position
	m_pSprite->SetX(_f);
}

/***********************

 * SetY: Set the y position of the entitiy
 * @author: 
 * @parameter: int _f, ypos

 ********************/
void CEntity::SetY(int _f)
{
	// Set position
	m_pSprite->SetY(_f);
}

/***********************

 * SetDrawX: Set the draw x position of the entitiy
 * @author: 
 * @parameter: int _f, xpos

 ********************/
void CEntity::SetDrawX(int _f)
{
	// Set position
	m_pSprite->SetDrawX(_f);
}

/***********************

 * SetDrawY: Set the draw y position of the entitiy
 * @author: 
 * @parameter: int _f, ypos

 ********************/
void CEntity::SetDrawY(int _f)
{
	// Set position
	m_pSprite->SetDrawY(_f);
}

/***********************

 * GetDrawX: Get the draw x position of the entitiy
 * @author: 
 * @return: int

 ********************/
int CEntity::GetDrawX() const
{
	// Get position
	return m_pSprite->GetDrawX();
}

/***********************

 * GetDrawY: Get the draw y position of the entitiy
 * @author: 
 * @return: int

 ********************/
int CEntity::GetDrawY() const
{
	// Get position
	return m_pSprite->GetDrawY();
}