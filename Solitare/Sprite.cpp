//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: Sprite.cpp
// Description	: Implementation for the sprite class
// Author		: Tom O'Brien, Kelsey Scheurich, Tom Butler
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"
#include "game.h"
#include "backbuffer.h"
#include "utils.h"

// This include
#include "Sprite.h"

// Static Variables
HDC CSprite::s_hSharedSpriteDC = 0;
int CSprite::s_iRefCount = 0;

// Implementation
CSprite::CSprite(): m_iX(0), m_iY(0)
{
	++s_iRefCount;
}

CSprite::~CSprite()
{
	DeleteObject(m_hSprite);
	//DeleteObject(m_hMask);
	--s_iRefCount;
	if (s_iRefCount == 0)
	{
		DeleteDC(s_hSharedSpriteDC);
		s_hSharedSpriteDC = 0;
	}
}

bool CSprite::Initialise(int _iDrawX, int _iDrawY)
{
	HINSTANCE hInstance = CGame::GetInstance().GetAppInstance();

	if (!s_hSharedSpriteDC)
	{
		s_hSharedSpriteDC = CreateCompatibleDC(NULL);
	}

	//if (!m_hSprite)
	//{
	//	m_hSprite = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_CARDS), IMAGE_BITMAP, 0, 0, 0);
	//	GetObject(m_hSprite, sizeof(BITMAP), &m_bitmapSprite);
	//}

	m_iDrawX = 132 * _iDrawX;
	m_iDrawY = 192 * _iDrawY;

	m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_CARDS));
	//m_hMask = LoadBitmap(hInstance, MAKEINTRESOURCE(_iMaskResourceID));
	//VALIDATE(m_hMask);
	GetObject(m_hSprite, sizeof(BITMAP), &m_bitmapSprite);

	//GetObject(m_hMask, sizeof(BITMAP), &m_bitmapMask);
	return (true);
}

void CSprite::Draw()
{
	//int iW = GetWidth();
	//int iH = GetHeight();
	//int iX = m_iX - (iW / 2);
	//int iY = m_iY - (iH / 2);
	CBackBuffer* pBackBuffer = CGame::GetInstance().GetBackBuffer();

	HGDIOBJ hOldObj = SelectObject(s_hSharedSpriteDC, m_hSprite);
	//BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, 0, 0, SRCAND);
	//SelectObject(s_hSharedSpriteDC, m_hSprite);
	//BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, 0, 0, SRCPAINT);
	//SelectObject(s_hSharedSpriteDC, hOldObj);
	BitBlt(pBackBuffer->GetBFDC(), m_iX, m_iY, CARD_WIDTH, CARD_HEIGHT, s_hSharedSpriteDC, MASK_X, MASK_Y, SRCAND);
	BitBlt(pBackBuffer->GetBFDC(), m_iX, m_iY, CARD_WIDTH, CARD_HEIGHT, s_hSharedSpriteDC, m_iDrawX, m_iDrawY, SRCPAINT);
	SelectObject(s_hSharedSpriteDC, hOldObj);

}

void CSprite::Process(float _fDeltaTick)
{
}

int CSprite::GetWidth() const
{
	return (m_bitmapSprite.bmWidth);
}

int CSprite::GetHeight() const
{
	return (m_bitmapSprite.bmHeight);
}

int CSprite::GetX() const
{
	return (m_iX);
}

int CSprite::GetY() const
{
	return (m_iY);
}

void CSprite::SetX(int _i)
{
	m_iX = _i;	
}

void CSprite::SetY(int _i)
{
	m_iY = _i;
}

int CSprite::GetDrawX() const
{
	return m_iDrawX;
}

int CSprite::GetDrawY() const
{
	return m_iDrawY;
}

void CSprite::SetDrawX(int _i)
{
	m_iDrawX = _i;
}

void CSprite::SetDrawY(int _i)
{
	m_iDrawY = _i;
}

void CSprite::TranslateRelative(int _iX, int _iY)
{
	m_iX += _iX;
	m_iY += _iY;
}

void CSprite::TranslateAbsolute(int _iX, int _iY)
{
	m_iX = _iX;
	m_iY = _iY;
}