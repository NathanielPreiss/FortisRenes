#include "CHostageState.h"
#include "CAlly.h"
#include "DirectX Wrappers/SGD_Math.h"
#include "CPlayer.h"

CHostageState::CHostageState()
{
}

CHostageState* CHostageState::GetInstance()
{
	static CHostageState instance;
	return &instance;
}

void CHostageState::CalculateAI(float fElapsedTime, CBase* pBase)
{
	CAlly* hostage = (CAlly*)pBase;

	tVector2D vectorToPlayer;

	vectorToPlayer.fX = CPlayer::GetInstance()->GetPosX() - hostage->GetPosX();
	vectorToPlayer.fY = CPlayer::GetInstance()->GetPosY() - hostage->GetPosY();

	if( Vector2DLength(vectorToPlayer) < 100 )
	{
		Vector2DNormalize(vectorToPlayer);
		vectorToPlayer = vectorToPlayer * (float)hostage->GetSpeed();

		hostage->SetVelX(vectorToPlayer.fX);
		hostage->SetVelY(vectorToPlayer.fY);
	}
	else
	{
		hostage->SetVelX(0.0f);
		hostage->SetVelY(0.0f);
	}
}