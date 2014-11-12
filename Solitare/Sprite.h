//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: Sprite.h
// Description	: Header for the sprite class
// Author		: Tom O'Brien, Kelsey Scheurich, Tom Butler
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#pragma once

#if !defined(__SPRITE_H__)
#define __SPRITE_H__

// Library Includes
#include "windows.h"

// Prototypes
class CSprite
{
// Member Functions
public:
	// Constructor/destructor
	CSprite();
	~CSprite();

	bool Initialise(int _iDrawX, int _iDrawY);
	void Draw();
	int GetWidth() const;
	int GetHeight() const;
	int GetX() const;
	int GetY() const;
	void SetX(int _i);
	void SetY(int _i);
	int GetDrawX() const;
	int GetDrawY() const;
	void SetDrawX(int _i);
	void SetDrawY(int _i);
	void TranslateRelative(int _iX, int _iY);
	void TranslateAbsolute(int _iX, int _iY);

protected:
private:
	CSprite(const CSprite& _kr);
	CSprite& operator= (const CSprite& _kr);

// Member Variables
public:
protected:
	//Center handle
	int m_iX;
	int m_iY;
	int m_iDrawX;
	int m_iDrawY;
	HBITMAP m_hSprite;
	BITMAP m_bitmapSprite;
	static HDC s_hSharedSpriteDC;
	static int s_iRefCount;

private:
};
#endif // __SPRITE_H__