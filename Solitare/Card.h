#pragma once
#include "Entity.h"

class CCard : public CEntity
{
public:
	CCard();
	~CCard();

private:
	int m_iFace;
	int m_iSuit;
//	HRGN m_hRgn;
	bool m_bIsFaceUp;
	static CSprite m_BackSprite;
};

