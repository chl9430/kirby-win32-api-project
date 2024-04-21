#pragma once
// sound �뵵 - ��� ���� �߿�
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

// �ڵ�
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

class GameSound;

class GameSoundMgr
{
	SINGLE(GameSoundMgr);

private:
	LPDIRECTSOUND8	m_pSound;	// ����ī�� ��ǥ ��ü
	GameSound* m_pBGM;		// ���� ������ BGM Sound

public:
	int init(void);
	LPDIRECTSOUND8 GetSoundDevice() { return m_pSound; }
	void RegisterToBGM(GameSound* _pSound);
};