#include "CJeepState.h"
#include "CBase.h"
#include "CJeep.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"
#include "DirectX Wrappers/CSGD_DirectInput.h"
#include "CObjectManager.h"
#include "CCamera.h"
#include "CGame.h"
#include "CBitmapFont.h"
#include "Tinyxml/tinyxml.h"
#include "CPlayerInfantryState.h"
#include "CEventSystem.h"
#include "CBitmapFont.h"

CJeepState::CJeepState(void)
{
	m_nImageID = 0;
	m_fRot = 0.0f;
	m_vDirection.fX = 0.0f;
	m_vDirection.fY = -1.0f;
}

//		destructor
CJeepState::~CJeepState(void)
{
	//CSGD_TextureManager::GetInstance()->UnloadTexture(m_nImageID);
}

//	Singleton accessor
CJeepState* CJeepState::GetInstance(void)
{
	static CJeepState instance;
	return &instance;
}

void CJeepState::Enter()
{
	m_nImageID = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/vehicle.png");
	pPlayer = CPlayerInfantryState::GetInstance()->GetPlayer();
	pPlayer->SetImageID(m_nImageID);
	pPlayer->SetWidth(32);
	pPlayer->SetHeight(64);
	pPlayer->SetHealth(400);
	pPlayer->SetMaxHealth(400);

	m_vDirection = pPlayer->GetTempJeep()->GetDirection();

	m_fRotationRate = 3.14f;
	m_fSpeed = 0.0f;
	m_fAccelerationRate = 100.0f;
	m_fRot = CPlayer::GetInstance()->GetTempJeep()->GetRotation();
}

void CJeepState::Update(float fElapsedTime)
{
	if( CSGD_DirectInput::GetInstance()->KeyDown( DIK_W ) )
	{
		SetSpeed( GetSpeed() + GetAccelerationRate() * fElapsedTime );
		if(GetSpeed() > 250)
			SetSpeed(250.0f);
	}
	else if( CSGD_DirectInput::GetInstance()->KeyDown( DIK_S ) )
	{
		SetSpeed( GetSpeed() - GetAccelerationRate() * fElapsedTime );
		if(GetSpeed() < -250)
			SetSpeed(-250.0f);
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
		pPlayer->SetDriving(false);
		pPlayer->SetHealth(100);
		pPlayer->SetMaxHealth(100);
		CEventSystem::GetInstance()->SendEvent("Spawn_Jeep", CPlayer::GetInstance()->GetTempJeep());

		ChangeState(CPlayerInfantryState::GetInstance());
	}

	pPlayer->SetVelX( (m_vDirection.fX * GetSpeed()) );
	pPlayer->SetVelY( (m_vDirection.fY * GetSpeed()) );

	pPlayer->SetPosX( pPlayer->GetPosX() + (pPlayer->GetVelX() * fElapsedTime));
	pPlayer->SetPosY( pPlayer->GetPosY() + (pPlayer->GetVelY() * fElapsedTime));

	if( pPlayer->GetPosX() - pPlayer->GetWidth()*0.5f < 0.0f )
	{
		pPlayer->SetPosX(0.0f + pPlayer->GetWidth() * 0.5f);
	}

	if( pPlayer->GetPosY() - pPlayer->GetHeight()*0.5f < 0.0f )
	{
		pPlayer->SetPosY(0.0f + pPlayer->GetHeight() * 0.5f);
	}

	if(pPlayer->GetHealth() < 150)
	{
		pPlayer->SetHealth(100);
		pPlayer->SetMaxHealth(100);
		pPlayer->SetDriving(false);

		ChangeState(CPlayerInfantryState::GetInstance());
	}
}

void CJeepState::Render(float fCamPosX, float fCamPosY)
{
	CSGD_TextureManager::GetInstance()->Draw(m_nImageID, (int)((pPlayer->GetPosX() - pPlayer->GetWidth()*0.5f) - fCamPosX), (int)((pPlayer->GetPosY() - pPlayer->GetHeight() * 0.5f) - fCamPosY), 1.0f, 1.0f, 0, pPlayer->GetWidth()*.5f, pPlayer->GetHeight()*.5f, m_fRot);

	CPlayerInfantryState* IS = CPlayerInfantryState::GetInstance();

	CSGD_TextureManager::GetInstance()->Draw(IS->GetHud(), 42, 370);
	CSGD_TextureManager::GetInstance()->Draw(IS->GetHud(), 423, 370);
	char buffer[32];
	sprintf_s(buffer, _countof(buffer), "Health: %d : %d", pPlayer->GetMaxHealth()-150, pPlayer->GetHealth()-150);
	CBitmapFont::GetInstance()->Draw(buffer, 64, 410, 0.5f);
	
	pPlayer->GetInventory()->Render(pPlayer->GetCurrItem());

	if( pPlayer->GetNumWeapons() > 0 )
	{
		pPlayer->PrevWeapon();
		CSGD_TextureManager::GetInstance()->Draw(pPlayer->GetCurrWeapon()->GetImageID(), 426, 400, 0.5f, 0.5f);
		pPlayer->NextWeapon();
		CSGD_TextureManager::GetInstance()->Draw(pPlayer->GetCurrWeapon()->GetImageID(), 469, 375, 1.0f, 1.0f);
		pPlayer->NextWeapon();
		CSGD_TextureManager::GetInstance()->Draw(pPlayer->GetCurrWeapon()->GetImageID(), 555, 400, 0.5f, 0.5f);
		pPlayer->PrevWeapon();

		sprintf_s(buffer, _countof(buffer), "%d", pPlayer->GetCurrWeapon()->GetCurrMagazine());
		CBitmapFont::GetInstance()->Draw(buffer, 476, 410, 0.5f);
	

		sprintf_s(buffer, _countof(buffer), "%d", pPlayer->GetCurrWeapon()->GetCurrAmmo());
		CBitmapFont::GetInstance()->DrawCenter(buffer, 550, 410, 0.5f);
	}
}

void CJeepState::ChangeState( IPlayerState* newState )
{
	pPlayer->SetPlayerState(newState);
	pPlayer->GetPlayerState()->Enter();
}