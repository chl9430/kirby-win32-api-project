#include "pch.h"
#include "GameAnimator.h"

#include "GameAnimation.h"

GameAnimator::GameAnimator()
	: m_mapAnim{}
	, m_pOwner{}
	, m_pCurAnim{ nullptr }
	, m_bRepeat{ false }
{
}

GameAnimator::~GameAnimator()
{
	Safe_Delete_Map(m_mapAnim);
}

void GameAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_strName);
	m_bRepeat = _bRepeat;
}

GameAnimation* GameAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, GameAnimation*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void GameAnimator::LoadAnimation(const wstring& _strRelativePath)
{
	GameAnimation* pAnim = new GameAnimation;
	pAnim->Load(_strRelativePath);

	pAnim->m_pAnimator = this;
	m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim));
}