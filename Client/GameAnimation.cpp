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

void GameAnimation::Create(const wstring& _strName, GameTexture* _pTex, float _fDuration)
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

		return;
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

		return;
	}

	if (_strName == L"RUN_RIGHT" || _strName == L"RUN_LEFT")
	{
		tAnimFrm frm01 = {};
		frm01.fDuration = _fDuration;
		frm01.vLT = Vec2{ 0.f, 0.f };
		frm01.vOffset = Vec2{ 0.f, 0.f };
		frm01.vSlice = Vec2{ 48.f, 38.f };
		m_vecFrm.push_back(frm01);

		tAnimFrm frm02 = {};
		frm02.fDuration = _fDuration;
		frm02.vLT = Vec2{ 52.f, 0.f };
		frm02.vOffset = Vec2{ 0.f, 0.f };
		frm02.vSlice = Vec2{ 38.f, 38.f };
		m_vecFrm.push_back(frm02);

		tAnimFrm frm03 = {};
		frm03.fDuration = _fDuration;
		frm03.vLT = Vec2{ 96.f, 2.f };
		frm03.vOffset = Vec2{ 0.f, 0.f };
		frm03.vSlice = Vec2{ 34.f, 36.f };
		m_vecFrm.push_back(frm03);

		tAnimFrm frm04 = {};
		frm04.fDuration = _fDuration;
		frm04.vLT = Vec2{ 136.f, 0.f };
		frm04.vOffset = Vec2{ 0.f, 0.f };
		frm04.vSlice = Vec2{ 36.f, 38.f };
		m_vecFrm.push_back(frm04);

		tAnimFrm frm05 = {};
		frm05.fDuration = _fDuration;
		frm05.vLT = Vec2{ 178.f, 0.f };
		frm05.vOffset = Vec2{ 0.f, 0.f };
		frm05.vSlice = Vec2{ 38.f, 38.f };
		m_vecFrm.push_back(frm05);

		tAnimFrm frm06 = {};
		frm06.fDuration = _fDuration;
		frm06.vLT = Vec2{ 220.f, 0.f };
		frm06.vOffset = Vec2{ 0.f, 0.f };
		frm06.vSlice = Vec2{ 36.f, 38.f };
		m_vecFrm.push_back(frm06);

		tAnimFrm frm07 = {};
		frm07.fDuration = _fDuration;
		frm07.vLT = Vec2{ 260.f, 2.f };
		frm07.vOffset = Vec2{ 0.f, 0.f };
		frm07.vSlice = Vec2{ 34.f, 36.f };
		m_vecFrm.push_back(frm07);

		tAnimFrm frm08 = {};
		frm08.fDuration = _fDuration;
		frm08.vLT = Vec2{ 298.f, 0.f };
		frm08.vOffset = Vec2{ 0.f, 0.f };
		frm08.vSlice = Vec2{ 38.f, 38.f };
		m_vecFrm.push_back(frm08);

		return;
	}

	if (_strName == L"STOP_RIGHT" || _strName == L"STOP_LEFT")
	{
		tAnimFrm frm01 = {};
		frm01.fDuration = _fDuration;
		frm01.vLT = Vec2{ 0.f, 0.f };
		frm01.vOffset = Vec2{ 0.f, 0.f };
		frm01.vSlice = Vec2{ 44.f, 40.f };
		m_vecFrm.push_back(frm01);

		return;
	}

	if (_strName == L"JUMP_RIGHT" || _strName == L"JUMP_LEFT")
	{
		tAnimFrm frm01 = {};
		frm01.fDuration = _fDuration;
		frm01.vLT = Vec2{ 0.f, 0.f };
		frm01.vOffset = Vec2{ 0.f, 0.f };
		frm01.vSlice = Vec2{ 40.f, 40.f };
		m_vecFrm.push_back(frm01);

		return;
	}

	if (_strName == L"DROP_RIGHT" || _strName == L"DROP_LEFT")
	{
		tAnimFrm frm01 = {};
		frm01.fDuration = _fDuration;
		frm01.vLT = Vec2{ 0.f, 2.f };
		frm01.vOffset = Vec2{ 0.f, 0.f };
		frm01.vSlice = Vec2{ 42.f, 38.f };
		m_vecFrm.push_back(frm01);

		tAnimFrm frm02 = {};
		frm02.fDuration = _fDuration;
		frm02.vLT = Vec2{ 46.f, 4.f };
		frm02.vOffset = Vec2{ 0.f, 0.f };
		frm02.vSlice = Vec2{ 40.f, 36.f };
		m_vecFrm.push_back(frm02);

		tAnimFrm frm03 = {};
		frm03.fDuration = _fDuration;
		frm03.vLT = Vec2{ 88.f, 2.f };
		frm03.vOffset = Vec2{ 0.f, 0.f };
		frm03.vSlice = Vec2{ 42.f, 38.f };
		m_vecFrm.push_back(frm03);

		tAnimFrm frm04 = {};
		frm04.fDuration = _fDuration;
		frm04.vLT = Vec2{ 134.f, 0.f };
		frm04.vOffset = Vec2{ 0.f, 0.f };
		frm04.vSlice = Vec2{ 40.f, 40.f };
		m_vecFrm.push_back(frm04);

		tAnimFrm frm05 = {};
		frm05.fDuration = _fDuration;
		frm05.vLT = Vec2{ 178.f, 6.f };
		frm05.vOffset = Vec2{ 0.f, 0.f };
		frm05.vSlice = Vec2{ 42.f, 34.f };
		m_vecFrm.push_back(frm05);

		tAnimFrm frm06 = {};
		frm06.fDuration = _fDuration;
		frm06.vLT = Vec2{ 224.f, 4.f };
		frm06.vOffset = Vec2{ 0.f, 0.f };
		frm06.vSlice = Vec2{ 44.f, 36.f };
		m_vecFrm.push_back(frm06);

		tAnimFrm frm07 = {};
		frm07.fDuration = _fDuration;
		frm07.vLT = Vec2{ 272.f, 2.f };
		frm07.vOffset = Vec2{ 0.f, 0.f };
		frm07.vSlice = Vec2{ 42.f, 38.f };
		m_vecFrm.push_back(frm07);

		tAnimFrm frm08 = {};
		frm08.fDuration = _fDuration;
		frm08.vLT = Vec2{ 316.f, 2.f };
		frm08.vOffset = Vec2{ 0.f, 0.f };
		frm08.vSlice = Vec2{ 40.f, 38.f };
		m_vecFrm.push_back(frm08);

		return;
	}

	if (_strName == L"FLOAT_START_RIGHT" || _strName == L"FLOAT_START_LEFT")
	{
		tAnimFrm frm01 = {};
		frm01.fDuration = _fDuration;
		frm01.vLT = Vec2{ 0.f, 8.f };
		frm01.vOffset = Vec2{ 0.f, 0.f };
		frm01.vSlice = Vec2{ 38.f, 40.f };
		m_vecFrm.push_back(frm01);

		tAnimFrm frm02 = {};
		frm02.fDuration = _fDuration;
		frm02.vLT = Vec2{ 42.f, 4.f };
		frm02.vOffset = Vec2{ 0.f, 0.f };
		frm02.vSlice = Vec2{ 40.f, 44.f };
		m_vecFrm.push_back(frm02);

		tAnimFrm frm03 = {};
		frm03.fDuration = _fDuration;
		frm03.vLT = Vec2{ 86.f, 0.f };
		frm03.vOffset = Vec2{ 0.f, 0.f };
		frm03.vSlice = Vec2{ 42.f, 48.f };
		m_vecFrm.push_back(frm03);

		tAnimFrm frm04 = {};
		frm04.fDuration = _fDuration;
		frm04.vLT = Vec2{ 134.f, 0.f };
		frm04.vOffset = Vec2{ 0.f, 0.f };
		frm04.vSlice = Vec2{ 40.f, 48.f };
		m_vecFrm.push_back(frm04);

		return;
	}

	if (_strName == L"FLOAT_IDLE_RIGHT" || _strName == L"FLOAT_IDLE_LEFT")
	{
		tAnimFrm frm01 = {};
		frm01.fDuration = _fDuration;
		frm01.vLT = Vec2{ 0.f, 0.f };
		frm01.vOffset = Vec2{ 0.f, 0.f };
		frm01.vSlice = Vec2{ 48.f, 50.f };
		m_vecFrm.push_back(frm01);

		tAnimFrm frm02 = {};
		frm02.fDuration = _fDuration;
		frm02.vLT = Vec2{ 52.f, 2.f };
		frm02.vOffset = Vec2{ 0.f, 0.f };
		frm02.vSlice = Vec2{ 48.f, 48.f };
		m_vecFrm.push_back(frm02);

		return;
	}

	if (_strName == L"FLOAT_END_RIGHT" || _strName == L"FLOAT_END_LEFT")
	{
		tAnimFrm frm04 = {};
		frm04.fDuration = _fDuration;
		frm04.vLT = Vec2{ 134.f, 0.f };
		frm04.vOffset = Vec2{ 0.f, 0.f };
		frm04.vSlice = Vec2{ 40.f, 48.f };
		m_vecFrm.push_back(frm04);

		tAnimFrm frm03 = {};
		frm03.fDuration = _fDuration;
		frm03.vLT = Vec2{ 86.f, 0.f };
		frm03.vOffset = Vec2{ 0.f, 0.f };
		frm03.vSlice = Vec2{ 42.f, 48.f };
		m_vecFrm.push_back(frm03);

		tAnimFrm frm02 = {};
		frm02.fDuration = _fDuration;
		frm02.vLT = Vec2{ 42.f, 4.f };
		frm02.vOffset = Vec2{ 0.f, 0.f };
		frm02.vSlice = Vec2{ 40.f, 44.f };
		m_vecFrm.push_back(frm02);

		tAnimFrm frm01 = {};
		frm01.fDuration = _fDuration;
		frm01.vLT = Vec2{ 0.f, 8.f };
		frm01.vOffset = Vec2{ 0.f, 0.f };
		frm01.vSlice = Vec2{ 38.f, 40.f };
		m_vecFrm.push_back(frm01);

		return;
	}

	if (_strName == L"INHALE_RIGHT" || _strName == L"INHALE_LEFT")
	{
		tAnimFrm frm01 = {};
		frm01.fDuration = _fDuration;
		frm01.vLT = Vec2{ 0.f, 2.f };
		frm01.vOffset = Vec2{ 0.f, 0.f };
		frm01.vSlice = Vec2{ 46.f, 42.f };
		m_vecFrm.push_back(frm01);

		tAnimFrm frm02 = {};
		frm02.fDuration = _fDuration;
		frm02.vLT = Vec2{ 52.f, 0.f };
		frm02.vOffset = Vec2{ 0.f, 0.f };
		frm02.vSlice = Vec2{ 44.f, 44.f };
		m_vecFrm.push_back(frm02);

		return;
	}

	if (_strName == L"POWER_INHALE_RIGHT" || _strName == L"POWER_INHALE_LEFT")
	{
		tAnimFrm frm01 = {};
		frm01.fDuration = _fDuration;
		frm01.vLT = Vec2{ 0.f, 2.f };
		frm01.vOffset = Vec2{ 0.f, 0.f };
		frm01.vSlice = Vec2{ 46.f, 42.f };
		m_vecFrm.push_back(frm01);

		tAnimFrm frm02 = {};
		frm02.fDuration = _fDuration;
		frm02.vLT = Vec2{ 50.f, 0.f };
		frm02.vOffset = Vec2{ 0.f, 0.f };
		frm02.vSlice = Vec2{ 44.f, 44.f };
		m_vecFrm.push_back(frm02);

		return;
	}

	if (_strName == L"WADDLE_DEE_WALK_RIGHT" || _strName == L"WADDLE_DEE_WALK_LEFT")
	{
		tAnimFrm frm01 = {};
		frm01.fDuration = _fDuration;
		frm01.vLT = Vec2{ 0.f, 0.f };
		frm01.vOffset = Vec2{ 0.f, 0.f };
		frm01.vSlice = Vec2{ 38.f, 38.f };
		m_vecFrm.push_back(frm01);

		tAnimFrm frm02 = {};
		frm02.fDuration = _fDuration;
		frm02.vLT = Vec2{ 44.f, 0.f };
		frm02.vOffset = Vec2{ 0.f, 0.f };
		frm02.vSlice = Vec2{ 38.f, 38.f };
		m_vecFrm.push_back(frm02);

		tAnimFrm frm03 = {};
		frm03.fDuration = _fDuration;
		frm03.vLT = Vec2{ 88.f, 2.f };
		frm03.vOffset = Vec2{ 0.f, 0.f };
		frm03.vSlice = Vec2{ 38.f, 36.f };
		m_vecFrm.push_back(frm03);

		tAnimFrm frm04 = {};
		frm04.fDuration = _fDuration;
		frm04.vLT = Vec2{ 132.f, 2.f };
		frm04.vOffset = Vec2{ 0.f, 0.f };
		frm04.vSlice = Vec2{ 38.f, 36.f };
		m_vecFrm.push_back(frm04);

		tAnimFrm frm05 = {};
		frm05.fDuration = _fDuration;
		frm05.vLT = Vec2{ 176.f, 0.f };
		frm05.vOffset = Vec2{ 0.f, 0.f };
		frm05.vSlice = Vec2{ 44.f, 38.f };
		m_vecFrm.push_back(frm05);

		tAnimFrm frm06 = {};
		frm06.fDuration = _fDuration;
		frm06.vLT = Vec2{ 226.f, 2.f };
		frm06.vOffset = Vec2{ 0.f, 0.f };
		frm06.vSlice = Vec2{ 38.f, 36.f };
		m_vecFrm.push_back(frm06);

		tAnimFrm frm07 = {};
		frm07.fDuration = _fDuration;
		frm07.vLT = Vec2{ 270.f, 2.f };
		frm07.vOffset = Vec2{ 0.f, 0.f };
		frm07.vSlice = Vec2{ 38.f, 36.f };
		m_vecFrm.push_back(frm07);

		tAnimFrm frm08 = {};
		frm08.fDuration = _fDuration;
		frm08.vLT = Vec2{ 314.f, 0.f };
		frm08.vOffset = Vec2{ 0.f, 0.f };
		frm08.vSlice = Vec2{ 38.f, 38.f };
		m_vecFrm.push_back(frm08);

		return;
	}

	if (_strName == L"WADDLE_DEE_DRAWN_RIGHT" || _strName == L"WADDLE_DEE_DRAWN_LEFT")
	{
		tAnimFrm frm01 = {};
		frm01.fDuration = _fDuration;
		frm01.vLT = Vec2{ 0.f, 0.f };
		frm01.vOffset = Vec2{ 0.f, 0.f };
		frm01.vSlice = Vec2{ 42.f, 36.f };
		m_vecFrm.push_back(frm01);

		return;
	}

	if (_strName == L"SCARFY_IDLE_RIGHT" || _strName == L"SCARFY_IDLE_LEFT")
	{
		tAnimFrm frm01 = {};
		frm01.fDuration = _fDuration;
		frm01.vLT = Vec2{ 0.f, 8.f };
		frm01.vOffset = Vec2{ 0.f, 0.f };
		frm01.vSlice = Vec2{ 36.f, 28.f };
		m_vecFrm.push_back(frm01);

		tAnimFrm frm02 = {};
		frm02.fDuration = _fDuration;
		frm02.vLT = Vec2{ 42.f, 4.f };
		frm02.vOffset = Vec2{ 0.f, 0.f };
		frm02.vSlice = Vec2{ 36.f, 32.f };
		m_vecFrm.push_back(frm02);

		tAnimFrm frm03 = {};
		frm03.fDuration = _fDuration;
		frm03.vLT = Vec2{ 84.f, 0.f };
		frm03.vOffset = Vec2{ 0.f, 0.f };
		frm03.vSlice = Vec2{ 36.f, 36.f };
		m_vecFrm.push_back(frm03);

		return;
	}

	if (_strName == L"PENGY_IDLE_RIGHT" || _strName == L"PENGY_IDLE_LEFT")
	{
		tAnimFrm frm01 = {};
		frm01.fDuration = _fDuration;
		frm01.vLT = Vec2{ 0.f, 0.f };
		frm01.vOffset = Vec2{ 0.f, 0.f };
		frm01.vSlice = Vec2{ 40.f, 40.f };
		m_vecFrm.push_back(frm01);

		return;
	}

	if (_strName == L"STAR")
	{
		tAnimFrm frm01 = {};
		frm01.fDuration = _fDuration;
		frm01.vLT = Vec2{ 0.f, 0.f };
		frm01.vOffset = Vec2{ 0.f, 0.f };
		frm01.vSlice = Vec2{ 46.f, 48.f };
		m_vecFrm.push_back(frm01);

		return;
	}
}

void GameAnimation::Update()
{
	if (!m_bFinish)
	{
		m_fAccTime += fDT;

		if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
		{
			++m_iCurFrm;

			if (m_vecFrm.size() <= m_iCurFrm)
			{
				if (m_pAnimator->IsRepeatAnim())
					m_iCurFrm = -1;
				else m_iCurFrm -= 1;
				m_bFinish = true;
				m_fAccTime = 0.f;
				return;
			}

			m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;
		}
	}
}

void GameAnimation::Render(HDC _dc)
{
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