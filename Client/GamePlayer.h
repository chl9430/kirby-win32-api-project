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
    DROP,
    FLOAT_START,
    FLOAT_IDLE,
    FLOAT_END,
    EXHALE,
    SWALLOW,
    HIT,
    KEEP_START,
    KEEP_IDLE,
    KEEP_WALK_READY,
    KEEP_WALK,
    KEEP_JUMP,
    KEEP_DROP_START,
    KEEP_DROP,
    KEEP_HIT,
};

class GamePlayer :
    public GameObject
{
private:
    PLAYER_STATE m_eCurState;
    PLAYER_STATE m_ePrevState;

    float m_fInhaleTime;
    float m_fPowerInhaleTime;
    float m_fJumpPower;
    float m_fFloatJumpPower;
    float m_fWalkSpeed;
    float m_fFloatMoveSpeed;

    GameObject* m_pEatenMon;

public:
    virtual void Update();
    virtual void Render(HDC _dc);

    void CreateInhale();

    void UpdateDir();
    void UpdateState();
    void UpdateMove();
    void UpdateAnimation();

    void JumpKirby();
    void SwallowMon();
    void LaunchMon();

    virtual void OnCollisionEnter(GameCollider* _pOther);
    virtual void OnCollision(GameCollider* _pOther);
    virtual void OnCollisionExit(GameCollider* _pOther);

    PLAYER_STATE GetPlayerState()
    {
        return m_eCurState;
    }

    GamePlayer(wstring _strName, Vec2 _vPos, Vec2 _vScale);
    virtual ~GamePlayer();
};