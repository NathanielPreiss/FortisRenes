#include "CPlayerInfantryState.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"
#include "DirectX Wrappers/CSGD_DirectInput.h"
#include "CEventSystem.h"
#include "CMessageSystem.h"
#include "CTalkingState.h"
#include "CBitmapFont.h"
#include "CGame.h"
#include "CDialogueManager.h"


CPlayerInfantryState::CPlayerInfantryState(void)
{
	m_pPlayer = CPlayer::GetInstance();	
}
CPlayerInfantryState::~CPlayerInfantryState(void)
{

}
CPlayerInfantryState* CPlayerInfantryState::GetInstance(void)
{
	static CPlayerInfantryState instance;
	return &instance;
}

void CPlayerInfantryState::Enter()
{
	m_pPlayer = CPlayer::GetInstance();
	m_pPlayer->SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/Player.png"));
	m_pPlayer->SetWidth(16);
	m_pPlayer->SetHeight(20);
	m_pPlayer->SetVelX(250.0f);
	m_pPlayer->SetVelY(250.0f);
	m_nHudID = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/PlayerHUD_BG.png");
}

void CPlayerInfantryState::Update(float fElapsedTime)
{
	const D3DPRESENT_PARAMETERS *d3dpp = CSGD_Direct3D::GetInstance()->GetPresentParams();

#pragma region Attack Controls
	if(CSGD_DirectInput::GetInstance()->MouseButtonDown(0))
	{
		if( m_pPlayer->GetNumWeapons() - 1 >= 0 )
		{
			m_pPlayer->Shoot();
			m_pPlayer->GetCurrWeapon()->FireWeapon(m_pPlayer);
		}
	}
	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_UP) || CSGD_DirectInput::GetInstance()->MouseWheelMovement() < 0)
	{
		m_pPlayer->NextWeapon();
	}
	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_DOWN) || CSGD_DirectInput::GetInstance()->MouseWheelMovement() > 0)
	{
		m_pPlayer->PrevWeapon();
	}
	
	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_TAB))
	{
		m_pPlayer->NextItem();
	}
	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_SPACE))
	{
		m_pPlayer->GetInventory()->UseItem(m_pPlayer->GetCurrItem());
	}

#pragma endregion

#pragma region Movement Controls

	bool bIsMoving = false;

	if( CSGD_DirectInput::GetInstance()->KeyDown( DIK_W ) )
	{
		bIsMoving = true;
		m_pPlayer->Walk();
		m_pPlayer->SetPosY( m_pPlayer->GetPosY() - (m_pPlayer->GetSpeed() * fElapsedTime));
	}
	else if( CSGD_DirectInput::GetInstance()->KeyDown( DIK_S ) )
	{
		bIsMoving = true;
		m_pPlayer->Walk();
		m_pPlayer->SetPosY( m_pPlayer->GetPosY() + (m_pPlayer->GetSpeed() * fElapsedTime));
	}

	if( CSGD_DirectInput::GetInstance()->KeyDown( DIK_A ) )
	{
		bIsMoving = true;
		m_pPlayer->Walk();
		m_pPlayer->SetPosX( m_pPlayer->GetPosX() - (m_pPlayer->GetSpeed() * fElapsedTime));
	}
	else if( CSGD_DirectInput::GetInstance()->KeyDown( DIK_D ) )
	{
		bIsMoving = true;
		m_pPlayer->Walk();
		m_pPlayer->SetPosX( m_pPlayer->GetPosX() + (m_pPlayer->GetSpeed() * fElapsedTime));
	}
	else if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_RETURN ))
	{
		if( m_pPlayer->GetTalkBool() == true )
		{
			m_pPlayer->Idle();
			CDialogueManager::GetInstance()->UseProgressDialogue();
			CGame::GetInstance()->AddState(CTalkingState::GetInstance());
			m_pPlayer->SetTalkBool(false);
		}
	}

	if( bIsMoving == false )
		m_pPlayer->Idle();

#pragma endregion

#pragma region Player Out of Bounds Check

	if( m_pPlayer->GetPosX() - m_pPlayer->GetWidth()*0.5f < 0.0f )
	{
		m_pPlayer->SetPosX(0.0f + m_pPlayer->GetWidth() * 0.5f);
	}

	if( m_pPlayer->GetPosY() - m_pPlayer->GetHeight()*0.5f < 0.0f )
	{
		m_pPlayer->SetPosY(0.0f + m_pPlayer->GetHeight() * 0.5f);
	}


#pragma endregion

#pragma region Debug Controls

	// Add a healthpack just above the player
	if( CSGD_DirectInput::GetInstance()->KeyPressed(DIK_NUMPAD1) )
	{
		CMessageSystem::GetInstance()->SendMsg(new CTesterMedPack(m_pPlayer));
	}
	if( CSGD_DirectInput::GetInstance()->KeyPressed(DIK_NUMPADMINUS) )
	{
		m_pPlayer->SetHealth(m_pPlayer->GetHealth()-10);
	}
#pragma endregion

}
void CPlayerInfantryState::Render(float fCamPosX, float fCamPosY)
{
	CSGD_TextureManager::GetInstance()->Draw(m_nHudID, 42, 370);
	CSGD_TextureManager::GetInstance()->Draw(m_nHudID, 423, 370);
	char buffer[32];
	sprintf_s(buffer, _countof(buffer), "Health: %d : %d", m_pPlayer->GetMaxHealth(), m_pPlayer->GetHealth());
	CBitmapFont::GetInstance()->Draw(buffer, 64, 410, 0.5f);
	
	m_pPlayer->GetInventory()->Render(m_pPlayer->GetCurrItem());

	if( m_pPlayer->GetNumWeapons() > 0 )
	{
		m_pPlayer->PrevWeapon();
		CSGD_TextureManager::GetInstance()->Draw(m_pPlayer->GetCurrWeapon()->GetImageID(), 426, 400, 0.5f, 0.5f);
		m_pPlayer->NextWeapon();
		CSGD_TextureManager::GetInstance()->Draw(m_pPlayer->GetCurrWeapon()->GetImageID(), 469, 375, 1.0f, 1.0f);
		m_pPlayer->NextWeapon();
		CSGD_TextureManager::GetInstance()->Draw(m_pPlayer->GetCurrWeapon()->GetImageID(), 555, 400, 0.5f, 0.5f);
		m_pPlayer->PrevWeapon();

		sprintf_s(buffer, _countof(buffer), "%d", m_pPlayer->GetCurrWeapon()->GetCurrMagazine());
		CBitmapFont::GetInstance()->Draw(buffer, 476, 410, 0.5f);
	

		sprintf_s(buffer, _countof(buffer), "%d", m_pPlayer->GetCurrWeapon()->GetCurrAmmo());
		CBitmapFont::GetInstance()->DrawCenter(buffer, 550, 410, 0.5f);
	}
	
	if(m_pPlayer->GetAnimation() != NULL && m_pPlayer->GetAnimation()->currSheet != NULL)
		m_pPlayer->GetAnimation()->Render((m_pPlayer->GetPosX()-m_pPlayer->GetWidth()*0.5f) - fCamPosX, (m_pPlayer->GetPosY()-m_pPlayer->GetHeight()*0.5f) - fCamPosY, 1.0f, 1.0f);
	else
		CSGD_TextureManager::GetInstance()->Draw(m_pPlayer->GetImageID(), (int)(m_pPlayer->GetPosX() - (m_pPlayer->GetWidth() * 0.5f) - fCamPosX),
														 (int)(m_pPlayer->GetPosY() - (m_pPlayer->GetHeight() * 0.5f) - fCamPosY), 
														 1.0f, 1.0f, 0, m_pPlayer->GetWidth()*0.5f, m_pPlayer->GetHeight()*0.5f);
	}