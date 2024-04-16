#pragma once
#include "GameObject.h"

class GameBackground :
    public GameObject
{
private:
    UINT m_iOriginWidth;
    UINT m_iOriginHeight;

public:
    virtual void Update();
    virtual void Render(HDC _dc);

    void SetOriginSize(UINT _iWidth, UINT _iHeight)
    {
        m_iOriginWidth = _iWidth;
        m_iOriginHeight = _iHeight;
    }

    GameBackground(wstring _strName, Vec2 _vPos, Vec2 _vScale);
    ~GameBackground();
};