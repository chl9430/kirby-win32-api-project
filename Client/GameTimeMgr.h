#pragma once

class GameTimeMgr
{
	SINGLE(GameTimeMgr);

private:
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	double m_dDT; // 프레임 사이의 시간값
	double m_dAcc; // 1초 체크를 위한 누적시간
	UINT m_iCallCount;
	UINT m_iFPS; // 최종 FPS

public:
	void Init();
	void Update();
	void Render();

	double GetDT()
	{
		return m_dDT;
	}

	float GetfDT()
	{
		return (float)m_dDT;
	}
};