#include "pch.h"
#include "GameCollisionMgr.h"

GameCollisionMgr::GameCollisionMgr()
	: m_arrCheck{}
{
}

GameCollisionMgr::~GameCollisionMgr()
{
}

void GameCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	UINT iRow = (UINT)_eLeft; // 콜리젼 2차원 배열의 열
	UINT iCol = (UINT)_eRight; // 콜리젼 2차원 배열의 행

	if (iRow > iCol)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}
}