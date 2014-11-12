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

/***********************

 * CSprite: Constructor
 * @author: 

 ********************/
CSprite::CSprite()
	: m_iX(0), m_iY(0) // Default to 0
{
	++s_iRefCount;
}

/***********************

 * ~CSprite: Destructor
 * @author: 

 ********************/
CSprite::~CSprite()
{
	// Delete sprite
	DeleteObject(m_hSprite);
	// Decrease count
	--s_iRefCount;
	
	// If count is 0
	if (s_iRefCount == 0)
	{
		// delete
		DeleteDC(s_hSharedSpriteDC);
		s_hSharedSpriteDC = 0;
	}
}

/***********************

 * Initialise: Initialise the sprite
 * @author: 
 * @parameter: int _iDrawX, x pos
 *				int _iDrawY, y pos
 * @return: bool

 ********************/
bool CSprite::Initialise(int _iDrawX, int _iDrawY)
{
	// Get game instance
	HINSTANCE hInstance = CGame::GetInstance().GetAppInstance();

	// If not shared sprite
	if (!s_hSharedSpriteDC)
	{
		// Create one
		s_hSharedSpriteDC = CreateCompatibleDC(NULL);
	}

	// Set x & y pos
	m_iDrawX = 132 * _iDrawX;
	m_iDrawY = 192 * _iDrawY;

	// Load bitmap into sprite
	m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_CARDS));
	GetObject(m_hSprite, sizeof(BITMAP), &m_bitmapSprite);

	return (true);
}

/***********************

 * Draw: Draw the sprite
 * @author:

 ********************/
void CSprite::Draw()
{
	// Get back buffer
	CBackBuffer* pBackBuffer = CGame::GetInstance().GetBackBuffer();

	// Set old object to shared sprite
	HGDIOBJ hOldObj = SelectObject(s_hSharedSpriteDC, m_hSprite);
	// Draw
	BitBlt(pBackBuffer->GetBFDC(), m_iX, m_iY, CARD_WIDTH, CARD_HEIGHT, s_hSharedSpriteDC, MASK_X, MASK_Y, SRCAND);
	BitBlt(pBackBuffer->GetBFDC(), m_iX, m_iY, CARD_WIDTH, CARD_HEIGHT, s_hSharedSpriteDC, m_iDrawX, m_iDrawY, SRCPAINT);
	SelectObject(s_hSharedSpriteDC, hOldObj);

}

/***********************

 * GetWidth: Get width of sprite
 * @author:
 * @return: int

 ********************/
int CSprite::GetWidth() const
{
	return (m_bitmapSprite.bmWidth);
}

/***********************

 * GetHeight: Get height of sprite
 * @author:
 * @return: int

 ********************/
int CSprite::GetHeight() const
{
	return (m_bitmapSprite.bmHeight);
}

/***********************

 * GetX: Get x pos of sprite
 * @author:
 * @return: int

 ********************/
int CSprite::GetX() const
{
	return (m_iX);
}

/***********************

 * GetY: Get y pos of sprite
 * @author:
 * @return: int

 ********************/
int CSprite::GetY() const
{
	return (m_iY);
}

/***********************

 * SetX: Set x pos of sprite
 * @author:
 * @parameter: int _i, x pos

 ********************/
void CSprite::SetX(int _i)
{
	m_iX = _i;	
}

/***********************

 * SetY: Set y pos of sprite
 * @author:
 * @parameter: int _i, y pos

 ********************/
void CSprite::SetY(int _i)
{
	m_iY = _i;
}

/***********************

 * GetDrawX: Get draw x pos of sprite
 * @author:
 * @return: int

 ********************/
int CSprite::GetDrawX() const
{
	return( m_iDrawX );
}

/***********************

 * GetDrawY: Get draw y pos of sprite
 * @author:
 * @return: int

 ********************/
int CSprite::GetDrawY() const
{
	return( m_iDrawY );
}

/***********************

 * SetDrawX: Set draw x pos of sprite
 * @author:
 * @parameter: int _i

 ********************/
void CSprite::SetDrawX(int _i)
{
	m_iDrawX = _i;
}

/***********************

 * SetDrawY: Set draw y pos of sprite
 * @author:
 * @parameter: int _i

 ********************/
void CSprite::SetDrawY(int _i)
{
	m_iDrawY = _i;
}

/***********************

 * TranslateRelative: Translate sprite relative to current position
 * @author:
 * @parameter: int _iX, x pos
 *				int _iY, y pos

 ********************/
void CSprite::TranslateRelative(int _iX, int _iY)
{
	m_iX += _iX;
	m_iY += _iY;
}

/***********************

 * TranslateAbsolute: Translate sprite to new position
 * @author:
 * @parameter: int _iX, x pos
 *				int _iY, y pos

 ********************/
void CSprite::TranslateAbsolute(int _iX, int _iY)
{
	m_iX = _iX;
	m_iY = _iY;
}