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

void GameCamera::Render(HDC _dc)
{
	if (m_listCamEffect.empty())
		return;

	// 누적 시간을 체크한다.
	tCamEffect& tEffect = m_listCamEffect.front();
	tEffect.fCurTime += fDT;

	float fRatio = 0.f;
	fRatio = tEffect.fCurTime / tEffect.fDuration;

	// 현재 효과 진행 비율 값 보정
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
	bf.AlphaFormat = 0; // 우리가 만든 텍스쳐는 알파채널이 없다.
	bf.SourceConstantAlpha = iAlpha; // 전역알파

	AlphaBlend(_dc, 0, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		, m_pVeilTex->GetDC()
		, 0, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height(), bf);

	// dt가 fDuration을 넘어서도 끝까지 효과를 진행시켜준다. (그래야 효과가 모두 끝까지 정상 진행된다.)
	// 진행 시간이 이펙트 최대 지정 시간을 넘어선 경우
	if (tEffect.fDuration < tEffect.fCurTime)
	{
		// 효과 종료
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