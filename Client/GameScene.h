#pragma once

class GameObject;

class GameScene
{
private:
	wstring m_strName;
	vector<GameObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // ���͸� ���ҷ� �ϴ� �迭�� ����
	GameObject* m_pPlayer;

	UINT m_iTileX; // Ÿ�� ���� ����
	UINT m_iTileY; // Ÿ�� ���� ����

public:
	virtual void Start();
	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);

	/*void CreateTile(UINT _iXCount, UINT _iYCount);*/
	void LoadTile(const wstring& _strRelativePath);
	void DeleteAll();
	void DeleteGroup(GROUP_TYPE _eTarget);

	virtual void Enter() = 0;
	virtual void Exit() = 0;

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
	const vector<GameObject*>& GetGroupObject(GROUP_TYPE _eType)
	{
		return m_arrObj[(UINT)_eType];
	}
	vector<GameObject*>& GetUIGroup() 
	{ 
		return m_arrObj[(UINT)GROUP_TYPE::UI]; 
	}
	UINT GetTileX()
	{
		return m_iTileX;
	}
	UINT GetTileY()
	{
		return m_iTileY;
	}

	GameScene();
	~GameScene();
};