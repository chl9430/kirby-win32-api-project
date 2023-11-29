#pragma once

class GameRes
{
private:
    wstring m_strKey; // 리소스 키 값
    wstring m_strRelativePath; // 리소스 상대 경로

public:
    void SetKey(const wstring& _strKey)
    {
        m_strKey = _strKey;
    }

    GameRes();
    virtual ~GameRes();
};

