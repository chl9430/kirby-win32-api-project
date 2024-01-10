#include "pch.h"
#include "GameBtnUI.h"

#include "GameTexture.h"

GameBtnUI::GameBtnUI(bool _bCamAff)
	: GameUI{ _bCamAff }
	, m_pSceneFunc{ nullptr }
	, m_pSceneInst{ nullptr }
	, m_pIdleTexture { nullptr }
	, m_pMouseOnTex { nullptr }
	, m_pMouseDownTex { nullptr }
	, m_pMouseUpTex { nullptr }
	, m_pMouseClickedTex{ nullptr }
{
}

GameBtnUI::~GameBtnUI()
{
}

void GameBtnUI::SetClickedCallBack(GameScene* _pScene, SCENE_MEMFUNC_1 _pSceneFunc, wstring _str, DWORD_PTR _param1, DWORD_PTR _param2)
{
	m_pSceneInst = _pScene;
	m_pSceneFunc = _pSceneFunc;
	m_strParam = _str;
}

void GameBtnUI::MouseOn()
{
	if (m_pMouseOnTex)
	{
		SetCurrentTexture(m_pMouseOnTex);
	}
}

void GameBtnUI::MouseLbtnDown()
{
	if (m_pMouseDownTex)
	{
		SetCurrentTexture(m_pMouseDownTex);
	}
}

void GameBtnUI::MouseLbtnUp()
{
	if (m_pMouseUpTex)
	{
		SetCurrentTexture(m_pMouseUpTex);
	}
}

void GameBtnUI::MouseLbtnClicked()
{
	if (m_pMouseClickedTex)
	{
		SetCurrentTexture(m_pMouseClickedTex);
	}

	/*if (nullptr != m_pFunc)
	{
		m_pFunc(m_param1, m_param2);
	}*/

	if (m_pSceneInst && m_pSceneFunc)
	{
		// 클래스 멤버함수를 함수포인터로 호출합니다.
		((*m_pSceneInst).*m_pSceneFunc)(m_strParam);
	}
}

void GameBtnUI::SetTexture(GameTexture* _pTexture)
{
	SetCurrentTexture(_pTexture);
}