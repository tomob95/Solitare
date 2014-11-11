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

#include "Home.h"
#include "Card.h"
#include "Level.h"
#include <list>

CHome::CHome()
{
}


CHome::~CHome()
{
}

bool CHome::Initialise(int _iDrawX, int _iDrawY)
{
	VALIDATE(CEntity::Initialise(_iDrawX, _iDrawY));
	return true;
}

void CHome::Draw()
{
	CEntity::Draw();
}

void CHome::Process(float _fDeltaTick)
{
	if (IsEmpty())
	{
		//Set Sprite to the empty sprite
		CEntity::SetDrawX(6 * CARD_WIDTH);
		CEntity::SetDrawY(4 * CARD_HEIGHT);
	}
	else
	{
		//draw card back sprite
		SetDrawX(BACK_X);
		SetDrawY(BACK_Y);
		/*if(CCard().GetDragged() == true)
		{
			switch(CCard().GetFace())
			{
			case 0: 
				{
					if(m_pHome.size() == 0)
					{
						m_pHome.push_back(0);
					}
				}
				case 1: 
				{
					if(m_pHome.size() == 1)
					{
						m_pHome.push_back(1);
					}
				}
				case 2: 
				{
					if(m_pHome.size() == 2)
					{
						m_pHome.push_back(2);
					}
				}
				case 3: 
				{
					if(m_pHome.size() == 3)
					{
						m_pHome.push_back(3);
					}
				}
				case 4: 
				{
					if(m_pHome.size() == 4)
					{
						m_pHome.push_back(4);
					}
				}
				case 5: 
				{
					if(m_pHome.size() == 5)
					{
						m_pHome.push_back(5);
					}
				}
				case 6: 
				{
					if(m_pHome.size() == 6)
					{
						m_pHome.push_back(6);
					}
				}
				case 7: 
				{
					if(m_pHome.size() == 7)
					{
						m_pHome.push_back(7);
					}
				}
				case 8: 
				{
					if(m_pHome.size() == 8)
					{
						m_pHome.push_back(8);
					}
				}
				case 9: 
				{
					if(m_pHome.size() == 9)
					{
						m_pHome.push_back(9);
					}
				}
				case 10: 
				{
					if(m_pHome.size() == 10)
					{
						m_pHome.push_back(10);
					}
				}
				case 11: 
				{
					if(m_pHome.size() == 11)
					{
						m_pHome.push_back(11);
					}
				}
				case 12: 
				{
					if(m_pHome.size() == 12)
					{
						m_pHome.push_back(12);
					}
				}
				break;
			}
		}*/
	}
}

bool CHome::IsEmpty()
{
	return m_pHome.empty();
}