#include "pch.h"
#include "GameTile.h"

#include "GameCamera.h"
#include "GameKeyMgr.h"

#include "GameTexture.h"
#include "GameCollider.h"
#include "GameGravity.h"
#include "GameRigidBody.h"

GameTile::GameTile(wstring _strName, Vec2 _vPos, Vec2 _vScale)
	: GameObject{ _strName, _vPos, _vScale }
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
	// Ÿ���� ��ġ
	fwprintf(_pFile, L"[Tile Pos]\n");
	fwprintf(_pFile, L"%d %d\n", (int)GetPos().x, (int)GetPos().y);
	fwprintf(_pFile, L"\n");

	// Ÿ���� �ؽ�ó
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

	if (pOtherObj->GetName() == L"Player" || pOtherObj->GetName() == L"Monster" || pOtherObj->GetName() == L"LeftSight" || pOtherObj->GetName() == L"RightSight")
	{
		FixObjPos(_pOther);
	}
}

void GameTile::OnCollisionExit(GameCollider* _pOther)
{
	GameObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player" || pOtherObj->GetName() == L"Monster" || pOtherObj->GetName() == L"LeftSight" || pOtherObj->GetName() == L"RightSight")
	{
		pOtherObj->SetTouchBottom(false);
		pOtherObj->SetTouchTop(false);
		pOtherObj->SetTouchLeft(false);
		pOtherObj->SetTouchRight(false);
	}
}

void GameTile::FixObjPos(GameCollider* _pOther)
{
	GameObject* pOtherObj = _pOther->GetObj();

	Vec2 vObjPos = _pOther->GetFinalPos();
	Vec2 vObjScale = _pOther->GetScale();

	Vec2 vPos = GetCollider()->GetFinalPos();
	Vec2 vScale = GetCollider()->GetScale();

	// �浹ü ���� �Ÿ�
	float fDiffX = vPos.x - vObjPos.x;
	float fDiffY = vPos.y - vObjPos.y;

	// �浹 �� �߻��� ��ġ�� �κ��� �簢���� ����, �ʺ�
	float fWidth = (vScale.x / 2.f + vObjScale.x / 2.f) - abs(fDiffX) - 1;
	float fHeight = (vScale.y / 2.f + vObjScale.y / 2.f) - abs(fDiffY) - 1;

	float fDir = 1.f;

	if (fWidth > fHeight) // ���� �浹
	{
		if (fDiffY >= 0) // ĳ���Ͱ� ������ �΋H�� ���
		{
			pOtherObj->SetTouchBottom(true);
			fDir = 1.f;
		}
		else // ĳ���Ͱ� �Ʒ����� �΋H�� ���
		{
			pOtherObj->SetTouchTop(true);
			fDir = -1.f;
		}

		// �浹�� ���� ���·� �����ϱ� ���� ������ŭ �ȼ��� �÷��ش�.
		vObjPos = pOtherObj->GetPos();
		vObjPos.y -= (fHeight * fDir);

		pOtherObj->SetPos(vObjPos);
		_pOther->SetFinalPos(vObjPos);
	}
	else if (fWidth < fHeight) // ���� �浹
	{
		if (fDiffX >= 0) // ĳ���Ͱ� ���ʿ��� �΋H�� ���
		{
			pOtherObj->SetTouchRight(true);
			fDir = 1.f;
		}
		else // ĳ���Ͱ� �����ʿ��� �΋H�� ���
		{
			pOtherObj->SetTouchLeft(true);
			fDir = -1.f;
		}

		// �浹�� ���� ���·� �����ϱ� ���� ������ŭ �ȼ��� �÷��ش�.
		vObjPos = pOtherObj->GetPos();
		vObjPos.x -= (fWidth * fDir);

		pOtherObj->SetPos(vObjPos);
		_pOther->SetFinalPos(vObjPos);
	}
}