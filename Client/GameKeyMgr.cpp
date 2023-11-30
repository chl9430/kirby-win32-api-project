#include "pch.h"
#include "GameKeyMgr.h"

GameKeyMgr::GameKeyMgr()
	: m_vecKey{}
{
}

GameKeyMgr::~GameKeyMgr()
{
}

void GameKeyMgr::Init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}