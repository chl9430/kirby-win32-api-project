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
		Vec2 vCenterPos = Vec2{ (float)GameCore::GetInst()->GetResolution().x / 2, m_pTargetObj->GetPos().y };
		m_vDiff = m_pTargetObj->GetPos() - vCenterPos;
	}
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
		if (m_pTargetObj->IsDead()) // ī�޶� Ÿ���� ���� �����ӿ� ������ �����̶��
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}

	if (KEY_HOLD(KEY::I))
	{
		m_vDiff.y -= 500.f * fDT;
	}

	if (KEY_HOLD(KEY::K))
	{
		m_vDiff.y += 500.f * fDT;
	}

	if (KEY_HOLD(KEY::J))
	{
		m_vDiff.x -= 500.f * fDT;
	}

	if (KEY_HOLD(KEY::L))
	{
		m_vDiff.x += 500.f * fDT;
	}

	// ȭ�� �߾���ǥ�� ī�޶� LookAt ��ǥ���� ���̰� ���
	 CalDiff();
}