//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: Clock.cpp
// Description	: Implementation for the clock class
// Author		: Tom O'Brien, Kelsey Scheurich, Tom Butler
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

// Library Includes
#include <windows.h>
// Local Includes
#include "Clock.h"

// Implementation
/***********************

 * CClock: Constructor
 * @author: 

 ********************/
CClock::CClock()
	: m_fTimeElapsed(0.0f),	// Default all to 0
	  m_fDeltaTime(0.0f),
	  m_fLastTime(0.0f),
	  m_fCurrentTime(0.0f)
{
}

/***********************

 * ~CClock: Deconstructor
 * @author:
 * @parameter: 
 * @return:

 ********************/
CClock::~CClock()
{
}

/***********************

 * Initialise: Set up clock
 * @author:  
 * @return: bool

 ********************/
bool CClock::Initialise()
{
	return (true);
}

/***********************

 * Process: Process the clock
 * @author:  

 ********************/
void CClock::Process()
{
	// Set last time as current time
	m_fLastTime = m_fCurrentTime;
	// Set member variable as current time
	m_fCurrentTime = static_cast<float>(timeGetTime());

	// If last time is 0
	if (m_fLastTime == 0.0f)
	{
		// set last time as current time
		m_fLastTime = m_fCurrentTime;
	}

	// Set delta to current time minus last the last time
	m_fDeltaTime = m_fCurrentTime - m_fLastTime;
	// Add elapsed time plus delta pick
	m_fTimeElapsed += m_fDeltaTime;
}

/***********************

 * GetDeltaTick: Get the delta tick
 * @author:  
 * @return: float

 ********************/
float CClock::GetDeltaTick()
{
	// Calculate delta tick and return
	return (m_fDeltaTime / 1000.0f);
}