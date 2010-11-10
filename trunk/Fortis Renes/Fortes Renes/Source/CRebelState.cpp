#include "CRebelState.h"
#include "CAlly.h"
#include "CMessageSystem.h"
#include "CEventSystem.h"
#include "CWeapon.h"

CRebelState::CRebelState(void)
{
}

CRebelState::CRebelState(const CRebelState&)
{
}

CRebelState* CRebelState::GetInstance(void)
{
	static CRebelState instance;
	return &instance;
}

void CRebelState::CalculateAI(float fElapsedTime, CBase* pBase)
{
	CAlly* pRebel = (CAlly*)pBase;
	pRebel->GetWeapon()->Update(fElapsedTime);

	if( pRebel->GetTarget() != NULL )
	{
		tVector2D toTarget;
		toTarget.fX = pRebel->GetTarget()->GetPosX() - pRebel->GetPosX();
		toTarget.fY = pRebel->GetTarget()->GetPosY() - pRebel->GetPosY();

		if( Vector2DLength(toTarget) < pRebel->GetWeapon()->GetRange() )
		{
			pRebel->GetWeapon()->FireWeapon(pRebel);
		}
	}
}