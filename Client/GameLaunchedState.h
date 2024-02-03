#pragma once
#include "GameState.h"

class GameLaunchedState :
    public GameState
{
private:

public:
    virtual void Update();
    virtual void Enter();
    virtual void Exit();

    GameLaunchedState();
    virtual ~GameLaunchedState();
};