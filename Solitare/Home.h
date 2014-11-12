//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: Home.h
// Description	: Header for the home class
// Author		: Tom O'Brien, Kelsey Scheurich, Tom Butler
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#pragma once

// Local includes
#include "Card.h"
#include "Entity.h"
#include "utils.h"
#include <vector>

// Prototypes
class CHome : public CEntity
{
public:
	// Constructor/destructor
	CHome();
	CHome(eSuit _eSuit):m_eSuit(_eSuit){};
	virtual ~CHome();

	// Member functions
	virtual bool Initialise(int _iDrawX, int _iDrawY);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	CCard* GetTopCard();
	bool IsEmpty();
	
	// Member variables
	eSuit m_eSuit;
	std::vector<CCard*> m_pHome;
};

