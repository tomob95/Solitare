//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: Deck.h
// Description	: Header for the Deck class
// Author		: Tom O'Brien, Kelsey Scheurich, Tom Butler
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#pragma once

// Library includes
#include <stack>
#include <vector>

// Local includes
#include "entity.h"
#include "Card.h"

using namespace std;

class CDeck :
	public CEntity
{
public:
	// Coonstructor/Destructor
	CDeck(void);
	virtual ~CDeck(void);

	virtual bool Initialise(int _iDrawX, int _iDrawY);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	// Member functions
	bool DeckEmpty();
	CCard* GetTopCard();

	// Member variables
	vector<CCard*> m_pDeck;

};

