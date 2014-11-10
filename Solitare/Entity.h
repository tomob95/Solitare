#pragma once
#if !defined(__ENTITY_H__)
#define __ENTITY_H__
// Library Includes
// Local Includes
// Types
// Constants
// Prototypes
class CSprite;
class CEntity
{
// Member Functions
public:
	CEntity();
	virtual ~CEntity();
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