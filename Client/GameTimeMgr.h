#pragma once

class GameTimeMgr
{
	SINGLE(GameTimeMgr);

private:
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	double m_dDT; // 프레임 사이의 시간값

public:
	void Init();
	void Update();
};