//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: Entity.h
// Description	: Header for the Entity class
// Author		: Tom O'Brien, Kelsey Scheurich, Tom Butler
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#pragma once

#if !defined(__ENTITY_H__)
#define __ENTITY_H__

// Prototypes
class CSprite;
class CEntity
{

public:
	// Constructor/destructor
	CEntity();
	virtual ~CEntity();

	// Member Functions
	virtual bool Initialise(int _iDrawX, int _iDrawY);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	void SetX(int _f);
	void SetY(int _f);
	int GetX() const;
	int GetY() const;
	void SetDrawX(int _f);
	void SetDrawY(int _f);
	int GetDrawX() const;
	int GetDrawY() const;
	float GetHeight() const;
	float GetWidth() const;

protected:
private:
	CEntity(const CEntity& _kr);
	CEntity& operator= (const CEntity& _kr);

// Member Variables
public:
protected:
	CSprite* m_pSprite;
private:
};
#endif // __ENTITY_H__