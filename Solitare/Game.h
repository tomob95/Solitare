//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: Game.h
// Description	: Header for the game class
// Author		: Tom O'Brien, Kelsey Scheurich, Tom Butler
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#pragma once

#if !defined(__GAME_H__)
#define __GAME_H__

// Library Includes
#include <windows.h>

// Local Includes
#include "clock.h"

// Prototypes
class CLevel;
class CBackBuffer;
class CGame
{
// Member Functions
public:
	// destructor
	virtual ~CGame();

	virtual bool Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	void ExecuteOneFrame();
	CBackBuffer* GetBackBuffer();
	CLevel* GetLevel();
	HINSTANCE GetAppInstance();
	HWND GetWindow();
	void GameOverWon();
	void GameOverLost();
	void SetMouseCoords(int _x, int _y);
	void SetMouseDown(bool _bMouseDown);
	bool GetMouseDown();
	void HandleMouseDrag();

	// Singleton Methods
	static CGame& GetInstance();
	static void DestroyInstance();

protected:
private:
	// Constructor
	CGame();

	CGame(const CGame& _kr);
	CGame& operator= (const CGame& _kr);

// Member Variables
public:
protected:
	CClock* m_pClock;
	CLevel* m_pLevel;
	CBackBuffer* m_pBackBuffer;

	//Application data
	HINSTANCE m_hApplicationInstance;
	HWND m_hMainWindow;

	// Singleton Instance
	static CGame* s_pGame;

private:
};
#endif // __GAME_H__