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

	// ���� ��Ŀ�� �� UI�� �޾Ƶΰ� ����Ǿ����� Ȯ���Ѵ�.
	GameUI* pFocusedUI = m_pFocusedUI;

	/*if (!bLbtnTap)
	{
		return pFocusedUI;
	}*/

	// ���ʹ�ư Ŭ���� �߻��ߴٸ�
	vector<GameObject*>::iterator targetIter = vecUI.end();
	vector<GameObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (((GameUI*)*iter)->IsMouseOn())
		{
			targetIter = iter;
		}
	}

	// �̹��� Focus �� UI�� ����.
	if (vecUI.end() == targetIter)
	{
		return nullptr;
	}

	pFocusedUI = (GameUI*)*targetIter;

	// ���� ������ �ǵڷ� ������ ��ü
	vecUI.erase(targetIter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

GameUI* GameUIMgr::GetTargetedUI(GameUI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	// �θ� ���� ��� �ڽĵ��� �˻�
	GameUI* pTargetUI = nullptr;

	static list<GameUI*> queue;
	static vector<GameUI*> vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	// ť�� �������� �ݺ����� �����Ѵ�.
	while (!queue.empty())
	{
		// ť���� ������ �ϳ� ������
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

	// ���� ��ư�� ����, ������ üũ�� �ٽ� �����Ѵ�.
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
	// ��Ŀ�� �� UI Ȯ��
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI)
		return;

	// FocusedUI ������, �θ� UI ����, �ڽ� UI���߿� ���� Ÿ���� �� UI�� �����´�.
	GameUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	bool bLbtnAway = KEY_AWAY(KEY::LBTN);
	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	if (nullptr != pTargetUI)
	{
		pTargetUI->MouseOn();

		if (bLbtnTap) // ���콺�� ���Ȱų�
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if(bLbtnAway) // ���콺�� �����ٸ�
		{
			pTargetUI->MouseLbtnUp();

			if (pTargetUI->m_bLbtnDown) // ������ ���ȴٸ�(������ �� ������ Ŭ����Ȳ�̸�)
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

	// ���� ������ �ǵڷ� ������ü
	vecUI.erase(iter); // ���� ��
	vecUI.push_back(m_pFocusedUI); // �ٽ� �ڷ� Ǫ��
}