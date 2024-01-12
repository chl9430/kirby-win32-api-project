#include "pch.h"
#include "GameTile.h"

#include "GameCamera.h"

#include "GameTexture.h"
#include "GameCollider.h"
#include "GameGravity.h"

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
		pOtherObj->GetGravity()->SetGround(true);

		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		float fLen = abs(vObjPos.y - vPos.y); // 99 (dt������ 1�ȼ� ����)
		float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen; // 100 - 99 = 1

		// �浹�� ���� ���·� �����ϱ� ���� �Ϻη� 1�ȼ� �÷��ش�.
		vObjPos = pOtherObj->GetPos();
		vObjPos.y -= (fValue);

		pOtherObj->SetPos(vObjPos);
		_pOther->SetFinalPos(vObjPos);
	}
}

void GameTile::OnCollision(GameCollider* _pOther)
{
	GameObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player" || pOtherObj->GetName() == L"Monster")
	{
		pOtherObj->GetGravity()->SetGround(true);

		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		float fLen = abs(vObjPos.y - vPos.y);
		float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

		// �浹�� ���� ���·� �����ϱ� ���� �Ϻη� 1�ȼ� �÷��ش�.
		vObjPos = pOtherObj->GetPos();
		vObjPos.y -= (fValue);

		pOtherObj->SetPos(vObjPos);
		_pOther->SetFinalPos(vObjPos);
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