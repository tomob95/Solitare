//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: Column.h
// Description	: Header for the Column class
// Author		: Tom O'Brien, Kelsey Scheurich, Tom Butler
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#pragma once

// Library includes
#include <vector>

// Local includes
#include "entity.h"
#include "Card.h"

using namespace std;

// Prototypes
class CCard;
class CColumn :
	public CEntity
{
public:
	// Constructor/destructor
	CColumn(void);
	virtual ~CColumn(void);

	// Member functions
	virtual void Draw();
	virtual bool Initialise(int _iDrawX, int _iDrawY);
	virtual void Process(float _fDeltaTick);
	CCard* GetTopCard();
	bool IsEmpty();

	// Member variables
	vector<CCard*> m_pPile;
	
};

