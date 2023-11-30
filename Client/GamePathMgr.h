#pragma once

class GamePathMgr
{
	SINGLE(GamePathMgr);

private:
	wchar_t m_szContentPath[256];
	wchar_t m_szRelativePath[256];

public:
	void Init();
};

