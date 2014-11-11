#include "Card.h"
#include "utils.h"
CCard::~CCard()
{
}

bool CCard::Initialise(int _iDrawX, int _iDrawY)
{
	VALIDATE(CEntity::Initialise(_iDrawX, _iDrawY));
	return 0;
}

void CCard::Draw()
{
	CEntity::Draw();	
}

void CCard::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
}

int CCard::GetFace()
{
	return m_iFace;
}

void CCard::SetFace(int _iFace)
{
	m_iFace = _iFace;	
}

int CCard::GetSuit()
{
	return m_iSuit;
}

void CCard::SetSuit(int _iSuit)
{
	m_iSuit = _iSuit;
}

int CCard::GetFaceUp()
{
	return m_bIsFaceUp;
}

void CCard::SetFaceUp(bool _bFaceUp)
{
	m_bIsFaceUp = _bFaceUp;
}

void CCard::SetDragged(bool _bDragged)
{
	m_bBeingDragged = _bDragged;
}

bool CCard::GetDragged()
{
	return m_bBeingDragged;
}
