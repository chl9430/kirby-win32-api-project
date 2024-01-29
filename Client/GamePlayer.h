#pragma once
#include "GameObject.h"

enum class PLAYER_STATE
{
    IDLE,
    WALK_READY,
    WALK,
    RUN_READY,
    RUN,
    INHALE,
    POWER_INHALE,
    JUMP,
    FLOAT_START,
    FLOAT_IDLE,
    FLOAT_END,
    DROP,
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
    float m_fInhaleTime;
    float m_fPowerInhaleTime;
    float m_fJumpPower;
    float m_fFloatJumpPower;
    float m_fWalkSpeed;
    float m_fFloatMoveSpeed;

public:
    virtual void Update();
    virtual void Render(HDC _dc);

    void UpdateDir();
    void UpdateState();
    void UpdateMove();
    void UpdateAnimation();

    PLAYER_STATE GetPlayerState()
    {
        return m_eCurState;
    }

    GamePlayer(wstring _strName, Vec2 _vPos, Vec2 _vScale);
    virtual ~GamePlayer();
};