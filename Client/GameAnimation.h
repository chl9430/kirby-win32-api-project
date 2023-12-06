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

public:
	void Save(const wstring& _strRelativePath);
	void Load(const wstring& _strRelativePath);

	const wstring& GetName()
	{
		return m_strName;
	}

	GameAnimation();
	~GameAnimation();

	friend class GameAnimator;
};