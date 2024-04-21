#pragma once
#include "GameObject.h"

class GameMissile;
class GameGate;
class GameSound;

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
    GONE,
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

    vector<GameObject*> m_vecInhaleRangeMon;
    vector<GameObject*> m_vecPowerInhaleRangeMon;
    MON_TYPE m_eEatenMon;
    GameMissile* m_pStarMissile;
    GameGate* m_pGate;

    // Sound
    GameSound* m_pJumpSound;
    GameSound* m_pInhaleSound;
    GameSound* m_pExhaleSound;
    GameSound* m_pLaunchSound;
    GameSound* m_pHoldSound;
    GameSound* m_pSwallowSound;
    GameSound* m_pGoneSound;

public:
    virtual void Update();
    virtual void Render(HDC _dc);

    void CreateInhale();

    void UpdateDir();
    void UpdateState();
    void UpdateMove();
    void UpdateAnimation();

    void JumpKirby();
    void InhaleMon();
    void SwallowMon();
    void LaunchMon();

    virtual void OnCollisionEnter(GameCollider* _pOther);
    virtual void OnCollision(GameCollider* _pOther);
    virtual void OnCollisionExit(GameCollider* _pOther);

    PLAYER_STATE GetPlayerState()
    {
        return m_eCurState;
    }
    void AddInhaleRangeMon(GameObject* _pObj)
    {
        m_vecInhaleRangeMon.push_back(_pObj);
    }
    void RemoveInhaleRangeMon(GameObject* _pObj)
    {
        m_vecInhaleRangeMon.erase(remove(m_vecInhaleRangeMon.begin(), m_vecInhaleRangeMon.end(), _pObj), m_vecInhaleRangeMon.end());
    }
    void AddPowerInhaleRangeMon(GameObject* _pObj)
    {
        m_vecPowerInhaleRangeMon.push_back(_pObj);
    }
    void RemovePowerInhaleRangeMon(GameObject* _pObj)
    {
        m_vecPowerInhaleRangeMon.erase(remove(m_vecPowerInhaleRangeMon.begin(), m_vecPowerInhaleRangeMon.end(), _pObj), m_vecPowerInhaleRangeMon.end());
    }

    GamePlayer(wstring _strName, Vec2 _vPos, Vec2 _vScale);
    virtual ~GamePlayer();
};