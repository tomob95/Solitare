//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: Card.cpp
// Description	: Implementation for the card class
// Author		: Tom O'Brien, Kelsey Scheurich, Tom Butler
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// This includes
#include "Card.h"
#include "utils.h"

/***********************

 * ~CCard: Destructor function
 * @author: 

 ********************/
CCard::~CCard()
{
}

/***********************

 * ~CCard: Destructor function
 * @author: 
 * @parameter: int _iDrawX, draw y position
 *				int _iDrawY, draw x position
 * @return: bool

 ********************/
bool CCard::Initialise(int _iDrawX, int _iDrawY)
{
	// Validate and initialise entity at that position
	VALIDATE(CEntity::Initialise(_iDrawX, _iDrawY));
	return 0;
}

/***********************

 * Draw: draw the entitity
 * @author: 
 * @return: bool

 ********************/
void CCard::Draw()
{
	// Call draw function for that entitiy
	CEntity::Draw();	
}

/***********************

 * Process: process the entity
 * @author: 
 * @parameters: float _fDeltaTick, delta tick rate
 * @return: bool

 ********************/
void CCard::Process(float _fDeltaTick)
{
	// Call process for entity
	CEntity::Process(_fDeltaTick);
}

/***********************

 * GetFace: Get the face value of the card
 * @author: 
 * @return: int

 ********************/
int CCard::GetFace()
{
	return m_iFace;
}

/***********************

 * SetFace: Set the face value of the card
 * @author: 
 * @parameter: int _iFace, face value to set as

 ********************/
void CCard::SetFace(int _iFace)
{
	m_iFace = _iFace;	
}

/***********************

 * GetSuit: Get the suit value of the card
 * @author: 
 * @return: int

 ********************/
int CCard::GetSuit()
{
	return m_iSuit;
}

/***********************

 * SetSuit: Set the suit value of the card
 * @author: 
 * @parameter: int _iSuit

 ********************/
void CCard::SetSuit(int _iSuit)
{
	m_iSuit = _iSuit;
}

/***********************

 * GetFaceUp: Get the face up value
 * @author: 
 * @return: int

 ********************/
int CCard::GetFaceUp()
{
	// Return member variable
	return (m_bIsFaceUp);
}

/***********************

 * SetFaceUp: Set the face up value
 * @author: 
 * @parameter: bool _bFaceUp

 ********************/
void CCard::SetFaceUp(bool _bFaceUp)
{
	// Set member variable to input
	m_bIsFaceUp = _bFaceUp;
}

/***********************

 * SetDragged: Set the card to dragged
 * @author: 
 * @parameter: bool _bDragged

 ********************/
void CCard::SetDragged(bool _bDragged)
{
	// Set member variable to dragged 
	m_bBeingDragged = _bDragged;
}

/***********************

 * SetDragged: Set the card to dragged
 * @author: 
 * @return: bool

 ********************/
bool CCard::GetDragged()
{
	// Return member variable
	return (m_bBeingDragged);
}
