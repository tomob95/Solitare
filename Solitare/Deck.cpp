//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: BackBuffer.cpp
// Description	: Implementation for the BackBuffer class
// Author		: Tom O'Brien, Kelsey Scheurich, Tom Butler
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#include "Deck.h"
#include "utils.h"

CDeck::CDeck(void)
{
}

CDeck::~CDeck(void)
{
}

bool CDeck::Initialise(int _iDrawX, int _iDrawY)
{
	VALIDATE(CEntity::Initialise(_iDrawX, _iDrawY));

	return true;
}

void CDeck::Draw()
{
	CEntity::Draw();
}

void CDeck::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
	if (DeckEmpty())
	{
		//draw empty deck sprite
		SetDrawX(CARD_WIDTH * 6);
		SetDrawY(CARD_HEIGHT * 4);
	}
	else
	{
		//draw card back sprite
		SetDrawX(BACK_X);
		SetDrawY(BACK_Y);
	}
}

bool CDeck::DeckEmpty()
{
	return m_pDeck.empty();
}
