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
	void SetFinalPos(const Vec2& _vPos)
	{
		m_vFinalPos = _vPos;
	}
	Vec2 GetScale()
	{
		return m_vScale;
	}

	void OnCollision(GameCollider* _pOther); // �浹 ���϶� ȣ��Ǵ� �Լ�
	void OnCollisionEnter(GameCollider* _pOther); // �浹�� �����Ҷ� ȣ��Ǵ� �Լ�
	void OnCollisionExit(GameCollider* _pOther); // �浹�� ���������� ȣ��Ǵ� �Լ�

	GameCollider();
	~GameCollider();

	friend class GameObject;
};