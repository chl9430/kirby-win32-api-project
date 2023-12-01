#pragma once

class GameObject
{
private:
	wstring m_strName;
	Vec2 m_vPos;
	Vec2 m_vScale;
	bool m_bAlive;

public:
	virtual void Update() = 0;

	void SetName(const wstring& _strName)
	{
		m_strName = _strName;
	}
	const wstring& GetName()
	{
		return m_strName;
	}
	void SetScale(Vec2 _vScale)
	{
		m_vScale = _vScale;
	}
	bool IsDead()
	{
		return !m_bAlive;
	}
	Vec2 GetPos()
	{
		return m_vPos;
	}
	void SetPos(Vec2 _vPos)
	{
		m_vPos = _vPos;
	}

	GameObject();
	virtual ~GameObject();
};