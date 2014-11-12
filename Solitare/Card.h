//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: Card.h
// Description	: Header for the card class
// Author		: Tom O'Brien, Kelsey Scheurich, Tom Butler
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#pragma once

// Local includes
#include "Entity.h"

// prototypes
class CCard : public CEntity
{
public:
	// Constructor/destructor
	CCard(int _iFace, int _iSuit):m_iFace(_iFace),m_iSuit(_iSuit),m_bIsFaceUp(false),m_bBeingDragged(false){};
	virtual ~CCard();

	virtual bool Initialise(int _iDrawX, int _iDrawY);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	int GetFace();
	void SetFace(int _iFace);
	int GetSuit();
	void SetSuit(int _iSuit);
	int GetFaceUp();
	void SetFaceUp(bool _bFaceUp);
	void SetDragged(bool _bDragged);
	bool GetDragged();

private:
	int m_iFace;
	int m_iSuit;
	bool m_bIsFaceUp;
	bool m_bBeingDragged;

};

