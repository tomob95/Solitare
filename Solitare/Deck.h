//Deck Pile and Draw Pile

#pragma once
#include <stack>
#include <vector>
#include "entity.h"
#include "Card.h"
using namespace std;

class CDeck :
	public CEntity
{
public:
	CDeck(void);
	virtual ~CDeck(void);
	virtual bool Initialise(int _iDrawX, int _iDrawY);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	// Deck Empty
	// Determine if the deck is empty
	bool DeckEmpty();

	//on deck click
	//		Take top card and move to draw deck
	//		Set card m_bFaceUp to true
	//	if empty
	//		Take cards from m_pDraw
	//		Set each card m_bFaceUp to false
	//		Push into m_pDeck
	//
	//on draw click
	//		Select top card
	//		Set CLevel::m_pSelectedCard to card

	vector<CCard*> m_pDeck;
	stack<CCard*> m_pDraw;


};

