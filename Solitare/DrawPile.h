//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: DrawPile.h
// Description	: Header file for Drawpile class
// Author		: Kelsey Scheurich
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#pragma once

// Library includes
#include <stack>
//#include <vector>

// Local includes
#include "entity.h"
#include "Card.h"

using namespace std;

class CDrawPile :
	public CEntity
{
public:
	// Member funtions
	CDrawPile(void);
	// Virtual functions
	virtual ~CDrawPile(void);
	virtual bool Initialise(int _iDrawX, int _iDrawY);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	//Prototypes
	bool DrawEmpty();
	CCard* GetTopCard();

	// Member varible
	stack<CCard*> m_pDraw;


};

