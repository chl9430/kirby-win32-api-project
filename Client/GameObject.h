#pragma once

class GameObject
{
private:
	Vec2 m_vPos;
	bool m_bAlive;

public:
	bool IsDead()
	{
		return !m_bAlive;
	}

	Vec2 GetPos()
	{
		return m_vPos;
	}

	GameObject();
	~GameObject();
};