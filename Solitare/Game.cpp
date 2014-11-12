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


// Library Includes
#include <vector>

// Local Includes
#include "Clock.h"
#include "Card.h"
#include "Level.h"
#include "BackBuffer.h"
#include "utils.h"
#include "resource.h"

// This Include
#include "Game.h"

using namespace std;


// Static Variables
CGame* CGame::s_pGame = 0;

// Implementation

/***********************

 * CGame: Constructor
 * @author: 

 ********************/
CGame::CGame()
: m_pLevel(0) // Default to 0
, m_pClock(0)
, m_hApplicationInstance(0)
, m_hMainWindow(0)
, m_pBackBuffer(0)
, m_bDeckStored(false)
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

	for(unsigned int i=0; i<m_pStoredResetDeck.size(); i++)
	{
		delete m_pStoredResetDeck[i];
	}
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
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

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

bool CGame::IsDeckStored()
{
	return m_bDeckStored;
}

void CGame::StoreGameDeck()
{
	m_bDeckStored = true;
	m_pLevel->GetDeck(m_pStoredResetDeck);
}

void CGame::GetStoredDeck(vector<CCard*> &_pTarget)
{

	_pTarget.resize(52);
	copy(m_pStoredResetDeck.begin(),m_pStoredResetDeck.end(),_pTarget.begin());

}


void CGame::RestartGame()
{
	delete m_pLevel;
	m_pLevel = 0;
	delete m_pBackBuffer;
	m_pBackBuffer = 0;
	delete m_pClock;
	m_pClock = 0;

	Initialise(m_hApplicationInstance, m_hMainWindow, m_iWidth, m_iHeight);
}

void CGame::NewGame()
{
	delete m_pLevel;
	m_pLevel = 0;
	delete m_pBackBuffer;
	m_pBackBuffer = 0;
	delete m_pClock;
	m_pClock = 0;
	while(!m_pStoredResetDeck.empty())
	{
		CCard* _pTemp = m_pStoredResetDeck.back();
		m_pStoredResetDeck.pop_back();
		delete _pTemp;
	}
	m_bDeckStored = 0;
	Initialise(m_hApplicationInstance, m_hMainWindow, m_iWidth, m_iHeight);
}

/***********************

 * DlgProc: handle the dialog box functions
 * @parameter: HWND hWndDlg, dialog handler
				UINT _msg, message
				WPARAM _wparam,	
				LPARAM _lparam
 * @return:

 ********************/
LRESULT CALLBACK CGame::DlgProc(HWND hWndDlg, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	switch(_msg)
	{
	case WM_INITDIALOG:
		{
			char* _Instructions = "- The aim of the game is to sort all the cards into the four suit piles at \nthe top right of the screen, from lowest (ace) to highest (king).\n- There are 7 columns in the lower portion of the screen. The first column\nhas one card, the second two, etc. The topmost card is face up.\n- Only cards that are face up can be moved or have other face up cards placed\non top of them, and these must be the opposite color to the card below.\n- Cards within the columns must be in decending order with alternating color,\nfrom highest (king) to lowest (ace).\n- The remaining 24 cards are in the deck, top left of the screen. You can click\non the deck to draw a card, which you can then choose to add to \nyour columns. You can't reshuffle the deck.\n- If you run out of cards in the deck, simply click again to flip the drawn\n	pile back onto the deck.\n- If there is an empty space in a column, only a king may be placed there.\n- Click and drag cards to move them, and click again to drop them into place.\n- You gain points for various moves:\n	- 5 points if you move a card to a place within a column\n	- 10 points if you move a card to a suit pile\n	- 5 points for flipping a card to face up";
			SetDlgItemText(hWndDlg,IDC_SCORE,ToString(CGame::GetInstance().GetLevel()->GetScore()).c_str());
			SetDlgItemText(hWndDlg,IDC_INSTRUCTIONS,ToString(_Instructions).c_str());

			return true;
		}
		break;

	case WM_COMMAND:
		{
			switch(_wparam)
			{
				case IDC_EXIT:
				{
					PostQuitMessage(0);
					return false;
				}
					break;
				case IDC_NEWGAME:
				{
					CGame::GetInstance().NewGame();
					EndDialog(hWndDlg, 0);
					return true;
				}
					break;
				case IDC_RESTARTGAME:
				{
					CGame::GetInstance().RestartGame();
					EndDialog(hWndDlg, 0);
					return true;
				}
					break;
				case IDOK:
				{
					EndDialog(hWndDlg, 0);
					return true;
				}
					break;
			}
			break;
		}
		break;

	case WM_CLOSE:
		{
		EndDialog(hWndDlg, 0);
		return true;
		}
		break;
	}


	return false;
}