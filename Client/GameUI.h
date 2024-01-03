#pragma once
#include "GameObject.h"

class GameUI :
    public GameObject
{
private:
    vector<GameUI*> m_vecChildUI;
    GameUI* m_pParentUI;
    Vec2 m_vFinalPos;

    bool m_bCamAffected; // UI가 카메라의 영향을 받는지 유무
    bool m_bMouseOn; // UI 위에 마우스가 있는지 유무
    bool m_bLbtnDown; // UI에 왼쪽버튼이 눌린적이 있는지 우무

    void UpdateChild();
    void FinalUpdateChild();
    void RenderChild(HDC _dc);

    void MouseOnCheck();

public:
    virtual void Update();
    virtual void FinalUpdate();
    virtual void Render(HDC _dc);

    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();

    void AddChild(GameUI* _pUI)
    {
        m_vecChildUI.push_back(_pUI);
        _pUI->m_pParentUI = this;
    }
    GameUI* GetParent()
    {
        return m_pParentUI;
    }
    Vec2 GetFinalPos()
    {
        return m_vFinalPos;
    }
    bool IsLbtnDown()
    {
        return m_bLbtnDown;
    }
    bool IsMouseOn() { 
        return m_bMouseOn;
    }
    const vector<GameUI*>& GetChildUI() 
    { 
        return m_vecChildUI; 
    }

    GameUI(bool _bCamAff);
    ~GameUI();

    friend class GameUIMgr;
};