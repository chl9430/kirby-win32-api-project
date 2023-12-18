#pragma once
#include "GameObject.h"

enum class PLAYER_STATE
{
    IDLE,
    WALK_READY,
    WALK,
    WALK_STOP,
    RUN_READY,
    RUN,
    RUN_STOP,
    DOWN,
    INHALE,
    JUMP,
    DROP,
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
    float m_fJumpStartPos;
    bool isRunning;

public:
    virtual void Update();
    virtual void Render(HDC _dc);

    virtual void OnCollisionEnter(GameCollider* _pOther);

    void UpdateState();
    void UpdateMove();
    void UpdateAnimation();
    void UpdateGravity();

    GamePlayer();
    virtual ~GamePlayer();
};