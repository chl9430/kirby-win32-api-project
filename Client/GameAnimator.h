#pragma once

class GameAnimation;
class GameObject;

class GameAnimator
{
private:
	map<wstring, GameAnimation*> m_mapAnim;
	GameObject* m_pOwner;
	GameAnimation* m_pCurAnim;
	bool m_bRepeat;

public:
	void Play(const wstring& _strName, bool _bRepeat);

	void CreateAnimation(const wstring& _strName
		, GameTexture* _pTex // 이미지 텍스처
		, Vec2 _vLT // 자를 이미지의 좌상단 위치
		, Vec2 _vSliceSize // 자를 이미지의 사이즈
		, Vec2 _vStep // 다음에 자를 이미지까지의 거리
		, float _fDuration
		, UINT _iFrameCount // 이미지의 프레임 수
	);
	GameAnimation* FindAnimation(const wstring& _strName);
	void LoadAnimation(const wstring& _strRelativePath);

	GameAnimator();
	~GameAnimator();

	friend class GameObject;
};