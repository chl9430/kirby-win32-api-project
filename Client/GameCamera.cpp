#include "pch.h"
#include "GameCamera.h"

#include "GameCore.h"
#include "GameResMgr.h"
#include "GameKeyMgr.h"
#include "GameTimeMgr.h"

#include "GameObject.h"

GameCamera::GameCamera()
	: m_pVeilTex{ nullptr }
	, m_pTargetObj{ nullptr }
	, m_vCurLookAt{}
	, m_vPrevLookAt{}
	, m_vLookAt{}
	, m_vDiff{}
	, m_fAccTime{ 0.5f }
	, m_fTime{ 0.5f }
	, m_fSpeed{ 0 }
{
}

GameCamera::~GameCamera()
{
}

void GameCamera::CalDiff()
{
	if (m_pTargetObj)
	{
		Vec2 vCenterPos = Vec2{ (float)GameCore::GetInst()->GetResolution().x / 2, (float)GameCore::GetInst()->GetResolution().y / 2 };
		m_vDiff = m_pTargetObj->GetPos() - vCenterPos;
	}

	// 카메라 이동 제한
	FixDiff(m_vDiff);

	/*m_fAccTime += fDT;

	if (m_fTime <= m_fAccTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;

		if (!vLookDir.IsZero())
		{
			m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;
		}
	}

	Vec2 vResolution = GameCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	m_vDiff = m_vCurLookAt;
	m_vPrevLookAt = m_vCurLookAt;*/
}

void GameCamera::Init()
{
	Vec2 vResolution = GameCore::GetInst()->GetResolution();

	m_pVeilTex = GameResMgr::GetInst()->CreateTexture(L"CameraVeil", (UINT)vResolution.x, (UINT)vResolution.y);
}

void GameCamera::Update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead()) // 카메라 타겟이 다음 프레임에 없어질 예정이라면
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}

	// 화면 중앙좌표와 카메라 LookAt 좌표간의 차이값 계산
	 CalDiff();
}

void GameCamera::FixDiff(Vec2& _vDiff)
{
	float fLimitX = (float)((30 * TILE_SIZE) - GameCore::GetInst()->GetResolution().x);
	float fLimitY = (float)((20 * TILE_SIZE) - GameCore::GetInst()->GetResolution().y);

	if (_vDiff.x <= 0.f)
	{
		_vDiff.x = 0.f;
	}

	if (_vDiff.x >= fLimitX)
	{
		_vDiff.x = fLimitX;
	}

	if (_vDiff.y <= 0.f)
	{
		_vDiff.y = 0.f;
	}

	if (_vDiff.y >= fLimitY)
	{
		_vDiff.y = fLimitY;
	}
}