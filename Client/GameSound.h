#pragma once
#include "GameRes.h"

#include "GameSoundMgr.h"

class GameSound :
    public GameRes
{
private:
	LPDIRECTSOUNDBUFFER		m_pSoundBuffer; // 같은 사운드 동시에 여러 사운드를 재생하고 싶다면, 버퍼를 복사하는 개념으로 생각한다.(채널)
	// 하지만 지금은 같은 사운드를 다른 파일로 만들어 로드시키고 사용하도록 한다.
	DSBUFFERDESC			m_tBuffInfo;
	int						m_iVolume;

public:
	int Load(const wstring& _strPath);

	// 일반 재생
	void Play(bool _bLoop = false);

	// BGM 으로 재생
	void PlayToBGM(bool _bLoop = false);

	void Stop(bool _bReset = false);

	// 볼륨 범위 (0 ~ 100)
	void SetVolume(float _fVolume);

	// 음악파일 위치 조정
	void SetPosition(float _fPosition); // 0 ~ 100 사이

private:
	bool LoadWaveSound(const wstring& _strPath);
	int GetDecibel(float _fVolume);



public:
	GameSound();
	virtual ~GameSound();
};