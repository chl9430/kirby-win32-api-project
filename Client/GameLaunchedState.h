#pragma once
#include "GameState.h"

class GameLaunchedState :
    public GameState
{
private:
    int m_iDir;

public:
    virtual void Update();
    virtual void Enter();
    virtual void Exit();

    void SetLaunchDir(int _iDir)
    {
        m_iDir = _iDir;
    }

    GameLaunchedState();
    virtual ~GameLaunchedState();
};