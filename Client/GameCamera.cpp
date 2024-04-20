#include "pch.h"
#include "GameCamera.h"

#include "GameCore.h"
#include "GameResMgr.h"
#include "GameKeyMgr.h"
#include "GameTimeMgr.h"

#include "GameTexture.h"

#include "GameObject.h"

GameCamera::GameCamera()
	: m_pVeilTex{ nullptr }
	, m_pTargetObj{ nullptr }
	, m_listCamEffect{}
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

	// ī�޶� �̵� ����
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
		if (m_pTargetObj->IsDead()) // ī�޶� Ÿ���� ���� �����ӿ� ������ �����̶��
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}

	// ȭ�� �߾���ǥ�� ī�޶� LookAt ��ǥ���� ���̰� ���
	 CalDiff();
}

void GameCamera::Render(HDC _dc)
{
	if (m_listCamEffect.empty())
		return;

	// ���� �ð��� üũ�Ѵ�.
	tCamEffect& tEffect = m_listCamEffect.front();
	tEffect.fCurTime += fDT;

	float fRatio = 0.f;
	fRatio = tEffect.fCurTime / tEffect.fDuration;

	// ���� ȿ�� ���� ���� �� ����
	if (fRatio < 0.f)
		fRatio = 0.f;
	if (fRatio > 1.f)
		fRatio = 1.f;

	int iAlpha = 0;

	if (tEffect.eEffect == CAM_EFFECT::FADE_OUT)
	{
		iAlpha = (int)(255.f * fRatio);
	}

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0; // �츮�� ���� �ؽ��Ĵ� ����ä���� ����.
	bf.SourceConstantAlpha = iAlpha; // ��������

	AlphaBlend(_dc, 0, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		, m_pVeilTex->GetDC()
		, 0, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height(), bf);

	// dt�� fDuration�� �Ѿ�� ������ ȿ���� ��������ش�. (�׷��� ȿ���� ��� ������ ���� ����ȴ�.)
	// ���� �ð��� ����Ʈ �ִ� ���� �ð��� �Ѿ ���
	if (tEffect.fDuration < tEffect.fCurTime)
	{
		// ȿ�� ����
		m_listCamEffect.pop_front();
	}
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