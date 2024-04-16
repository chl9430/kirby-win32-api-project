#pragma once
#include "GameRes.h"

class GameTexture :
    public GameRes
{
private:
    HDC m_dc;
    HBITMAP m_hBit;
    BITMAP m_bitInfo;

public:
    void Load(const wstring& _strFilePath);
    void Create(UINT _iWidth, UINT _iHeight);

    HDC GetDC()
    {
        return m_dc;
    }
    UINT Width()
    {
        return m_bitInfo.bmWidth;
    }
    UINT Height()
    {
        return m_bitInfo.bmHeight;
    }
    Vec2 ChangeImageSizeByRate(Vec2 _vRequestScale)
    {
        if (_vRequestScale.x > _vRequestScale.y)
        {
            return Vec2{ m_bitInfo.bmWidth * _vRequestScale.y / m_bitInfo.bmHeight, _vRequestScale.y };
        }
        else
        {
            return Vec2{ _vRequestScale.x, m_bitInfo.bmHeight * _vRequestScale.x / m_bitInfo.bmWidth };
        }
    }

    GameTexture();
    virtual ~GameTexture();
};

