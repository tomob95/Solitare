#pragma once
#include "Card.h"
#include "Entity.h"
#include "utils.h"
#include <list>

class CHome : public CEntity
{
public:
	CHome();
	CHome(eSuit _eSuit):m_eSuit(_eSuit){};
	virtual ~CHome();
	virtual bool Initialise(int _iDrawX, int _iDrawY);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	CCard* GetTopCard();
	bool IsEmpty();
	
	eSuit m_eSuit;
	std::list<CCard*> m_pHome;
};

