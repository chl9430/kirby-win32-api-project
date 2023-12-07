#include "pch.h"
#include "GameCollisionMgr.h"

#include "GameSceneMgr.h"

#include "GameScene.h"
#include "GameObject.h"
#include "GameCollider.h"

GameCollisionMgr::GameCollisionMgr()
	: m_arrCheck{}
	, m_mapColInfo{}
{
}

GameCollisionMgr::~GameCollisionMgr()
{
}

void GameCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	GameScene* pCurScene = GameSceneMgr::GetInst()->GetCurScene();

	const vector<GameObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<GameObject*>& vecRight = pCurScene->GetGroupObject(_eRight);
	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		if (nullptr == vecLeft[i]->GetCollider()) // 오브젝트에 충돌체가 없다면
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			if (nullptr == vecRight[j]->GetCollider() || vecLeft[i] == vecRight[i])
				continue;

			GameCollider* pLeftCol = vecLeft[i]->GetCollider();
			GameCollider* pRightCol = vecRight[i]->GetCollider();

			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID);

			if (m_mapColInfo.end() == iter) // 두 물체간의 충돌정보가 없다면
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			// 충돌로직 구현
			if (IsCollision(pLeftCol, pRightCol))
			{
				if (iter->second) // 이전 프레임, 현재 프레임 둘다 충돌중이면
				{
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}
				}
				else // 이전 프레임에는 충돌하지 않았다면(방금 충돌하였다면)
				{
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
			}
			else
			{
				if (iter->second) // 이전 프레임에는 충돌했다면(충돌을 빠져나갔다면)
				{
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool GameCollisionMgr::IsCollision(GameCollider* _pLeftCol, GameCollider* _pRightCol)
{
	Vec2 vLeftPos = _pLeftCol->GetFinalPos();
	Vec2 vLeftScale = _pLeftCol->GetScale();

	Vec2 vRightPos = _pRightCol->GetFinalPos();
	Vec2 vRightScale = _pRightCol->GetScale();

	if (abs(vRightPos.x - vLeftPos.x) <= (vLeftScale.x + vRightScale.x) / 2.f
		&& abs(vRightPos.y - vLeftPos.y) <= (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}

void GameCollisionMgr::Update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void GameCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	UINT iRow = (UINT)_eLeft; // 콜리젼 2차원 배열의 열
	UINT iCol = (UINT)_eRight; // 콜리젼 2차원 배열의 행

	if (iRow > iCol)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}
}