#pragma once

class GameTexture;
class GameObject;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};

struct tCamEffect
{
	CAM_EFFECT eEffect; // 카메라 효과
	float fDuration; // 효과 최대 진행 시간
	float fCurTime; // 카메라 효과 현재 진행된 시간
};

class GameCamera
{
	SINGLE(GameCamera);

private:
	GameTexture* m_pVeilTex; // 카메라 가림막 텍스처(검은색), GameResMgr에서 메모리 할당 관리
	GameObject* m_pTargetObj;
	list<tCamEffect> m_listCamEffect;
	Vec2 m_vLookAt;
	Vec2 m_vCurLookAt;
	Vec2 m_vPrevLookAt;
	Vec2 m_vDiff;
	float m_fAccTime;
	float m_fTime;
	float m_fSpeed;

	void CalDiff();
public:
	void Init();
	void Update();
	void Render(HDC _dc);

	void FixDiff(Vec2& _vDiff);

	Vec2 GetRenderPos(Vec2 _vObjPos)
	{
		return _vObjPos - m_vDiff;
	}
	Vec2 GetRealPos(Vec2 _vRenderPos)
	{
		return _vRenderPos + m_vDiff;
	}
	void SetTargetObj(GameObject* _pObj)
	{
		m_pTargetObj = _pObj;
	}
	const Vec2& GetDiff()
	{
		return m_vDiff;
	}
	void SetDiff(const Vec2& _vDiff)
	{
		m_vDiff = _vDiff;
	}
	void FadeOut(float _fDuration)
	{
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_OUT;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;

		m_listCamEffect.push_back(ef);

		if (0.f == _fDuration)
			assert(nullptr);
	}
	bool IsAllCamEffectFinish()
	{
		return m_listCamEffect.size() == 0;
	}
};