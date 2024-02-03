#include "pch.h"
#include "GameEventMgr.h"

#include "GameSceneMgr.h"
#include "GameUIMgr.h"

#include "GameScene.h"
#include "GameObject.h"

GameEventMgr::GameEventMgr()
	: m_vecDead{}
	, m_vecEvent{}
{
}

GameEventMgr::~GameEventMgr()
{
}

void GameEventMgr::Execute(const tEvent& _tEve)
{
	switch (_tEve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : Object Address
		// wParam : Group Type
		GameObject* pNewObj = (GameObject*)_tEve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_tEve.wParam;

		GameSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
	break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : Object Address
		// ���� ó�� �� ������Ʈ�� ���Ϳ� �߰��Ѵ�.
		GameObject* pDeadObj = (GameObject*)_tEve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
	break;
	case EVENT_TYPE::SCENE_CHANGE:
	{
		// lParam : Next Scene Type
		GameSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_tEve.lParam);

		// ��Ŀ�� UI ����(���� Scene�� UI�� ����Ű�� �ֱ� ����)
		GameUIMgr::GetInst()->SetFocusedUI(nullptr);
	}
	break;
	case EVENT_TYPE::CHANGE_AI_STATE:
	{
		// lParam : AI
		// wParam : Next Type
	}
	break;
	}
}

void GameEventMgr::Update()
{
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	// Event ó��
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Execute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void GameEventMgr::AddEvent(tEvent _tEve)
{
	m_vecEvent.push_back(_tEve);
}