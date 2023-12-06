#pragma once

class GameRes
{
private:
    wstring m_strKey; // 리소스 키 값
    wstring m_strRelativePath; // 리소스 상대 경로

public:
    const wstring& GetKey()
    {
        return m_strKey;
    }

    void SetKey(const wstring& _strKey)
    {
        m_strKey = _strKey;
    }

    const wstring& GetRelativePath()
    {
        return m_strRelativePath;
    }

    void SetRelativePath(const wstring& _strPath)
    {
        m_strRelativePath = _strPath;
    }

    GameRes();
    virtual ~GameRes();
};

