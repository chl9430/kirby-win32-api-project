#pragma once

class GameScene
{
private:
	wstring m_strName;

public:
	virtual void Enter() = 0;

	void SetName(const wstring& _strName)
	{
		m_strName = _strName;
	}

	GameScene();
	~GameScene();
};