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

// Library Includes
// Local Includes
#include "resource.h"
#include "Sprite.h"
#include "utils.h"
// This Include
#include "entity.h"
// Static Variables
// Static Function Prototypes
// Implementation

CEntity::CEntity()
{
}

CEntity::~CEntity()
{
	delete m_pSprite;
	m_pSprite = 0;
}

bool CEntity::Initialise(int _iDrawX, int _iDrawY)
{
	m_pSprite = new CSprite();
	VALIDATE(m_pSprite->Initialise(_iDrawX, _iDrawY));

	return (true);
}

void CEntity::Draw()
{
	m_pSprite->Draw();
}

void CEntity::Process(float _fDeltaTick)
{
	
	m_pSprite->Process(_fDeltaTick);
}

int CEntity::GetX() const
{
	return (m_pSprite->GetX());
}

int CEntity::GetY() const
{
	return (m_pSprite->GetY());
}

float CEntity::GetWidth() const
{
	return (static_cast<float>(m_pSprite->GetWidth()));
}

float CEntity::GetHeight() const
{
	return (static_cast<float>(m_pSprite->GetHeight()));
}

void CEntity::SetX(int _f)
{
	m_pSprite->SetX(_f);
	
}

void CEntity::SetY(int _f)
{
	m_pSprite->SetY(_f);
}

void CEntity::SetDrawX(int _f)
{
	m_pSprite->SetDrawX(_f);
}

void CEntity::SetDrawY(int _f)
{
	m_pSprite->SetDrawY(_f);
}

int CEntity::GetDrawX() const
{
	return m_pSprite->GetDrawX();
}

int CEntity::GetDrawY() const
{
	return m_pSprite->GetDrawY();
}