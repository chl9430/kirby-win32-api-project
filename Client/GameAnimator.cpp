#include "pch.h"
#include "GameAnimator.h"

#include "GameAnimation.h"

GameAnimator::GameAnimator()
	: m_mapAnim{}
	, m_pOwner{}
	, m_pCurAnim{ nullptr }
	, m_bRepeat{ false }
	, m_pPrevAnim{ nullptr }
{
}

GameAnimator::~GameAnimator()
{
	Safe_Delete_Map(m_mapAnim);
}

void GameAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pPrevAnim = m_pCurAnim;
	m_pCurAnim = FindAnimation(_strName);
	if (m_pPrevAnim != m_pCurAnim)
	{
		m_pCurAnim->SetFrame(0);
	}
	m_bRepeat = _bRepeat;
}

void GameAnimator::CreateAnimation(const wstring& _strName, GameTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	GameAnimation* pAnim = FindAnimation(_strName);

	assert(nullptr == pAnim); // 키값이 이미 추가된 애니메이션의 키값이라면 프로그램 종료

	pAnim = new GameAnimation;
	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;
	pAnim->Create(_strName, _pTex, _vLT, _vSliceSize, _vStep, _fDuration, _iFrameCount);

	m_mapAnim.insert(make_pair(_strName, pAnim));
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

void GameAnimator::FinalUpdate()
{
	if (m_pCurAnim != nullptr)
	{
		m_pCurAnim->Update();

		if (m_bRepeat && m_pCurAnim->IsFinish())
		{
			m_pCurAnim->SetFrame(0);
		}
	}
}

void GameAnimator::Render(HDC _dc)
{
	if (nullptr != m_pCurAnim)
		m_pCurAnim->Render(_dc);
}