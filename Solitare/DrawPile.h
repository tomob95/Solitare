//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: DrawPile.h
// Description	: Header for the DrawPile class
// Author		: Tom O'Brien, Kelsey Scheurich, Tom Butler
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#pragma once

// Library includes
#include <stack>

// Local includes
#include "entity.h"
#include "Card.h"

using namespace std;

// Prototypes
class CDrawPile :
	public CEntity
{
public:
	// Constructor
	CDrawPile(void);
	// Virtual functions
	virtual ~CDrawPile(void);
	virtual bool Initialise(int _iDrawX, int _iDrawY);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	// Member functions
	bool DrawEmpty();
	CCard* GetTopCard();

	// Member varible
	stack<CCard*> m_pDraw;

};

