#include "pch.h"
#include "GameAnimation.h"

#include "GamePathMgr.h"
#include "GameResMgr.h"
#include "GameTimeMgr.h"
#include "GameCamera.h"

#include "GameTexture.h"
#include "GameObject.h"
#include "GameAnimator.h"

GameAnimation::GameAnimation()
	: m_pAnimator{ nullptr }
	, m_strName{}
	, m_pTex{ nullptr }
	, m_vecFrm{}
	, m_bFinish{ false }
	, m_iCurFrm{ 0 }
	, m_fAccTime{ 0 }
{
}

GameAnimation::~GameAnimation()
{
}

void GameAnimation::Save(const wstring& _strRelativePath)
{
	//wstring strFilePath = GamePathMgr::GetInst()->GetContentPath();
	//strFilePath += _strRelativePath;

	//FILE* pFile = nullptr;
	//_wfopen_s(&pFile, strFilePath.c_str(), L"wb");
	//assert(pFile);

	//// Animation의 이름을 저장한다. (데이터 직렬화)
	//fprintf(pFile, "[Animation Name]\n");
	//string strName = string(m_strName.begin(), m_strName.end());
	///*SaveWString(m_strName, pFile);*/
	//fprintf(pFile, strName.c_str());
	//fprintf(pFile, "\n");

	//// Animation이 사용하는 텍스처
	//fprintf(pFile, "[Texture Name]\n");
	//strName = string(m_pTex->GetKey().begin(), m_pTex->GetKey().end());
	//fprintf(pFile, strName.c_str());
	//fprintf(pFile, "\n");

	//fprintf(pFile, "[Texture Path]\n");
	//strName = string(m_pTex->GetRelativePath().begin(), m_pTex->GetRelativePath().end());
	//fprintf(pFile, strName.c_str());
	//fprintf(pFile, "\n");

	//// 프레임 개수
	//fprintf(pFile, "[Frame Count]\n");
	//fprintf(pFile, "%d\n", (int)m_vecFrm.size());

	//// 모든 프레임 정보
	//for (size_t i = 0; i < m_vecFrm.size(); ++i)
	//{
	//	fprintf(pFile, "[Frame Index]\n");
	//	fprintf(pFile, "%d\n", (int)i); // %d는 4바이트 정수, size_t는 8바이트 정수

	//	fprintf(pFile, "[Left Top]\n");
	//	fprintf(pFile, "%d %d\n", (int)m_vecFrm[i].vLT.x, (int)m_vecFrm[i].vLT.y);

	//	fprintf(pFile, "[Slice Size]\n");
	//	fprintf(pFile, "%d %d\n", (int)m_vecFrm[i].vSlice.x, (int)m_vecFrm[i].vSlice.y);

	//	fprintf(pFile, "[Offset]\n");
	//	fprintf(pFile, "%d %d\n", (int)m_vecFrm[i].vOffset.x, (int)m_vecFrm[i].vOffset.y);

	//	fprintf(pFile, "[Duration]\n");
	//	fprintf(pFile, "%f\n", m_vecFrm[i].fDuration);

	//	fprintf(pFile, "\n\n");
	//}

	//fclose(pFile);
}

void GameAnimation::Load(const wstring& _strRelativePath)
{
	//wstring strFilePath = GamePathMgr::GetInst()->GetContentPath();
	//strFilePath += _strRelativePath;

	//FILE* pFile = nullptr;
	//_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	//assert(pFile);

	//// Animation의 이름을 읽어온다.
	//string str;
	//char szBuff[256] = {};

	//FScanf(szBuff, pFile);
	//FScanf(szBuff, pFile);
	//str = szBuff;

	//m_strName = wstring(str.begin(), str.end());

	//// 참조하는 텍스쳐 이름 및 경로
	//FScanf(szBuff, pFile);
	//FScanf(szBuff, pFile);
	//str = szBuff;

	//wstring strTexKey = wstring(str.begin(), str.end());

	//FScanf(szBuff, pFile);
	//FScanf(szBuff, pFile);
	//str = szBuff;

	//wstring strTexPath = wstring(str.begin(), str.end());

	//m_pTex = GameResMgr::GetInst()->LoadTexture(strTexKey, strTexPath);

	//// 프레임 개수
	//FScanf(szBuff, pFile);
	//int iFrameCount = 0;
	//fscanf_s(pFile, "%d", &iFrameCount);

	//// 모든 프레임 정보
	//tAnimFrm frm = {};

	//for (int i = 0; i < iFrameCount; ++i)
	//{
	//	POINT pt = {};

	//	while (true)
	//	{
	//		FScanf(szBuff, pFile);

	//		if (!strcmp("[Frame Index]", szBuff))
	//		{
	//			fscanf_s(pFile, "%d", &pt.x);
	//		}
	//		else if (!strcmp("[Left Top]", szBuff))
	//		{
	//			fscanf_s(pFile, "%d", &pt.x);
	//			fscanf_s(pFile, "%d", &pt.y); // 정수형 포맷 데이터를 읽을 때 까지 파일을 읽는다.

	//			frm.vLT = pt;
	//		}
	//		else if (!strcmp("[Slice Size]", szBuff))
	//		{
	//			// fscanf_s(pFile, "%d, %d", &pt.x, &pt.y); // 요것도 잘 읽는지 테스트 해보기!!!
	//			fscanf_s(pFile, "%d", &pt.x);
	//			fscanf_s(pFile, "%d", &pt.y);

	//			frm.vSlice = pt;
	//		}
	//		else if (!strcmp("[Offset]", szBuff))
	//		{
	//			fscanf_s(pFile, "%d", &pt.x);
	//			fscanf_s(pFile, "%d", &pt.y);

	//			frm.vOffset = pt;
	//		}
	//		else if (!strcmp("[Duration]", szBuff))
	//		{
	//			fscanf_s(pFile, "%f", &frm.fDuration);
	//			break;
	//		}
	//	}

	//	m_vecFrm.push_back(frm);
	//}

	//fclose(pFile);
}

void GameAnimation::Create(const wstring& _strName, GameTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	if (_strName == L"IDLE_RIGHT" || _strName == L"IDLE_LEFT")
	{
		tAnimFrm frm01 = {};
		frm01.fDuration = _fDuration;
		frm01.vLT = Vec2{ 0.f, 0.f };
		frm01.vOffset = Vec2{ 0.f, 0.f };
		frm01.vSlice = Vec2{ 40.f, 36.f };
		m_vecFrm.push_back(frm01);
	}

	if (_strName == L"WALK_RIGHT" || _strName == L"WALK_LEFT")
	{
		tAnimFrm frm01 = {};
		frm01.fDuration = _fDuration;
		frm01.vLT = Vec2{ 0.f, 2.f };
		frm01.vOffset = Vec2{ 0.f, 0.f };
		frm01.vSlice = Vec2{ 40.f, 36.f };
		m_vecFrm.push_back(frm01);
		tAnimFrm frm02 = {};
		frm02.fDuration = _fDuration;
		frm02.vLT = Vec2{ 44.f, 0.f };
		frm02.vOffset = Vec2{ 0.f, 0.f };
		frm02.vSlice = Vec2{ 42.f, 38.f };
		m_vecFrm.push_back(frm02);
		tAnimFrm frm03 = {};
		frm03.fDuration = _fDuration;
		frm03.vLT = Vec2{ 90.f, 2.f };
		frm03.vOffset = Vec2{ 0.f, 0.f };
		frm03.vSlice = Vec2{ 40.f, 36.f };
		m_vecFrm.push_back(frm03);
		tAnimFrm frm04 = {};
		frm04.fDuration = _fDuration;
		frm04.vLT = Vec2{ 134.f, 6.f };
		frm04.vOffset = Vec2{ 0.f, 0.f };
		frm04.vSlice = Vec2{ 38.f, 32.f };
		m_vecFrm.push_back(frm04);
		tAnimFrm frm05 = {};
		frm05.fDuration = _fDuration;
		frm05.vLT = Vec2{ 176.f, 4.f };
		frm05.vOffset = Vec2{ 0.f, 0.f };
		frm05.vSlice = Vec2{ 34.f, 34.f };
		m_vecFrm.push_back(frm05);
		tAnimFrm frm06 = {};
		frm06.fDuration = _fDuration;
		frm06.vLT = Vec2{ 214.f, 2.f };
		frm06.vOffset = Vec2{ 0.f, 0.f };
		frm06.vSlice = Vec2{ 34.f, 36.f };
		m_vecFrm.push_back(frm06);
		tAnimFrm frm07 = {};
		frm07.fDuration = _fDuration;
		frm07.vLT = Vec2{ 254.f, 0.f };
		frm07.vOffset = Vec2{ 0.f, 0.f };
		frm07.vSlice = Vec2{ 42.f, 38.f };
		m_vecFrm.push_back(frm07);
		tAnimFrm frm08 = {};
		frm08.fDuration = _fDuration;
		frm08.vLT = Vec2{ 300.f, 2.f };
		frm08.vOffset = Vec2{ 0.f, 0.f };
		frm08.vSlice = Vec2{ 40.f, 36.f };
		m_vecFrm.push_back(frm08);
		tAnimFrm frm09 = {};
		frm09.fDuration = _fDuration;
		frm09.vLT = Vec2{ 344.f, 6.f };
		frm09.vOffset = Vec2{ 0.f, 0.f };
		frm09.vSlice = Vec2{ 38.f, 32.f };
		m_vecFrm.push_back(frm09);
		tAnimFrm frm10 = {};
		frm10.fDuration = _fDuration;
		frm10.vLT = Vec2{ 386.f, 4.f };
		frm10.vOffset = Vec2{ 0.f, 0.f };
		frm10.vSlice = Vec2{ 38.f, 34.f };
		m_vecFrm.push_back(frm10);
	}

	/*for (UINT i = 0; i < _iFrameCount; ++i)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + _vStep * (float)i;

		m_vecFrm.push_back(frm);
	}*/
}

void GameAnimation::Update()
{
	if (m_bFinish)
		return;

	m_fAccTime += fDT;

	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{
		++m_iCurFrm;

		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = -1;
			m_bFinish = true;
			m_fAccTime = 0.f;
			return;
		}

		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;
	}
}

void GameAnimation::Render(HDC _dc)
{
	if (m_bFinish)
		return;

	GameObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();

	vPos += m_vecFrm[m_iCurFrm].vOffset;

	vPos = GameCamera::GetInst()->GetRenderPos(vPos);

	TransparentBlt(_dc
		, (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f)
		, (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y)
		, m_pTex->GetDC()
		, (int)(m_vecFrm[m_iCurFrm].vLT.x), (int)(m_vecFrm[m_iCurFrm].vLT.y)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y)
		, RGB(255, 0, 255)
	);
}