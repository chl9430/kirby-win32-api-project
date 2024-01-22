#pragma once

class GameTexture;
class GameObject;

class GameCamera
{
	SINGLE(GameCamera);

private:
	GameTexture* m_pVeilTex; // ī�޶� ������ �ؽ�ó(������), GameResMgr���� �޸� �Ҵ� ����
	GameObject* m_pTargetObj;
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
};