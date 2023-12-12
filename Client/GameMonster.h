#pragma once
#include "GameObject.h"

class AI;

struct tMonInfo
{
	float fHP;
	float fSpeed;
	float fRecogRange;
	float fAttRange;
	float fAtt;
};

class GameMonster :
	public GameObject
{
private:
	tMonInfo m_tInfo;
	AI* m_pAI;

	void SetMonInfo(const tMonInfo& _info)
	{
		m_tInfo = _info;
	}

public:
	virtual void Update();
	virtual void Render(HDC _dc);

	void UpdateAnimation();

	void SetAI(AI* _pAI);

	GameMonster();
	~GameMonster();

	friend class GameMonsterFactory;
};