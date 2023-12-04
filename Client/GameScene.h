#pragma once

class GameObject;

class GameScene
{
private:
	wstring m_strName;
	vector<GameObject*> m_arrObj[(UINT)GROUP_TYPE::END];
	GameObject* m_pPlayer;

public:
	virtual void Start();
	virtual void Update();
	virtual void FinalUpdate();

	virtual void Enter() = 0;

	void AddObject(GameObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

	void SetName(const wstring& _strName)
	{
		m_strName = _strName;
	}
	void RegisterPlayer(GameObject* _pPlayer)
	{
		m_pPlayer = _pPlayer;
	}

	GameScene();
	~GameScene();
};