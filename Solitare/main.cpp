//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: Main.cpp
// Description	: Main implementation of the program
// Author		: Tom O'Brien, Kelsey Scheurich, Tom Butler
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#define WIN32_LEAN_AND_MEAN

// Library includes
#include <windows.h> // Include all the windows headers.
#include <windowsx.h> // Include useful macros.
#include <vector>
#include <codecvt>
#include <locale>
#include <ctime>
#include "vld.h"

// Local includes
#include "Game.h"
#include "Level.h"
#include "utils.h"
#include "resource.h"

#define WINDOW_CLASS_NAME "WINCLASS1"

//Struct and Enum Declarations



/***********************

 * WindowProc: Windows message handler
 * @parameter: HWND _hwnd, window handler
				UINT _msg, message
				WPARAM _wparam,	
				LPARAM _lparam
 * @return:

 ********************/
LRESULT CALLBACK WindowProc(HWND _hwnd,	UINT _msg,	WPARAM _wparam,	LPARAM _lparam)
{

	// This is the main message handler of the system.
	PAINTSTRUCT ps; // Used in WM_PAINT.
	HDC hdc; // Handle to a device context.

	// What is the message?
	switch (_msg)
	{
	case WM_CREATE:
	{
		// Do initialization stuff here.
		// Return Success.
		return (0);
	}
		break;
	case WM_PAINT:
	{
		// Validate the window.
		hdc = BeginPaint(_hwnd, &ps);
		// All painting here
		EndPaint(_hwnd, &ps);
		// Return Success.
		return (0);
	}
		break;

	case WM_COMMAND:
		switch(_wparam)
		{
			case ID_FILE_EXIT:
			{
				PostQuitMessage(0);
				return false;
			}
				break;
			case ID_FILE_NEWGAME:
			{
				CGame::GetInstance().NewGame();
				return true;
			}
				break;
			case ID_FILE_RESTARTGAME:
			{
				CGame::GetInstance().RestartGame();
				return true;
			}
				break;
			case ID_HELP:
				{
					DialogBox(CGame::GetInstance().GetAppInstance(), MAKEINTRESOURCE(IDD_DIALOG2), CGame::GetInstance().GetWindow(),  (DLGPROC)CGame::DlgProc);
					return true;
				}
				break;
		}
		break;

	case WM_KEYDOWN:
	{
		switch(_wparam)
		{
		case VK_ESCAPE:
			{
				PostQuitMessage(0);
			}
		case VK_F2:
			{
				CGame::GetInstance().RestartGame();
			}
			break;
		case VK_F1:
			{
				CGame::GetInstance().NewGame();
			}
			break;
		}
	}
		break;

	// On mouse move
	case WM_MOUSEMOVE:
	{
		// Call GetInstance of game and set new mouse coordinates
		CGame::GetInstance().SetMouseCoords(LOWORD(_lparam), HIWORD(_lparam));
	}
		break;

	// If left mouse button is pressed
	case WM_LBUTTONDOWN:
	{
		//Get Mouse Coords
		if(!CGame::GetInstance().GetLevel()->IsMouseDraggingCards())
		{
			int _iMouseX = LOWORD(_lparam); 
			int _iMouseY = HIWORD(_lparam);
			CGame::GetInstance().SetMouseCoords(_iMouseX, _iMouseY);
			int _iDeckX = CGame::GetInstance().GetLevel()->GetDeckX();
			int _iDeckY = CGame::GetInstance().GetLevel()->GetDeckY();

			// If mouse is over deck
			if( ( _iMouseX >= _iDeckX ) && ( _iMouseX < _iDeckX+CARD_WIDTH )
			&& ( _iMouseY >= _iDeckY ) && ( _iMouseY < _iDeckY+CARD_HEIGHT ) )
			{
				// Call deck click function
				CGame::GetInstance().GetLevel()->DeckClick();
				break;
			}

			// Set mousedown to true for game instance
			CGame::GetInstance().SetMouseDown(true);
			CGame::GetInstance().GetLevel()->HandleMouseDrag();
		}
	}
		break;

	// If left mouse button is released
	case WM_LBUTTONUP:
	{
		if(CGame::GetInstance().GetLevel()->IsMouseDraggingCards())
		{
			// Set mousedown to true for game instance
			CGame::GetInstance().SetMouseDown(false);
			CGame::GetInstance().GetLevel()->HandleMouseDrop();
		}
	}
		break;

	case WM_DESTROY:
	{
		// Kill the application, this sends a WM_QUIT message.
		PostQuitMessage(0);
		// Return success.
		return (0);
	}
		break;
	default:break;
	} // End switch.

	// Process any messages that we did not take care of...
	return (DefWindowProc(_hwnd, _msg, _wparam, _lparam));
}

/***********************

 * WinMain: Main function for window
 * @parameter: HINSTANCE _hInstance, game instance
 *				HINSTANCE _hPrevInstance, previous instance
 *				LPSTR _lpCmdLine, command line
 *				int _nCmdShow, command show
 * @return:

 ********************/
int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance,	LPSTR _lpCmdLine,	int _nCmdShow)
{
	// This will hold the class we create.
	WNDCLASSEX winclass; 
	MSG msg; // Generic message.
	HMENU Menu = LoadMenu(_hInstance, MAKEINTRESOURCE(IDR_MENU1));
	// Create const ints for window width and height
	const int WINDOW_WIDTH = 1300;
	const int WINDOW_HEIGHT = 1080;

	// Window class structure.
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = CreateSolidBrush(RGB(41,63,151));
	winclass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register the window class
	if (!RegisterClassEx(&winclass))
	{
		return (0);
	}

	// create the window
	hwnd =	CreateWindowEx(NULL,				// Extended style.
			WINDOW_CLASS_NAME,					// Class.
			"Solitare",						// Title.
			(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) | WS_VISIBLE,
			0, 0,								// Initial x,y.
			WINDOW_WIDTH, WINDOW_HEIGHT,		// Initial width, height.
			NULL,								// Handle to parent.
			Menu,								// Handle to menu.
			_hInstance,							// Instance of this application.
			NULL);								// Extra creation parameters.

	// If there is no window
	if (!(hwnd))
	{
		return (0);
	}

	//Get current monitor Height and Width
	HMONITOR monitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
	MONITORINFO info;
	info.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(monitor, &info);
	int monitor_width = info.rcMonitor.right - info.rcMonitor.left;
	int monitor_height = info.rcMonitor.bottom - info.rcMonitor.top;
	//Resize the window to the height of the monitor
	SetWindowPos(hwnd,0,0,0,WINDOW_WIDTH,monitor_height-50,SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);	
	
	// Seed random
	srand((unsigned int)time(0));

	//Run the initialization, set up the game
	CGame& Game = CGame::GetInstance();
	Game.Initialise(_hInstance, hwnd, WINDOW_WIDTH, monitor_height-50);
	
	// Enter main event loop
	while (true)
	{
		// Test if there is a message in queue, if so get it.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Test if this is a quit.
			if (msg.message == WM_QUIT)
			{
				break;
			}
			// Translate any accelerator keys.
			TranslateMessage(&msg);
			// Send the message to the window proc.
			DispatchMessage(&msg);
		}
			// Main game processing goes here.
			Game.ExecuteOneFrame(); //One frame of game logic occurs here...
	}
	// Return to Windows like this...
	delete &Game;
	return (static_cast<int>(msg.wParam));
}
