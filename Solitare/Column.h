//Column Pile of Cards

#pragma once
#include <stack>
#include "entity.h"
#include "Card.h"
using namespace std;
class CColumn :
	public CEntity
{
public:
	CColumn(void);
	virtual ~CColumn(void);
	virtual void Draw();
	virtual bool Initialise(const int _kiSpriteID, const int _kiMaskID);
	virtual void Process(float _fDeltaTick);
	stack<CCard*> m_pColumn;

};

