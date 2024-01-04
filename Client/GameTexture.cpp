#include "pch.h"
#include "GameTexture.h"

#include "GameCore.h"

GameTexture::GameTexture()
	: m_dc{}
	, m_hBit{}
	, m_bitInfo{}
{
}

GameTexture::~GameTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}

void GameTexture::Load(const wstring& _strFilePath)
{
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	// assert(m_hBit);

	m_dc = CreateCompatibleDC(GameCore::GetInst()->GetMainDC()); // 새로운 이미지 비트맵용 dc를 생성

	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit); // 디폴트로 만들어진 비트맵을 삭제하고, 이미지 비트맵을 방금 만든 비트맵용 dc에 연결
	DeleteObject(hPrevBit);

	// 비트맵정보
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}

void GameTexture::Create(UINT _iWidth, UINT _iHeight)
{
	HDC mainDC = GameCore::GetInst()->GetMainDC(); // 메인 DC를 가져온다.

	// 이중 버퍼링 용도의 비트맵과 DC를 생성
	m_hBit = CreateCompatibleBitmap(mainDC, _iWidth, _iHeight);
	m_dc = CreateCompatibleDC(mainDC); // 그림을 그릴 사본용 DC(Device Context)를 생성

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_dc, m_hBit); // 그림 그릴 타겟을 바꾸고
	DeleteObject(hOldBit); // 디폴트로 생성된 1px 비트맵을 삭제

	// 비트맵 정보
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}