#include "pch.h"
#include "GameTimeMgr.h"

GameTimeMgr::GameTimeMgr()
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDT{ 0 }
{

}

GameTimeMgr::~GameTimeMgr()
{

}

void GameTimeMgr::Init()
{
	QueryPerformanceCounter(&m_llPrevCount); // 현재 카운트
	QueryPerformanceFrequency(&m_llFrequency); // 초당 카운트할 수 있는 횟수
}

void GameTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);

	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	m_llPrevCount = m_llCurCount;
}