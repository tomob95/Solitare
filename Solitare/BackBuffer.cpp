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

// This include
#include "BackBuffer.h"

// Implementation
/***********************

 * CBackBuffer: Constructor for BackBuffer class
 * @author: 

 ********************/
CBackBuffer::CBackBuffer()
			: m_hWnd(0)			// Default all to 0
			, m_hDC(0)
			, m_hSurface(0)
			, m_hOldObject(0)
			, m_iWidth(0)
			, m_iHeight(0)
{
}

/***********************

 * ~CBackBuffer: Deconstructor
 * @author: 

 ********************/
CBackBuffer::~CBackBuffer()
{
	// Delete member variable objects
	SelectObject(m_hDC, m_hOldObject);
	DeleteObject(m_hSurface);
	DeleteObject(m_hDC);
}

/***********************

 * Initialise: Initialise the backbuffer
 * @author:
 * @parameter: HWND _hWnd, window handler
 *				int _iWidth, width 
 *				int _iHeight, height
 * @return: bool

 ********************/
bool CBackBuffer::Initialise(HWND _hWnd, int _iWidth, int _iHeight)
{
	// Set member variables to window, width and height
	m_hWnd = _hWnd;
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	// Retrieve window, add to member variable
	HDC hWindowDC = ::GetDC(m_hWnd);
	m_hDC = CreateCompatibleDC(hWindowDC);
	// Create bitmap compatible surface on window
	m_hSurface = CreateCompatibleBitmap(hWindowDC, m_iWidth, m_iHeight);
	ReleaseDC(m_hWnd, hWindowDC);

	// Cast surface to bitmap
	m_hOldObject = static_cast<HBITMAP>(SelectObject(m_hDC, m_hSurface));
	// Paintbrushes
	HBRUSH brushWhite = CreateSolidBrush(RGB(41,63,151));
	HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(m_hDC, brushWhite));

	// Create rectangle using width and height
	Rectangle(m_hDC, 0, 0, m_iWidth, m_iHeight);
	SelectObject(m_hDC, oldBrush);

	return (true);
}

/***********************

 * Clear: Clears the screen
 * @author: 

 ********************/
void CBackBuffer::Clear()
{
	// Create new brush
	HBRUSH hOldBrush = 	CreateSolidBrush(RGB(41,63,151));
	// Create rectangle
	Rectangle(GetBFDC(), 0, 0, GetWidth(), GetHeight());
	// Paint rectangle
	SelectObject(GetBFDC(), hOldBrush);
}

/***********************

 * GetBFDC: Get BFDC
 * @author: 
 * @return: HDC

 ********************/
HDC CBackBuffer::GetBFDC() const
{
	// Return member variable
	return (m_hDC);
}

/***********************

 * GetWidth: Get window width
 * @author: 
 * @return: int

 ********************/
int CBackBuffer::GetWidth() const
{
	// Return member variable
	return (m_iWidth);
}

/***********************

 * GetHeight: Get window height
 * @author: 
 * @return: int

 ********************/
int CBackBuffer::GetHeight() const
{
	// Return member variable
	return (m_iHeight);
}

/***********************

 * Present: Current position of buffer
 * @author: 

 ********************/
void CBackBuffer::Present()
{
	// Window handler = current member variable
	HDC hWndDC = ::GetDC(m_hWnd);
	// Transfer data
	BitBlt(hWndDC, 0, 0, m_iWidth, m_iHeight, m_hDC, 0, 0, SRCCOPY);
	// Release window
	ReleaseDC(m_hWnd, hWndDC);
}