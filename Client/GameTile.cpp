#include "pch.h"
#include "GameTile.h"

#include "GameCamera.h"
#include "GameKeyMgr.h"

#include "GameTexture.h"
#include "GameCollider.h"
#include "GameGravity.h"
#include "GameRigidBody.h"

GameTile::GameTile()
{
}

GameTile::~GameTile()
{

}

void GameTile::Update()
{
}

void GameTile::Save(FILE* _pFile)
{
	// 타일의 위치
	fwprintf(_pFile, L"[Tile Pos]\n");
	fwprintf(_pFile, L"%d %d\n", (int)GetPos().x, (int)GetPos().y);
	fwprintf(_pFile, L"\n");

	// 타일의 텍스처
	fwprintf(_pFile, L"[Tile Texture]\n");
	fwprintf(_pFile, GetCurrentTexture()->GetKey().c_str());
	fwprintf(_pFile, L"\n\n");
}

void GameTile::OnCollisionEnter(GameCollider* _pOther)
{
	GameObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player" || pOtherObj->GetName() == L"Monster")
	{
	}
}

void GameTile::OnCollision(GameCollider* _pOther)
{
	GameObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player" || pOtherObj->GetName() == L"Monster")
	{
		FixObjPos(_pOther);
	}
}

void GameTile::OnCollisionExit(GameCollider* _pOther)
{
	GameObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player" || pOtherObj->GetName() == L"Monster")
	{
		pOtherObj->GetGravity()->SetGround(false);
	}
}

void GameTile::FixObjPos(GameCollider* _pOther)
{
	GameObject* pOtherObj = _pOther->GetObj();

	Vec2 vObjPos = _pOther->GetFinalPos();
	Vec2 vObjScale = _pOther->GetScale();

	Vec2 vPos = GetCollider()->GetFinalPos();
	Vec2 vScale = GetCollider()->GetScale();

	// 충돌체 간의 거리
	float fDiffX = vPos.x - vObjPos.x;
	float fDiffY = vPos.y - vObjPos.y;

	// 충돌 시 발생한 겹치는 부분의 사각형의 높이, 너비
	float fWidth = (vScale.x / 2.f + vObjScale.x / 2.f) - abs(fDiffX) - 1;
	float fHeight = (vScale.y / 2.f + vObjScale.y / 2.f) - abs(fDiffY) - 1;

	float fDir = 1.f;

	if (fWidth > fHeight) // 수직 충돌
	{
		if (fDiffY >= 0) // 캐릭터가 위에서 부딫힌 경우
		{
			pOtherObj->GetGravity()->SetGround(true);
			fDir = 1.f;
		}
		else // 캐릭터가 아래에서 부딫힌 경우
		{
			fDir = -1.f;
		}

		// 충돌을 접한 상태로 유지하기 위해 오차만큼 픽셀을 올려준다.
		vObjPos = pOtherObj->GetPos();
		vObjPos.y -= (fHeight * fDir);

		pOtherObj->SetPos(vObjPos);
		_pOther->SetFinalPos(vObjPos);
	}
	else if (fWidth < fHeight) // 수평 충돌
	{
		if (fDiffX >= 0) // 캐릭터가 왼쪽에서 부딫힌 경우
		{
			fDir = 1.f;
		}
		else // 캐릭터가 오른쪽에서 부딫힌 경우
		{
			fDir = -1.f;
		}

		// 충돌을 접한 상태로 유지하기 위해 오차만큼 픽셀을 올려준다.
		vObjPos = pOtherObj->GetPos();
		vObjPos.x -= (fWidth * fDir);

		pOtherObj->SetPos(vObjPos);
		_pOther->SetFinalPos(vObjPos);
	}
}