#pragma once
#include "GameState.h"

class GameDrawnState :
    public GameState
{
private:

public:
    virtual void Update();
    virtual void Enter();
    virtual void Exit();

    GameDrawnState();
    ~GameDrawnState();
};