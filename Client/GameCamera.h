#pragma once

class GameTexture;
class GameObject;

class GameCamera
{
	SINGLE(GameCamera);

private:
	GameTexture* m_pVeilTex; // 카메라 가림막 텍스처(검은색), GameResMgr에서 메모리 할당 관리
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

	Vec2 GetRenderPos(Vec2 _vObjPos)
	{
		return _vObjPos - m_vDiff;
	}
	void SetTargetObj(GameObject* _pObj)
	{
		m_pTargetObj = _pObj;
	}
};