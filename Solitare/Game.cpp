//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: Game.cpp
// Description	: Implementation for the game class
// Author		: Tom O'Brien, Kelsey Scheurich, Tom Butler
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// Local Includes
#include "Clock.h"
#include "Level.h"
#include "BackBuffer.h"
#include "utils.h"

// This Include
#include "Game.h"

// Static Variables
CGame* CGame::s_pGame = 0;

// Implementation

/***********************

 * CGame: Constructor
 * @author: 

 ********************/
CGame::CGame()
	: m_pLevel(0),	// Default to 0
		m_pClock(0),
		m_hApplicationInstance(0),
		m_hMainWindow(0),
		m_pBackBuffer(0)
{
}

/***********************

 * ~CGame: Destructor
 * @author: 

 ********************/
CGame::~CGame()
{
	// delete level, set to 0
	delete m_pLevel;
	m_pLevel = 0;

	// delete BackBuffer, set to 0
	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	// delete clock, set to 0
	delete m_pClock;
	m_pClock = 0;
}

/***********************

 * Initialise: Intialise game
 * @author: 
 * @parameter: HINSTANCE _hInstance, instance handler
 *				HWND _hWnd, window handler
 *				int _iWidth, width
 *				int _iHeight, heihght
 * @return: bool

 ********************/
bool CGame::Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight)
{
	// Set instance and window to respective variables
	m_hApplicationInstance = _hInstance;
	m_hMainWindow = _hWnd;

	// Create new clock and validate/initialise
	m_pClock = new CClock();
	VALIDATE(m_pClock ->Initialise());

	// Process clock
	m_pClock->Process();

	// Create new back buffer, validate/initialise
	m_pBackBuffer = new CBackBuffer();
	VALIDATE(m_pBackBuffer->Initialise(_hWnd, _iWidth, _iHeight));

	// Create new level, validate/initialise
	m_pLevel = new CLevel();
	VALIDATE(m_pLevel->Initialise(_iWidth, _iHeight));

	return (true);
}

/***********************

 * Draw: Draw game
 * @author: 

 ********************/
void CGame::Draw()
{
	// Clear buffer
	m_pBackBuffer->Clear();
	// Draw level
	m_pLevel->Draw();
	// call present
	m_pBackBuffer->Present();
}

/***********************

 * Process: Process game
 * @author: 
 * @parameter: float _fDeltaTick

 ********************/
void CGame::Process(float _fDeltaTick)
{
	// Process level
	m_pLevel->Process(_fDeltaTick);
}

/***********************

 * ExecuteOneFrame: Execute one frame of the game
 * @author: 

 ********************/
void CGame::ExecuteOneFrame()
{
	// Get delta tick
	float fDT = m_pClock->GetDeltaTick();
	// Process game using tick
	Process(fDT);
	// Draw game
	Draw();
	// Process clock
	m_pClock->Process();
	// Sleep for 1
	Sleep(1);
}

/***********************

 * GetInstance: Get instance of game
 * @author: 
 * @return: CGame&

 ********************/
CGame& CGame::GetInstance()
{
	// If game is 0
	if (s_pGame == 0)
	{
		// Create new game
		s_pGame = new CGame();
	}
	return (*s_pGame);
}

/***********************

 * GameOverWon: Bring up message for game won
 * @author: 

 ********************/
void CGame::GameOverWon()
{
	//Bring up message for game won
	MessageBox(m_hMainWindow, "Winner!", "Game Over", MB_OK);
	PostQuitMessage(0);
}

/***********************

 * GameOverLost: Bring up message for game lost
 * @author: 

 ********************/
void CGame::GameOverLost()
{
	// Bring up message for game lost
	MessageBox(m_hMainWindow, "Loser!", "Game Over", MB_OK);
	PostQuitMessage(0);
}

/***********************

 * DestroyInstance: Bring up message for game lost
 * @author: 

 ********************/
void CGame::DestroyInstance()
{
	// Delete and set to 0
	delete s_pGame;
	s_pGame = 0;
}

/***********************

 * GetBackBuffer: Get Back Buffer for game
 * @author: 
 * @return: CBackBuffer*

 ********************/
CBackBuffer* CGame::GetBackBuffer()
{
	return (m_pBackBuffer);
}

/***********************

 * GetLevel: Get level for game
 * @author: 
 * @return: CLevel*

 ********************/
CLevel* CGame::GetLevel()
{
	return (m_pLevel);
}

/***********************

 * GetAppInstance: Get instance for game
 * @author: 
 * @return: HINSTANCE

 ********************/
HINSTANCE CGame::GetAppInstance()
{
	return (m_hApplicationInstance);
}

/***********************

 * GetWindow: Get window for game
 * @author: 
 * @return: HWND

 ********************/
HWND CGame::GetWindow()
{
	return (m_hMainWindow);
}

/***********************

 * SetMouseCoords: Set mouse coordinates for game
 * @author: 
 * @parameters: int _x, x pos
 *				int _y, y pos

 ********************/
void CGame::SetMouseCoords(int _x, int _y)
{
	// Call level set mouse using xy
	m_pLevel->SetMouseCoords(_x,_y);
}

/***********************

 * SetMouseDown: Set mouse down for game
 * @author: 
 * @parameters: bool _bMouseDown

 ********************/
void CGame::SetMouseDown(bool _bMouseDown)
{
	// Call level set mouse using bool
	m_pLevel->SetMouseDown(_bMouseDown);
}

/***********************

 * GetMouseDown: Get mouse down for game
 * @author: 
 * @return bool 

 ********************/
bool CGame::GetMouseDown()
{
	return (m_pLevel->GetMouseDown());
}

/***********************

 * HandleMouseDrag: Handle mouse drag for game
 * @author: 

 ********************/
void CGame::HandleMouseDrag()
{
	// Call HandleMouseDrag for level
	m_pLevel->HandleMouseDrag();
}