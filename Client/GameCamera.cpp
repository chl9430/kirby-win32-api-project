#include "pch.h"
#include "GameCamera.h"

#include "GameCore.h"
#include "GameResMgr.h"

GameCamera::GameCamera()
	: m_pVeilTex{ nullptr }
{
}

GameCamera::~GameCamera()
{
}

void GameCamera::Init()
{
	Vec2 vResolution = GameCore::GetInst()->GetResolution();

	m_pVeilTex = GameResMgr::GetInst()->CreateTexture(L"CameraVeil", (UINT)vResolution.x, (UINT)vResolution.y);
}