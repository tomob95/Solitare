#pragma once
#if !defined(__LEVEL_H__)
#define __LEVEL_H__
// Library Includes
#include <vector>
#include <string>
// Local Includes
// Types
// Constants
// Prototypes
class CCard;
class CDeck;
class CHome;
class CColumn;
class CLevel
{

// Member Functions
public:
	CLevel();
	~CLevel();
	bool Initialise(int _iWidth, int _iHeight);
	void Draw();
	void Process(float _fDeltaTick);
	CDeck* GetDeck() const;
protected:
	void ProcessCheckForWin();
	void UpdateScoreText();
	void DrawScore();
private:
	CLevel(const CLevel& _kr);
	CLevel& operator= (const CLevel& _kr);

// Member Variables
public:
protected:
	CDeck* m_pDeck;
	std::vector<CColumn*> m_pColumn;
	int m_iWidth;
	int m_iHeight;
	std::wstring m_strScore;
private:
};

#endif // __LEVEL_H__