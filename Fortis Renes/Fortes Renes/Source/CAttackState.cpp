#include "CAttackState.h"
#include "CEnemy.h"
#include "CMessageSystem.h"

CAttackState::CAttackState()
{
}

CAttackState* CAttackState::GetInstance()
{
	static CAttackState instance;
	return &instance;
}

void CAttackState::CalculateAI(float fElapsedTime, CBase* pBase)
{
	CEnemy* pEnemy = (CEnemy*)pBase;
	pEnemy->GetWeapon()->Update(fElapsedTime);

	tVector2D distanceToTarget;

	distanceToTarget.fX = pEnemy->GetTarget()->GetPosX() - pEnemy->GetPosX();
	distanceToTarget.fY = pEnemy->GetTarget()->GetPosY() - pEnemy->GetPosY();

	if( Vector2DLength(distanceToTarget) > pEnemy->GetWeapon()->GetRange() )
	{
		pEnemy->Walk();
		distanceToTarget = Vector2DNormalize(distanceToTarget);
		distanceToTarget = distanceToTarget * pEnemy->GetSpeed();
		pEnemy->SetVelX((distanceToTarget.fX));
		pEnemy->SetVelY((distanceToTarget.fY));
	}
	else
	{
		pEnemy->Shoot();
		// Shoot at the player
		pEnemy->SetVelX(0.0f);
		pEnemy->SetVelY(0.0f);
		pEnemy->GetWeapon()->FireWeapon(pEnemy);
	}
}