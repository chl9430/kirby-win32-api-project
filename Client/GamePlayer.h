#pragma once
#include "GameObject.h"

enum class PLAYER_STATE
{
    IDLE,
    WALK,
    RUN,
    DOWN,
    INHALE,
    JUMP,
    FLOAT,
    EXHALE
};

class GamePlayer :
    public GameObject
{
private:
    PLAYER_STATE m_eCurState;
    PLAYER_STATE m_ePrevState;
    int m_iDir; // 플레이어의 방향정보
    int m_iPrevDir;

public:
    virtual void Update();

    void UpdateState();
    void UpdateMove();
    void UpdateAnimation();

    GamePlayer();
    virtual ~GamePlayer();
};