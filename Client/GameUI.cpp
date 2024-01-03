#include "pch.h"
#include "GameUI.h"

#include "GameKeyMgr.h"
#include "GameCamera.h"

#include "SelectGDI.h"

GameUI::GameUI(bool _bCamAff)
	: m_vecChildUI{}
	, m_pParentUI{ nullptr }
	, m_vFinalPos{}
	, m_bCamAffected{ _bCamAff }
	, m_bMouseOn{ false }
	, m_bLbtnDown{ false }
{
}

GameUI::~GameUI()
{
	Safe_Delete_Vec(m_vecChildUI);
}

void GameUI::UpdateChild()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Update();
	}
}

void GameUI::FinalUpdateChild()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->FinalUpdate();
	}
}

void GameUI::RenderChild(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Render(_dc);
	}
}

void GameUI::MouseOnCheck()
{
	Vec2 vMousePos = MOUSE_POS;
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
	{
		vMousePos = GameCamera::GetInst()->GetRealPos(vMousePos);
	}

	if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + vScale.x
		&& m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vScale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}

void GameUI::Update()
{
	// child ui update
	UpdateChild();
}

void GameUI::FinalUpdate()
{
	GameObject::FinalUpdate();

	// UI의 최종 좌표 위치
	m_vFinalPos = GetPos();

	if (GetParent())
	{
		Vec2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos;
	}

	// UI위의 마우스 포인터 체크
	MouseOnCheck();

	FinalUpdateChild();
}

void GameUI::Render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
	{
		vPos = GameCamera::GetInst()->GetRenderPos(vPos);
	}

	if (m_bLbtnDown)
	{
		SelectGDI select{ _dc, PEN_TYPE::GREEN };

		Rectangle(_dc
			, (int)(vPos.x)
			, (int)(vPos.y)
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y));
	}
	else
	{
		Rectangle(_dc
			, (int)(vPos.x)
			, (int)(vPos.y)
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y));
	}

	// child ui render
	RenderChild(_dc);
}

void GameUI::MouseOn()
{
}

void GameUI::MouseLbtnDown()
{
}

void GameUI::MouseLbtnUp()
{
}

void GameUI::MouseLbtnClicked()
{
}
