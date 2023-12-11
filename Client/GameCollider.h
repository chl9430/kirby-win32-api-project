#pragma once

class GameObject;

class GameCollider
{
private:
	static UINT g_iNextID;

	GameObject* m_pOwner;
	Vec2 m_vOffsetPos;
	Vec2 m_vScale;
	UINT m_iCol;
	Vec2 m_vFinalPos;

	UINT m_iId;

public:
	void FinalUpdate();
	void Render(HDC _dc);

	void SetOffsetPos(Vec2 _vPos)
	{
		m_vOffsetPos = _vPos;
	}
	void SetScale(Vec2 _vScale)
	{
		m_vScale = _vScale;
	}
	GameObject* GetObj()
	{
		return m_pOwner;
	}
	UINT GetID()
	{
		return m_iId;
	}
	Vec2 GetFinalPos()
	{
		return m_vFinalPos;
	}
	Vec2 GetScale()
	{
		return m_vScale;
	}

	void OnCollision(GameCollider* _pOther); // 충돌 중일때 호출되는 함수
	void OnCollisionEnter(GameCollider* _pOther); // 충돌을 시작할때 호출되는 함수
	void OnCollisionExit(GameCollider* _pOther); // 충돌을 빠져나갈때 호출되는 함수

	GameCollider();
	~GameCollider();

	friend class GameObject;
};