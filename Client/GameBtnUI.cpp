#include "pch.h"
#include "GameBtnUI.h"

GameBtnUI::GameBtnUI(bool _bCamAff)
	: GameUI{ _bCamAff }
	, m_pSceneFunc{ nullptr }
	, m_pFunc{ nullptr }
	, m_param1{}
	, m_param2{}
	, m_pSceneInst{ nullptr }
	, m_pIdleTexture { nullptr }
	, m_pMouseOnTex { nullptr }
	, m_pMouseDownTex { nullptr }
	, m_pMouseUpTex { nullptr }
{
}

GameBtnUI::~GameBtnUI()
{
}

void GameBtnUI::SetClickedCallBack(GameScene* _pScene, SCENE_MEMFUNC _pSceneFunc)
{
	m_pSceneInst = _pScene;
	m_pSceneFunc = _pSceneFunc;
}

void GameBtnUI::MouseLbtnDown()
{
	SetCurrentTexture(m_pMouseDownTex);
}

void GameBtnUI::MouseLbtnUp()
{
	SetCurrentTexture(m_pIdleTexture);
}

void GameBtnUI::MouseLbtnClicked()
{
	if (nullptr != m_pFunc)
	{
		m_pFunc(m_param1, m_param2);
	}

	if (m_pSceneInst && m_pSceneFunc)
	{
		// 클래스 멤버함수를 함수포인터로 호출합니다.
		((*m_pSceneInst).*m_pSceneFunc)(EDIT_MODE::BACKGROUND);
	}
}