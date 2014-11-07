//Draw Pile

#pragma once
#include <stack>
#include "entity.h"
#include "Card.h"

class CDraw :
	public CEntity
{
public:
	CDraw(void);
	virtual ~CDraw(void);
	virtual bool Initialise(const int _kiSpriteID, const int _kiMaskID);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	std::stack<CCard*> m_pDraw;
};

