#pragma once

class GameTexture;
class GameAnimator;

struct tAnimFrm
{
	Vec2 vLT; // 프레임 애니메이션 이미지의 좌상단
	Vec2 vSlice; // 프레임 애니메이션 이미지의 사이즈
	Vec2 vOffset;
	float fDuration;
};

class GameAnimation
{
private:
	GameAnimator* m_pAnimator;
	wstring m_strName;
	GameTexture* m_pTex;
	vector<tAnimFrm> m_vecFrm; // 모든 프레임 정보
	int m_iCurFrm; // 현재 프레임
	bool m_bFinish; // 재생 끝에 도달여부
	float m_fAccTime;

	void SetName(const wstring& _strName)
	{
		m_strName = _strName;
	}

public:
	void Save(const wstring& _strRelativePath);
	void Load(const wstring& _strRelativePath);
	void Create(const wstring& _strName, GameTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);

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