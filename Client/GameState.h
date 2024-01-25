#pragma once

class AI;

class GameState
{
private:
	AI* m_pAI;
	MON_STATE m_eState;

public:
	virtual void Update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;

	MON_STATE GetType()
	{
		return m_eState;
	}
	AI* GetAI()
	{
		return m_pAI;
	}

	GameState(MON_STATE _eState);
	~GameState();

	friend class AI;
};