#include "pch.h"
#include "GameState.h"

GameState::GameState(MON_STATE _eState)
	: m_eState{ _eState }
	, m_pAI{ nullptr }
{
}

GameState::~GameState()
{
}