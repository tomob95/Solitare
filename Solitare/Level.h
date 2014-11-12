//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: Level.cpp
// Description	: Implementation for the level class
// Author		: Tom O'Brien, Kelsey Scheurich, Tom Butler
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#pragma once

#if !defined(__LEVEL_H__)
#define __LEVEL_H__

// Library Includes
#include <Windows.h>
#include <vector>
#include <string>
using namespace std;

// Prototypes
class CCard;
class CDrawPile;
class CDeck;
class CHome;
class CColumn;
class CLevel
{

// Member Functions
public:
	// Constructor/destructor
	CLevel();
	~CLevel();

	bool Initialise(int _iWidth, int _iHeight);
	void Draw();
	void Process(float _fDeltaTick);
	void GetDeck(vector<CCard*> &_Target);
	void SetMouseCoords(int _x, int _y);
	void HandleMouseDrag();
	void HandleMouseDrop();
	bool CheckCardToColumn(CCard* _pSource, CCard* _pDestination);
	void SetMouseDown(bool _bMouseDown);
	bool GetMouseDown();
	bool IsMouseDraggingCards();
	void DeckClick();
	int GetDeckX();
	int GetDeckY();
	//static LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT _msg, WPARAM _wparam, LPARAM _lparam);

protected:
	bool ProcessCheckForWin();
	void UpdateScoreText(int _iScore);
	void DrawScore();

private:
	CLevel(const CLevel& _kr);
	CLevel& operator= (const CLevel& _kr);

// Member Variables
public:

protected:
	CDeck* m_pDeck;
	CDrawPile* m_pDraw;
	std::vector<CColumn*> m_pColumns;
	std::vector<CHome*> m_pAceHomes;
	std::vector<CCard*> m_pDraggedCards;
	int m_iDraggedCardsLastColumn;
	int m_iWidth;
	int m_iHeight;
	unsigned int m_iScore;
	bool m_bMouseDown;

	int m_fMouseX;
	int m_fMouseY;
};

#endif // __LEVEL_H__