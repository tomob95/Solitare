//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: BackBuffer.cpp
// Description	: Implementation for the BackBuffer class
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
// This Include
#include "Game.h"
using namespace std;

// Static Variables
CGame* CGame::s_pGame = 0;
// Static Function Prototypes

// Implementation

CGame::CGame()
: m_pLevel(0)
, m_pClock(0)
, m_hApplicationInstance(0)
, m_hMainWindow(0)
, m_pBackBuffer(0)
, m_bDeckStored(false)
{
}

CGame::~CGame()
{
	delete m_pLevel;
	m_pLevel = 0;

	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	delete m_pClock;
	m_pClock = 0;

	for(unsigned int i=0; i<m_pStoredResetDeck.size(); i++)
	{
		delete m_pStoredResetDeck[i];
	}
}

bool CGame::Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight)
{
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	m_hApplicationInstance = _hInstance;
	m_hMainWindow = _hWnd;

	m_pClock = new CClock();
	VALIDATE(m_pClock ->Initialise());

	m_pClock->Process();

	m_pBackBuffer = new CBackBuffer();
	VALIDATE(m_pBackBuffer->Initialise(_hWnd, _iWidth, _iHeight));

	m_pLevel = new CLevel();
	VALIDATE(m_pLevel->Initialise(_iWidth, _iHeight));

	//ShowCursor(false);
	return (true);
}

void CGame::Draw()
{
	m_pBackBuffer->Clear();
	m_pLevel->Draw();
	m_pBackBuffer->Present();
}

void CGame::Process(float _fDeltaTick)
{
	m_pLevel->Process(_fDeltaTick);
}

void CGame::ExecuteOneFrame()
{
	float fDT = m_pClock->GetDeltaTick();
	Process(fDT);
	Draw();
	m_pClock->Process();
	Sleep(1);
}

CGame& CGame::GetInstance()
{
	if (s_pGame == 0)
	{
		s_pGame = new CGame();
	}
	return (*s_pGame);
}

void CGame::DestroyInstance()
{
	delete s_pGame;
	s_pGame = 0;
}

CBackBuffer* CGame::GetBackBuffer()
{
	return (m_pBackBuffer);
}

CLevel* CGame::GetLevel()
{
	return (m_pLevel);
}

HINSTANCE CGame::GetAppInstance()
{
	return (m_hApplicationInstance);
}

HWND CGame::GetWindow()
{
	return (m_hMainWindow);
}

void CGame::SetMouseCoords(int _x, int _y)
{
	m_pLevel->SetMouseCoords(_x,_y);
}

void CGame::SetMouseDown(bool _bMouseDown)
{
	m_pLevel->SetMouseDown(_bMouseDown);
}

bool CGame::GetMouseDown()
{
	return (m_pLevel->GetMouseDown());
}

void CGame::HandleMouseDrag()
{
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
		return true;

	case WM_COMMAND:
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
		}
		break;
	}

	return false;
}