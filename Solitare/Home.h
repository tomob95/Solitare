#pragma once
#include "Card.h"
#include "Entity.h"
#include "utils.h"
#include <stack>

class CHome : public CEntity
{
public:
	CHome();
	CHome(eSuit _eSuit):m_eSuit(_eSuit){};
	virtual ~CHome();
	virtual bool Initialise(const int _kiSpriteID, const int _kiMaskID);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	CCard* GetTopCard();
	
	eSuit m_eSuit;
	std::stack<CCard*> m_pHome;
};

