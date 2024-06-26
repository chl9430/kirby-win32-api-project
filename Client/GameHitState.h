#pragma once
#include "GameState.h"

class GameHitState :
    public GameState
{
private:
    bool m_bIsDead;

public:
    virtual void Update();
    virtual void Enter();
    virtual void Exit();

    bool GetIsDead()
    {
        return m_bIsDead;
    }

    GameHitState();
    ~GameHitState();
};