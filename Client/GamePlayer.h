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
    virtual void Render(HDC _dc);

    virtual void OnCollisionEnter(GameCollider* _pOther);

    void UpdateState();
    void UpdateMove();
    void UpdateAnimation();
    void UpdateGravity();

    GamePlayer();
    virtual ~GamePlayer();
};