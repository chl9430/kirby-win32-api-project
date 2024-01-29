#pragma once

class GameTexture;
class GameAnimator;

struct tAnimFrm
{
	Vec2 vLT; // ������ �ִϸ��̼� �̹����� �»��
	Vec2 vSlice; // ������ �ִϸ��̼� �̹����� ������
	Vec2 vOffset;
	float fDuration;
};

class GameAnimation
{
private:
	GameAnimator* m_pAnimator;
	wstring m_strName;
	GameTexture* m_pTex;
	vector<tAnimFrm> m_vecFrm; // ��� ������ ����
	int m_iCurFrm; // ���� ������
	bool m_bFinish; // ��� ���� ���޿���
	float m_fAccTime;

	void SetName(const wstring& _strName)
	{
		m_strName = _strName;
	}

public:
	void Save(const wstring& _strRelativePath);
	void Load(const wstring& _strRelativePath);
	void Create(const wstring& _strName, GameTexture* _pTex, float _fDuration);

	void Update();
	void Render(HDC _dc);

	const wstring& GetName()
	{
		return m_strName;
	}
	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}
	bool IsFinish()
	{
		return m_bFinish;
	}

	GameAnimation();
	~GameAnimation();

	friend class GameAnimator;
};