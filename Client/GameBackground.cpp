#include "pch.h"
#include "GameBackground.h"

#include "GameCore.h"

#include "GameCamera.h"
#include "GameResMgr.h"

#include "GameTexture.h"

GameBackground::GameBackground(wstring _strName, Vec2 _vPos, Vec2 _vScale)
	: GameObject{ _strName, _vPos, _vScale }
	, m_iOriginWidth{ 0 }
	, m_iOriginHeight{ 0 }
{
}

GameBackground::~GameBackground()
{
}

void GameBackground::Update()
{
}

void GameBackground::Render(HDC _dc)
{
	Vec2 vRenderPos = GameCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vDiff = GameCamera::GetInst()->GetDiff();
	Vec2 vScale = GetScale();

	// 카메라가 움직인 정도에 따라서 배경도 이미지 끝까지 갈 수 있도록 한다.
	if (MAX_TILE_COUNT_WIDTH > MAX_TILE_COUNT_HEIGHT)
	{
		int iWidth = MAX_TILE_COUNT_WIDTH * TILE_SIZE - GameCore::GetInst()->GetResolution().x;

		float fCameraMoveRate = 0.f;

		fCameraMoveRate = vDiff.x / iWidth;

		float fDistance = abs((vScale.x / 2) - (GameCore::GetInst()->GetResolution().x - vScale.x / 2));

		float fRate = fDistance * fCameraMoveRate;

		vRenderPos = Vec2{ vScale.x / 2 - fRate, vRenderPos.y };
	}

	if (GetCurrentTexture() != nullptr)
	{
		TransparentBlt(_dc
			, (int)(vRenderPos.x - vScale.x / 2)
			, (int)(vRenderPos.y - vScale.y / 2)
			, (int)(vScale.x)
			, (int)(vScale.y)
			, GetCurrentTexture()->GetDC()
			, 0
			, 0
			, (int)(m_iOriginWidth)
			, (int)(m_iOriginHeight)
			, RGB(255, 0, 255)
		);
	}

	ComponentRender(_dc);
}