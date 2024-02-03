#pragma once
#include "GameState.h"

class GameObject;

class GameEatenState :
    public GameState
{
private:
    GameObject* m_pPlayer;

public:
    virtual void Update();
    virtual void Enter();
    virtual void Exit();

    void RegisterPlayer(GameObject* _pPlayer)
    {
        m_pPlayer = _pPlayer;
    }

    GameEatenState();
    virtual ~GameEatenState();
};