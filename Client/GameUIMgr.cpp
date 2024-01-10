#include "pch.h"
#include "GameUIMgr.h"

#include "GameSceneMgr.h"
#include "GameKeyMgr.h"

#include "GameObject.h"
#include "GameScene.h"
#include "GameUI.h"

GameUIMgr::GameUIMgr()
	: m_pFocusedUI{ nullptr }
{

}

GameUIMgr::~GameUIMgr()
{

}

GameUI* GameUIMgr::GetFocusedUI()
{
	GameScene* pCurScene = GameSceneMgr::GetInst()->GetCurScene();
	vector<GameObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	// 기존 포커싱 된 UI를 받아두고 변경되었는지 확인한다.
	GameUI* pFocusedUI = m_pFocusedUI;

	/*if (!bLbtnTap)
	{
		return pFocusedUI;
	}*/

	// 왼쪽버튼 클릭이 발생했다면
	vector<GameObject*>::iterator targetIter = vecUI.end();
	vector<GameObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (((GameUI*)*iter)->IsMouseOn())
		{
			targetIter = iter;
		}
	}

	// 이번에 Focus 된 UI가 없다.
	if (vecUI.end() == targetIter)
	{
		return nullptr;
	}

	pFocusedUI = (GameUI*)*targetIter;

	// 벡터 내에서 맨뒤로 순번을 교체
	vecUI.erase(targetIter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

GameUI* GameUIMgr::GetTargetedUI(GameUI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	// 부모 포함 모든 자식들을 검사
	GameUI* pTargetUI = nullptr;

	static list<GameUI*> queue;
	static vector<GameUI*> vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	// 큐가 빌때까지 반복문을 실행한다.
	while (!queue.empty())
	{
		// 큐에서 데이터 하나 꺼내기
		GameUI* pUI = queue.front();
		queue.pop_front();

		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);
			}
			pTargetUI = pUI;
		}
		else
		{
			vecNoneTarget.push_back(pUI);
		}

		const vector<GameUI*>& vecChild = pUI->GetChildUI();

		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
	}

	// 왼쪽 버튼을 떼면, 눌렀던 체크를 다시 해제한다.
	if (bLbtnAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}

	return pTargetUI;
}

void GameUIMgr::Update()
{
	// 포커싱 된 UI 확인
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI)
		return;

	// FocusedUI 내에서, 부모 UI 포함, 자식 UI들중에 실제 타겟팅 된 UI를 가져온다.
	GameUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	bool bLbtnAway = KEY_AWAY(KEY::LBTN);
	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	if (nullptr != pTargetUI)
	{
		pTargetUI->MouseOn();

		if (bLbtnTap) // 마우스가 눌렸거나
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if(bLbtnAway) // 마우스가 떼졌다면
		{
			pTargetUI->MouseLbtnUp();

			if (pTargetUI->m_bLbtnDown) // 그전에 눌렸다면(눌렀다 뗀 완전한 클릭상황이면)
			{
				pTargetUI->MouseLbtnClicked();
			}

			pTargetUI->m_bLbtnDown = false;
		}
	}
}

void GameUIMgr::SetFocusedUI(GameUI* _pUI)
{
	if (m_pFocusedUI == _pUI || nullptr == _pUI)
	{
		m_pFocusedUI = _pUI;
		return;
	}

	m_pFocusedUI = _pUI;

	GameScene* pCurScene = GameSceneMgr::GetInst()->GetCurScene();
	vector<GameObject*>& vecUI = pCurScene->GetUIGroup();

	vector<GameObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (m_pFocusedUI == *iter)
		{
			break;
		}
	}

	// 벡터 내에서 맨뒤로 순번교체
	vecUI.erase(iter); // 삭제 후
	vecUI.push_back(m_pFocusedUI); // 다시 뒤로 푸쉬
}