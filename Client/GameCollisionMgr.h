#pragma once

class GameCollisionMgr
{
	SINGLE(GameCollisionMgr);

private:
	UINT m_arrCheck[(UINT)GROUP_TYPE::END]; // 그룹 간의 충돌 체크 매트릭스

public:
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
};