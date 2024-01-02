#include "pch.h"
#include "GamePanelUI.h"

#include "GameKeyMgr.h"

GamePanelUI::GamePanelUI()
	: GameUI{ false }
	, m_vDragStart{}
{
}

GamePanelUI::~GamePanelUI()
{
}

void GamePanelUI::render(HDC _dc)
{
	GameUI::Render(_dc);
}

void GamePanelUI::MouseOn()
{
	if (IsLbtnDown())
	{
		Vec2 vDiff = MOUSE_POS - m_vDragStart;

		Vec2 vCurPos = GetPos();
		vCurPos += vDiff;
		SetPos(vCurPos);

		m_vDragStart = MOUSE_POS;
	}
}

void GamePanelUI::MouseLbtnDown()
{
	m_vDragStart = MOUSE_POS;
}

void GamePanelUI::MouseLbtnUp()
{
}