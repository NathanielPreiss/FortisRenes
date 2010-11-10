#include "CProgressCenterState.h"
#include "CGame.h"
#include "CMainMenuState.h"
#include "CPlayer.h"
CProgressCenterState::CProgressCenterState(void)
{
	m_pPlayer = CPlayer::GetInstance();
}
CProgressCenterState::~CProgressCenterState(void)
{

}
CProgressCenterState* CProgressCenterState::GetInstance(void)
{
	static CProgressCenterState instance;
	return &instance;
}
void CProgressCenterState::Enter(void)
{
	m_nBackgroundID = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/ProgressCenterStateBG.jpg");
	m_nSaveSound = CSGD_WaveManager::GetInstance()->LoadWave("Resource/Sounds/ProgressCenterStateSave.wav");
}
bool CProgressCenterState::Input(void)
{
	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_UPARROW ) )
	{
		m_nCursorPosition -= 1;
		if( m_nCursorPosition < 0 )
			m_nCursorPosition = 3;
	}
	else if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_DOWNARROW ) )
	{
		m_nCursorPosition += 1;
		if( m_nCursorPosition > 3 )
			m_nCursorPosition = 0;
	}
	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_RETURN ))
	{
		switch(m_nCursorPosition)
		{
		case 0:
			CGame::GetInstance()->RemoveTopState();
			break;
		case 1:
			m_pPlayer->SaveProfile();
			CSGD_WaveManager::GetInstance()->Play(m_nSaveSound);
			break;
		case 2:
			CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
			break;
		case 3:
			PostQuitMessage(0);
			return false;
		}
	}
	return true;
}
void CProgressCenterState::Update(float fElapsedTime)
{

}
void CProgressCenterState::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw(m_nBackgroundID, 0, 0);
	
	char BufferString[100] = {0};
	CBitmapFont::GetInstance()->Draw("PROGRESS CENTER", 300, 32, 0.5f );
	
	sprintf_s( BufferString, "Mzx Health: %d", m_pPlayer->GetMaxHealth() );
	CBitmapFont::GetInstance()->Draw(BufferString, 0, 64, 0.5f);

	sprintf_s( BufferString, "Attack Damage: %d", m_pPlayer->GetMaxHealth() );
	CBitmapFont::GetInstance()->Draw(BufferString, 0, 96, 0.5f);

	sprintf_s( BufferString, "Attack Speed: %d", m_pPlayer->GetMaxHealth() );
	CBitmapFont::GetInstance()->Draw(BufferString, 0, 128, 0.5f);

	sprintf_s( BufferString, "Stamina: %d", m_pPlayer->GetMaxHealth() );
	CBitmapFont::GetInstance()->Draw(BufferString, 0, 160, 0.5f);

	sprintf_s( BufferString, "Movement Speed: %d", m_pPlayer->GetMaxHealth() );
	CBitmapFont::GetInstance()->Draw(BufferString, 0, 192, 0.5f);

	sprintf_s( BufferString, "Armor: %d", m_pPlayer->GetMaxHealth() );
	CBitmapFont::GetInstance()->Draw(BufferString, 0, 224, 0.5f);

	sprintf_s( BufferString, "%d : 5 Areas Unlockd", m_pPlayer->GetMaxHealth() );
	CBitmapFont::GetInstance()->Draw(BufferString, 300, 64, 0.5f);

	sprintf_s( BufferString, "%d Reputation", m_pPlayer->GetMaxHealth() );
	CBitmapFont::GetInstance()->Draw(BufferString, 300, 96, 0.5f);

	CBitmapFont::GetInstance()->Draw("Items", 300, 128, 0.5f);

	CBitmapFont::GetInstance()->Draw("Exit", 300, 192, 0.5f, -1, (m_nCursorPosition == 0)?true:false );
	CBitmapFont::GetInstance()->Draw("Save Game", 300, 224, 0.5f, -1, (m_nCursorPosition == 1)?true:false );
	CBitmapFont::GetInstance()->Draw("Main Menu", 300, 256, 0.5f, -1, (m_nCursorPosition == 2)?true:false );
	CBitmapFont::GetInstance()->Draw("Exit Game", 300, 288, 0.5f, -1, (m_nCursorPosition == 3)?true:false );
}
void CProgressCenterState::Exit(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBackgroundID);
	CSGD_WaveManager::GetInstance()->UnloadWave(m_nSaveSound);
}