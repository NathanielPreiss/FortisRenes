#include "CFleeState.h"
#include "CEventSystem.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include "DirectX Wrappers/SGD_Math.h"
#include "CIdleState.h"

CFleeState::CFleeState()
{
}

CFleeState* CFleeState::GetInstance()
{
	static CFleeState instance;
	return &instance;
}

void CFleeState::CalculateAI(float fElapsedTime, CBase* pBase)
{
	CEnemy* pEnemy = (CEnemy*)pBase;
	pEnemy->GetWeapon()->Update(fElapsedTime);

	pEnemy->Walk();

	if( pEnemy->GetTarget() != NULL )
	{
		if( pEnemy->GetTarget()->GetType() == OBJECT_PLAYER )
		{
			CEventSystem::GetInstance()->SendEvent("need.cover",pEnemy);
		}
		else
		{
			bool hidden = false;
			tVector2D vectorToTarget;
			tVector2D vectorToPlayer;
			tVector2D targetToPlayer;
			tVector2D targetToEnemy;

			vectorToTarget.fX = pEnemy->GetTarget()->GetPosX() - pEnemy->GetPosX();
			vectorToTarget.fY = pEnemy->GetTarget()->GetPosY() - pEnemy->GetPosY();

			vectorToPlayer.fX = CPlayer::GetInstance()->GetPosX() - pEnemy->GetPosX();
			vectorToPlayer.fY = CPlayer::GetInstance()->GetPosY() - pEnemy->GetPosY();

			targetToPlayer.fX = CPlayer::GetInstance()->GetPosX() - pEnemy->GetTarget()->GetPosX();
			targetToPlayer.fY = CPlayer::GetInstance()->GetPosY() - pEnemy->GetTarget()->GetPosY();

			targetToEnemy.fX = pEnemy->GetPosX() - pEnemy->GetTarget()->GetPosX();
			targetToEnemy.fY = pEnemy->GetPosY() - pEnemy->GetTarget()->GetPosY();

			// Check if Line of sight is broken... ... ...sorta
			if( acos(DotProduct(targetToPlayer,targetToEnemy)) == D3DX_PI )
				hidden = true;
			

			if( hidden == false )
			{
				targetToEnemy = targetToEnemy;
				float rotation = (D3DX_PI * 0.5f) * fElapsedTime;
				targetToEnemy = Vector2DRotate(targetToEnemy,rotation);
				vectorToTarget = vectorToTarget - targetToEnemy;
				vectorToTarget = Vector2DNormalize(vectorToTarget);
				pEnemy->SetVelX(vectorToTarget.fX * pEnemy->GetSpeed());
				pEnemy->SetVelY(vectorToTarget.fY * pEnemy->GetSpeed());
			}
			else
			{
				pEnemy->SetVelX(0.0f);
				pEnemy->SetVelY(0.0f);
				pEnemy->SetHealth(pEnemy->GetHealth()+(int)(15*fElapsedTime));
			}

			if( pEnemy->GetHealth() > (0.85f*pEnemy->GetMaxHealth()) )
			{
				pEnemy->ChangeState(CIdleState::GetInstance());
			}

		}
	}
}