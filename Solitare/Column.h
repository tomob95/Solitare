//Column Pile of Cards

#pragma once
#include <vector>
#include "entity.h"
#include "Card.h"
using namespace std;
class CCard;
class CColumn :
	public CEntity
{
public:
	CColumn(void);
	virtual ~CColumn(void);
	virtual void Draw();
	virtual bool Initialise(int _iDrawX, int _iDrawY);
	virtual void Process(float _fDeltaTick);
	CCard* GetTopCard();
	vector<CCard*> m_pPile;
	bool IsEmpty();
};

