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

public:
	void Init();
	void Update();
};