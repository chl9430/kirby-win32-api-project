#pragma once
#include "GameUI.h"

class GamePanelUI :
    public GameUI
{
private:
    Vec2 m_vDragStart;

public:
    virtual void Render(HDC _dc);

    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();

    GamePanelUI(bool _bCamAff, wstring _strName, Vec2 _vPos, Vec2 _vScale);
    ~GamePanelUI();
};