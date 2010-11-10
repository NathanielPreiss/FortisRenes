#include "CIdleState.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include "CJeepState.h"
#include "CAttackState.h"
#include "CEventSystem.h"


CIdleState::CIdleState()
{
}

CIdleState* CIdleState::GetInstance()
{
	static CIdleState instance;
	return &instance;
}

void CIdleState::CalculateAI(float fElapsedTime, CBase* pBase)
{
	CEnemy* enemy = (CEnemy*)pBase;
	enemy->GetWeapon()->Update(fElapsedTime);
	tVector2D distanceToPlayer;

	distanceToPlayer.fX = CPlayer::GetInstance()->GetPosX()-enemy->GetPosX();
	distanceToPlayer.fY = CPlayer::GetInstance()->GetPosY()-enemy->GetPosY();

	if( Vector2DLength(distanceToPlayer) < 100 && DotProduct( enemy->GetFacing(), distanceToPlayer ) > 0 && CPlayer::GetInstance()->GetState() != CJeepState::GetInstance() )
	{
		enemy->SetTarget(CPlayer::GetInstance());
		enemy->ChangeState(CAttackState::GetInstance());
		CEventSystem::GetInstance()->SendEvent("player.detected",enemy);
	}
}