#include "CTank.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"
#include "CEvent.h"
#include "CPlayer.h"
#include "CTankState.h"

CTank::CTank(void)
{
	SetCoverObject(false);



}

CTank::~CTank(void)
{
}

void CTank::Render(float fCamPosX, float fCamPosY)
{
	CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)((GetPosX() - GetWidth()*0.5f) - fCamPosX), 
								(int)((GetPosY() - GetHeight() *0.5f) - fCamPosY), 1.0f, 1.0f, 0, GetWidth()*0.5f, GetHeight()*0.5f, m_fRot);
	
}

void CTank::Update(float fElapsedTime)
{
	
}

void CTank::HandleEvent( CEvent* pEvent )
{
	CPlayer* pPlayer = CPlayer::GetInstance();

	if(pEvent->GetEventID() == "Change_Position" && pEvent->GetParam() == this)
	{
		SetPosX(-200.0f);
		SetPosY(-200.0f);
	}

	if(pEvent->GetEventID() == "Spawn_Tank" && pEvent->GetParam() == this)
	{
		SetPosX(pPlayer->GetPosX()+20);
		SetPosY(pPlayer->GetPosY());
		SetDirection(CTankState::GetInstance()->GetDirectionX(), CTankState::GetInstance()->GetDirectionY());
		SetRotation(CTankState::GetInstance()->GetRotation());
	}
}