#include "CTankState.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"
#include "DirectX Wrappers/CSGD_DirectInput.h"
#include "DirectX Wrappers/SGD_Math.h"
#include "CCamera.h"
#include "CGame.h"
#include "CCursor.h"
#include "CTank.h"
#include "CBitmapFont.h"
#include "Tinyxml/tinyxml.h"
#include "CPlayerInfantryState.h"
#include "CEventSystem.h"
#include "CMessageSystem.h"
#include "CPlayerInfantryState.h"
#include "CGame.h"

CTankState::CTankState(void)
{
	m_nBaseImageID = 0;
	m_nTurretImageID = 0;
	m_fRot = 0.0f;
	m_fTurretRot = 0.0f;
	m_vDirection.fX = 0.0f;
	m_vDirection.fY = -1.0f;
}

//		destructor
CTankState::~CTankState(void)
{
	//CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBaseImageID);
	//CSGD_TextureManager::GetInstance()->UnloadTexture(m_nTurretImageID);
}

//	Singleton accessor
CTankState* CTankState::GetInstance(void)
{
	static CTankState instance;
	return &instance;
}

void CTankState::Enter()
{
	m_nBaseImageID = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/Tank.png", D3DCOLOR_XRGB(255,0,255));
	m_nTurretImageID = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/turret.png", D3DCOLOR_XRGB(255,0,255));
	pPlayer = CPlayerInfantryState::GetInstance()->GetPlayer();
	pPlayer->SetImageID(m_nBaseImageID);
	pPlayer->SetWidth(64);
	pPlayer->SetHeight(64);
	pPlayer->SetCurrentWeapon(WEP_BAZOOKA);
	pPlayer->SetHealth(500);

	m_fRot = CPlayer::GetInstance()->GetTempTank()->GetRotation();
	m_vDirection = CPlayer::GetInstance()->GetTempTank()->GetDirection();
	m_fRotationRate = 3.14f;

	SetSpeed(0.0f);
	m_fAccelerationRate = 100.0f;
}

void CTankState::Update(float fElapsedTime)
{
	if( CSGD_DirectInput::GetInstance()->KeyDown( DIK_W ) )
	{
		SetSpeed( GetSpeed() + GetAccelerationRate() * fElapsedTime );
		if(GetSpeed() > 50)
			SetSpeed(50.0f);
	}
	else if( CSGD_DirectInput::GetInstance()->KeyDown( DIK_S ) )
	{
		SetSpeed( GetSpeed() - GetAccelerationRate() * fElapsedTime );
		if(GetSpeed() < -50)
			SetSpeed(-50.0f);
	}

	if( CSGD_DirectInput::GetInstance()->KeyDown( DIK_A ) )
	{
		m_fRot = m_fRot - m_fRotationRate * fElapsedTime;
		m_vDirection = Vector2DRotate( m_vDirection, -m_fRotationRate * fElapsedTime );
	}
	else if( CSGD_DirectInput::GetInstance()->KeyDown( DIK_D ) )
	{
		m_fRot =  m_fRot + m_fRotationRate * fElapsedTime;
		m_vDirection = Vector2DRotate( m_vDirection, m_fRotationRate * fElapsedTime );
	}

	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_E))
	{
		pPlayer->SetCurrentWeapon(WEP_PISTOL);
		CEventSystem::GetInstance()->SendEvent("Spawn_Tank", CPlayer::GetInstance()->GetTempTank());

		ChangeState(CPlayerInfantryState::GetInstance());
	}

	pPlayer->SetVelX( (m_vDirection.fX * GetSpeed()) );
	pPlayer->SetVelY( (m_vDirection.fY * GetSpeed()) );

	pPlayer->SetPosX( pPlayer->GetPosX() + (pPlayer->GetVelX() * fElapsedTime));
	pPlayer->SetPosY( pPlayer->GetPosY() + (pPlayer->GetVelY() * fElapsedTime));

	if(CSGD_DirectInput::GetInstance()->MouseButtonDown(0))
	{
		CEventSystem::GetInstance()->SendEvent("big.bang", pPlayer);
		CMessageSystem::GetInstance()->SendMsg(new CCreatePlayerBullet(pPlayer));
	}

	// Turret Rotation
	///////////////////////////////////////////////////////////////////////////////////////
	tVector2D vDirection;
	tVector2D player;
	player.fX = 0.0f;
	player.fY = -1.0f;
	vDirection.fX = ((CCursor::GetInstance()->GetPosX() + CCamera::GetInstance()->GetPosX()) - pPlayer->GetPosX());
	vDirection.fY = ((CCursor::GetInstance()->GetPosY() + CCamera::GetInstance()->GetPosY()) - pPlayer->GetPosY());
	vDirection = Vector2DNormalize(vDirection);

	m_fTurretRot = AngleBetweenVectors(player, vDirection);
	if(CCursor::GetInstance()->GetPosX() + CCamera::GetInstance()->GetPosX() < pPlayer->GetPosX())
		m_fTurretRot = -m_fTurretRot;
	///////////////////////////////////////////////////////////////////////////////////////
	if( pPlayer->GetPosX() - pPlayer->GetWidth()*0.5f < 0.0f )
	{
		pPlayer->SetPosX(0.0f + pPlayer->GetWidth() * 0.5f);
	}

	if( pPlayer->GetPosY() - pPlayer->GetHeight()*0.5f < 0.0f )
	{
		pPlayer->SetPosY(0.0f + pPlayer->GetHeight() * 0.5f);
	}

	if(pPlayer->GetHealth() < 0)
	{
		pPlayer->SetHealth(100);
		pPlayer->SetCurrentWeapon(WEP_PISTOL);

		ChangeState(CPlayerInfantryState::GetInstance());
	}
}

void CTankState::Render(float fCamPosX, float fCamPosY)
{
	CSGD_TextureManager::GetInstance()->Draw(m_nBaseImageID, (int)((pPlayer->GetPosX() - pPlayer->GetWidth()*0.5f) - fCamPosX), 
		(int)((pPlayer->GetPosY() - pPlayer->GetHeight() * 0.5f) - fCamPosY), 1.0f, 1.0f, 0, pPlayer->GetWidth()*0.5f, pPlayer->GetHeight()*0.5f, 
		m_fRot);

	CSGD_TextureManager::GetInstance()->Draw(m_nTurretImageID, (int)((pPlayer->GetPosX() - pPlayer->GetWidth()/3) - fCamPosX), 
		(int)((pPlayer->GetPosY() - pPlayer->GetHeight() /2) - fCamPosY), 1.0f, 1.0f, 0, (float)pPlayer->GetWidth()/3, (float)pPlayer->GetHeight()/2, 
		m_fTurretRot);
}

void CTankState::HandleEvent( CEvent* pEvent )
{

}

void CTankState::ChangeState( IPlayerState* newState )
{
	pPlayer->SetPlayerState(newState);
	pPlayer->GetPlayerState()->Enter();
}