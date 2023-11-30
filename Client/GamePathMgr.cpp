#include "pch.h"
#include "GamePathMgr.h"

GamePathMgr::GamePathMgr() 
	: m_szContentPath{}
	, m_szRelativePath{}
{
}

GamePathMgr::~GamePathMgr()
{
}

void GamePathMgr::Init()
{
	GetCurrentDirectory(255, m_szContentPath);

	int iLen = (int)wcslen(m_szContentPath);

	for (int i = iLen - 1; 0 <= i; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\"); // 릴리즈 모드 디렉토리 안의 경로로 재설정
}
