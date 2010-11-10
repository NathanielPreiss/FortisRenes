//////////////////////////////////////////////////////////////////////////////
// File: "CMainMenuState.cpp"
//
// Date Edited: 10/14/2010
//
// Purpose: Fills out the state class functions in "CMainMenuState.h"
//
//////////////////////////////////////////////////////////////////////////////

// Nessisary header includes
#include "CGame.h"
#include "CPlayer.h"
#include "CMainMenuState.h"
#include "CGamePlayState.h"
#include "CCreditState.h"
#include "CHowToPlayState.h"
#include "COptionState.h"
#include "CAttractState.h"
#include "COpeningCinematicState.h"
#include "Tinyxml/tinyxml.h"

////////////////////////////////////////////////////////
// Function: CMainMenuState (Constructor)
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
CMainMenuState::CMainMenuState(void)
{
	m_nBackgroundID = 0;
	m_nCurrSelected = 0;
}

////////////////////////////////////////////////////////
// Function: ~CMainMenuState (Destructor)
// Paramaters: void 
// Returns: void
////////////////////////////////////////////////////////
CMainMenuState::~CMainMenuState(void)
{
}

////////////////////////////////////////////////////////
// Function: Enter
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
void CMainMenuState::Enter(void)
{
	m_nBackgroundID = 0;
	m_nBackgroundID = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/IntroStateBG.bmp");
	m_nCurrSelected = 0;
	m_fAwayTimer = 0.0f;

	m_nBGM_ID = CSGD_WaveManager::GetInstance()->LoadWave( "Resource/Sounds/MainMenuStateBG.wav" );
	m_nSFX_ID = CSGD_WaveManager::GetInstance()->LoadWave( "Resource/Sounds/Gunshot.wav" );
	LoadSettings();
	CSGD_WaveManager::GetInstance()->SetPan( m_nBGM_ID, CGame::GetInstance()->GetPanning() );
	CSGD_WaveManager::GetInstance()->SetPan(m_nSFX_ID, CGame::GetInstance()->GetPanning() );
	CSGD_WaveManager::GetInstance()->SetVolume( m_nBGM_ID, CGame::GetInstance()->GetBGMVolume() );
	CSGD_WaveManager::GetInstance()->SetVolume( m_nSFX_ID, CGame::GetInstance()->GetSFXVolume() );
	CSGD_WaveManager::GetInstance()->Play( m_nBGM_ID, DSBPLAY_LOOPING );
}

////////////////////////////////////////////////////////
// Function: LoadSettings
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
void CMainMenuState::LoadSettings(void)
{
	TiXmlDocument doc;

	if(doc.LoadFile("Resource/Data/Settings.xml") == false)
		return;
	
	TiXmlElement* pRoot = doc.RootElement();

	if(!pRoot)
		return;

	TiXmlElement* pSettings = pRoot->FirstChildElement("sound");

	if(pSettings)
	{
		int temp = 0;
		pSettings->Attribute("music_vol", &temp);
		CSGD_WaveManager::GetInstance()->SetVolume( m_nBGM_ID, temp );
		CGame::GetInstance()->SetBGMVolume( temp );
		
		pSettings->Attribute("sfx_vol", &temp);
		CSGD_WaveManager::GetInstance()->SetVolume( m_nSFX_ID, temp );		
		CGame::GetInstance()->SetSFXVolume( temp );
	
		pSettings->Attribute("pan", &temp);
		CSGD_WaveManager::GetInstance()->SetPan( m_nBGM_ID, temp );
		CSGD_WaveManager::GetInstance()->SetPan( m_nSFX_ID, temp );
		CGame::GetInstance()->SetPanning( temp );

	}
}

////////////////////////////////////////////////////////
// Function: Input
// Paramaters: void
// Returns: bool - If false you are exiting
////////////////////////////////////////////////////////
bool CMainMenuState::Input(void)
{
	if( CSGD_DirectInput::GetInstance()->CheckKeys() )
		m_fAwayTimer = 0.0f;

	if( CSGD_DirectInput::GetInstance()->KeyPressed(DIK_UPARROW))
	{
		m_fAwayTimer = 0.0f;
		m_nCurrSelected--;
		if( m_nCurrSelected < 0 )
			m_nCurrSelected = 5;
	}
	else if( CSGD_DirectInput::GetInstance()->KeyPressed(DIK_DOWNARROW))
	{
		m_fAwayTimer = 0.0f;
		m_nCurrSelected++;
		if( m_nCurrSelected > 5 )
			m_nCurrSelected = 0;
	}

	if( CSGD_DirectInput::GetInstance()->KeyPressed(DIK_RETURN) )
	{
		m_fAwayTimer = 0.0f;
		switch(m_nCurrSelected)
		{
		case 0:
			CPlayer::GetInstance()->NewPlayer();
			CGame::GetInstance()->ChangeState( COpeningCinematicState::GetInstance() );
			break;
		case 1:
			// Need to put the functionallity of this into the load
			// funtion so that it will call only one function
			CPlayer::GetInstance()->NewPlayer();
			CPlayer::GetInstance()->LoadProfile();
			CGame::GetInstance()->ChangeState( CGamePlayState::GetInstance() );
			break;
		case 2:
			CGame::GetInstance()->AddState( CHowToPlayState::GetInstance() );
			break;
		case 3:
			CGame::GetInstance()->AddState( CCreditState::GetInstance() );
			break;
		case 4:
			CGame::GetInstance()->AddState( COptionState::GetInstance() );
			break;
		case 5:
			return false;

		}
	}
	return true;
}

////////////////////////////////////////////////////////
// Function: Update
// Paramaters: float fElapsedTime - Time since last update
// Returns: void
////////////////////////////////////////////////////////
void CMainMenuState::Update(float fElapsedTime)
{
	m_fAwayTimer += fElapsedTime;
	if( m_fAwayTimer > 10.0f)
	{
		CGame::GetInstance()->AddState(CAttractState::GetInstance());
		m_fAwayTimer = 0.0f;
	}
}

////////////////////////////////////////////////////////
// Function: Render
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
void CMainMenuState::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw( m_nBackgroundID, 0, 0);

	CBitmapFont::GetInstance()->Draw("New Game", 0, 0, 1.0f, -1, (m_nCurrSelected == 0)?true:false);
	CBitmapFont::GetInstance()->Draw("Load Game", 0, 50, 1.0f, -1, (m_nCurrSelected == 1)?true:false);
	CBitmapFont::GetInstance()->Draw("How To Play", 0, 100, 1.0f, -1, (m_nCurrSelected == 2)?true:false);
	CBitmapFont::GetInstance()->Draw("Credits", 0, 150, 1.0f, -1, (m_nCurrSelected == 3)?true:false);
	CBitmapFont::GetInstance()->Draw("Options", 0, 200, 1.0f, -1, (m_nCurrSelected == 4)?true:false);
	CBitmapFont::GetInstance()->Draw("Exit Game", 0, 250, 1.0f, -1, (m_nCurrSelected == 5)?true:false);

}

////////////////////////////////////////////////////////
// Function: Exit
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
void CMainMenuState::Exit(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture( m_nBackgroundID );
	CSGD_WaveManager::GetInstance()->Stop(m_nBGM_ID);
	CSGD_WaveManager::GetInstance()->UnloadWave(m_nBGM_ID);
}

////////////////////////////////////////////////////////
// Function: GetInstance
// Paramaters: void
// Returns: CMainMenuState* instance - Pointer to the singleton
////////////////////////////////////////////////////////
CMainMenuState* CMainMenuState::GetInstance(void)
{
	static CMainMenuState instance;
	return &instance;
}