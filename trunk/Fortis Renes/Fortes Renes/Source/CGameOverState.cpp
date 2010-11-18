///////////////////////////////////////////////////
// File: "CGameOverState.cpp"
//
// Date Edited: 11/3/2010
//
// Purpose: Fill functions that are declared in
//			class header
//////////////////////////////////////////////////

#include "CGameOverState.h"
#include "CMainMenuState.h"
#include "CGamePlayState.h"
#include "CPlayer.h"
#include "DirectX Wrappers/CSGD_WaveManager.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "CGame.h"

CGameOverState::CGameOverState(void)
{
}
CGameOverState::~CGameOverState(void)
{
}
CGameOverState* CGameOverState::GetInstance(void)
{
	static CGameOverState instance;
	return &instance;
}
void CGameOverState::Enter(void)
{
	// Load texture
	m_nCursorPosition = 0;
	m_nBackgroundID = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/AlphaBG.png");;
	m_pGS = CGame::GetInstance()->GetGameStates();
}
bool CGameOverState::Input(void)
{
		if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_UP))
	{
		if(--m_nCursorPosition < 0)
			m_nCursorPosition = 1;
	}
	else if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_DOWN))
	{
		if(++m_nCursorPosition > 1)
			m_nCursorPosition = 0;
	}
	else if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_RETURN))
	{
		switch(m_nCursorPosition)
		{
		case 0:
			CEventSystem::GetInstance()->ClearEvents();
			CGamePlayState::GetInstance()->UnloadLevel();
			CSGD_DirectInput::GetInstance()->ClearInput();
			//CGamePlayState::GetInstance()->SetLevelBegun(false);

			// Replenish Ammo
			for(int i = 0; i < CPlayer::GetInstance()->GetNumWeapons(); i++)
				CPlayer::GetInstance()->GetWeapon(i)->SetAmmo(CPlayer::GetInstance()->GetWeapon(i)->GetMaxAmmo());

			CPlayer::GetInstance()->SetHealth(CPlayer::GetInstance()->GetMaxHealth());

			CGamePlayState::GetInstance()->LoadLevelHelper();
			CGamePlayState::GetInstance()->SetDead(false);
			while(CGame::GetInstance()->GetGameStates()->size() != 1)
				CGame::GetInstance()->RemoveTopState();
			break;
		case 1:
			CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
			break;
		}
	}	
	return true;

	//return true;
}
void CGameOverState::Update(float fElapsedTime)
{
	//(*m_pGS)[m_pGS->size()-2]->Update(fElapsedTime);
	
}
void CGameOverState::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw( m_nBackgroundID, 0, 0 );
	CBitmapFont::GetInstance()->Draw("You Have Died!", 50, 100, 2.0f, -1, false );

	CBitmapFont::GetInstance()->Draw("Continue?", 96, 250, 1.0f, -1, (m_nCursorPosition == 0)?true:false );
	CBitmapFont::GetInstance()->Draw("Exit", 176, 300, 1.0f, -1, (m_nCursorPosition == 1)?true:false );
}
void CGameOverState::Exit(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBackgroundID);
}