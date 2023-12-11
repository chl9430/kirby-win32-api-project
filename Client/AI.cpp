#include "pch.h"
#include "AI.h"

#include "GameState.h"

AI::AI()
	: m_mapState{}
	, m_pCurState{ nullptr }
	, m_pOwner{ nullptr }
{
}

AI::~AI()
{
	Safe_Delete_Map(m_mapState);
}

void AI::Update()
{
	m_pCurState->Update();
}

void AI::AddState(GameState* _pState)
{
	GameState* pState = GetState(_pState->GetType());
	assert(!pState);

	m_mapState.insert(make_pair(_pState->GetType(), _pState));
	_pState->m_pAI = this;
}

GameState* AI::GetState(MON_STATE _eState)
{
	map<MON_STATE, GameState*>::iterator iter = m_mapState.find(_eState);
	if (iter == m_mapState.end())
		return nullptr;

	return iter->second;
}

void AI::SetCurState(MON_STATE _eState)
{
	m_pCurState = GetState(_eState);
	assert(m_pCurState);
}