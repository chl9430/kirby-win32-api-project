#include "pch.h"
#include "GameUI.h"

#include "GameKeyMgr.h"
#include "GameCamera.h"

#include "SelectGDI.h"
#include "GameTexture.h"

GameUI::GameUI(bool _bCamAff, wstring _strName, Vec2 _vPos, Vec2 _vScale)
	: GameObject{ _strName, _vPos, _vScale }
	, m_vecChildUI{}
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

	// UI�� ���� ��ǥ ��ġ
	m_vFinalPos = GetPos();

	if (GetParent())
	{
		Vec2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos;
	}

	// UI���� ���콺 ������ üũ
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

	if (GetCurrentTexture())
	{
		TransparentBlt(
			_dc,
			(int)(vPos.x),
			(int)(vPos.y),
			(int)GetScale().x,
			(int)GetScale().y,
			GetCurrentTexture()->GetDC(),
			0,
			0,
			(int)GetScale().x,
			(int)GetScale().y,
			RGB(255, 0, 255)
		);
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
