#pragma once

class GameScene;

class GameSceneMgr
{
	SINGLE(GameSceneMgr);

private:
	GameScene* m_arrScene[(UINT)SCENE_TYPE::END]; // 모든 씬 목록
	GameScene* m_pCurScene;

	void ChangeScene(SCENE_TYPE _eNext); // GameEventMgr 클래스만 호출 가능

public:
	void Init();
	void Update();
	void Render(HDC _dc);

	GameScene* GetCurScene()
	{
		return m_pCurScene;
	}

	friend class GameEventMgr;
};