#pragma once

union COLLIDER_ID
{
	struct
	{
		UINT Left_id;
		UINT Right_id;
	};
	ULONGLONG ID;
};

class GameCollider;

class GameCollisionMgr
{
	SINGLE(GameCollisionMgr);

private:
	map<ULONGLONG, bool> m_mapColInfo; // 충돌체 간의 이전 프레임 충돌정보
	UINT m_arrCheck[(UINT)GROUP_TYPE::END]; // 그룹 간의 충돌 체크 매트릭스

	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(GameCollider* _pLeftCol, GameCollider* _pRightCol);
public:
	void Update();

	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
};