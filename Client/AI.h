#pragma once

class GameState;
class GameMonster;

class AI
{
private:
	map<MON_STATE, GameState*> m_mapState;
	GameState* m_pCurState;
	GameMonster* m_pOwner;

public:
	void Update();

	void AddState(GameState* _pState);
	GameState* GetState(MON_STATE _eState);
	void SetCurState(MON_STATE _eState);
	GameState* GetCurState()
	{
		return m_pCurState;
	}
	GameMonster* GetObj()
	{
		return m_pOwner;
	}

	AI();
	~AI();

	friend class GameMonster;
};