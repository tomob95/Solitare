#include "Column.h"
#include "utils.h"

CColumn::CColumn(void)
{
}


CColumn::~CColumn(void)
{
}

void CColumn::Draw()
{
	if(IsEmpty())
	{
		CEntity::Draw();
	}
	else
	{
		//Draw each card in the column
		for (unsigned int i = 0; i<m_pPile.size(); i++)
		{
			m_pPile[i]->Draw();
		}
	}
}

bool CColumn::Initialise(int _iDrawX, int _iDrawY)
{
	VALIDATE(CEntity::Initialise(_iDrawX, _iDrawY));

	return 0;
}

void CColumn::Process(float _fDeltaTick)
{
	if (IsEmpty())
	{
		//Set Sprite to the empty sprite
		CEntity::SetDrawX(6 * CARD_WIDTH);
		CEntity::SetDrawY(4 * CARD_HEIGHT);

	}
	else
	{
		//Draw each card in the column
		for (unsigned int i = 0; i<m_pPile.size(); i++)
		{
			if (!m_pPile[i]->GetFaceUp())
			{
				m_pPile[i]->SetDrawX(BACK_X);
				m_pPile[i]->SetDrawY(BACK_Y);
			}
		//	if(!m_pPile[i]->GetDragged())
		//	{
				m_pPile[i]->SetX(static_cast<int>(GetX()));
				m_pPile[i]->SetY(static_cast<int>(GetY() + (i * 58)));
		//	}
			m_pPile[i]->Process(_fDeltaTick);
		}
	}
	CEntity::Process(_fDeltaTick);
}

bool CColumn::IsEmpty()
{
	return m_pPile.empty();
}

CCard* CColumn::GetTopCard()
{
	return m_pPile.back();
}