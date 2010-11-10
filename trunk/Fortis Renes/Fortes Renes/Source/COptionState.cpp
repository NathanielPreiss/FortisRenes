//////////////////////////////////////////////////////////////
// File: "COptionState.h"
//
// Date Edited: 10/14/2010
//
// Purpose:
//////////////////////////////////////////////////////////////

#include "COptionState.h"
#include "CMainMenuState.h"
#include "CGamePlayState.h"
#include "DirectX Wrappers/CSGD_WaveManager.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "CGame.h"
#include <stdio.h>
#include "Tinyxml/tinyxml.h"

COptionState::COptionState(void)
{
	m_nBGImageID		= 0;
	m_nCursorPosition	= 0;	
}

COptionState::~COptionState(void)
{
}
COptionState* COptionState::GetInstance(void)
{
	static COptionState instance;
	return &instance;
}

void COptionState::Enter(void)
{
	m_nBGImageID = CSGD_TextureManager::GetInstance()->LoadTexture( "Resource/Graphics/OptionStateBG.jpg");
}

bool COptionState::Input(void)
{
	int x = CMainMenuState::GetInstance()->GetBGMID();
	int y = CGamePlayState::GetInstance()->GetBGMID();

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

	if( CSGD_DirectInput::GetInstance()->KeyDown( DIK_LEFTARROW ) )
	{
		switch( m_nCursorPosition )
		{
		case 0:
			CGame::GetInstance()->SetSFXVolume( CGame::GetInstance()->GetSFXVolume() - 1 );
			CSGD_WaveManager::GetInstance()->SetVolume( CMainMenuState::GetInstance()->GetSFXID(), CGame::GetInstance()->GetSFXVolume() );
			if(!CSGD_WaveManager::GetInstance()->IsWavePlaying(CMainMenuState::GetInstance()->GetSFXID()))
				CSGD_WaveManager::GetInstance()->Play( CMainMenuState::GetInstance()->GetSFXID() );
			break;

		case 1:
			CGame::GetInstance()->SetBGMVolume( CGame::GetInstance()->GetBGMVolume() - 1 );
			CSGD_WaveManager::GetInstance()->SetVolume( (x)?x:y, CGame::GetInstance()->GetBGMVolume() );
			break;

		case 2:
			CGame::GetInstance()->SetPanning( CGame::GetInstance()->GetPanning() - 2 );
			CSGD_WaveManager::GetInstance()->SetPan( (x)?x:y, CGame::GetInstance()->GetPanning() );
			CSGD_WaveManager::GetInstance()->SetPan( CMainMenuState::GetInstance()->GetSFXID(), CGame::GetInstance()->GetPanning() );
			break;
		}
	}
	else if( CSGD_DirectInput::GetInstance()->KeyDown( DIK_RIGHTARROW ) )
	{
		switch( m_nCursorPosition )
		{
		case 0:
			CGame::GetInstance()->SetSFXVolume( CGame::GetInstance()->GetSFXVolume() + 1 );
			CSGD_WaveManager::GetInstance()->SetVolume( CMainMenuState::GetInstance()->GetSFXID(), CGame::GetInstance()->GetSFXVolume() );
			if(!CSGD_WaveManager::GetInstance()->IsWavePlaying(CMainMenuState::GetInstance()->GetSFXID()))
				CSGD_WaveManager::GetInstance()->Play( CMainMenuState::GetInstance()->GetSFXID() );
			break;

		case 1:
			CGame::GetInstance()->SetBGMVolume( CGame::GetInstance()->GetBGMVolume() + 1 );
			CSGD_WaveManager::GetInstance()->SetVolume( (x)?x:y, CGame::GetInstance()->GetBGMVolume() );
			break;

		case 2:
			CGame::GetInstance()->SetPanning( CGame::GetInstance()->GetPanning() + 2 );
			CSGD_WaveManager::GetInstance()->SetPan( (x)?x:y, CGame::GetInstance()->GetPanning() );
			CSGD_WaveManager::GetInstance()->SetPan( CMainMenuState::GetInstance()->GetSFXID(), CGame::GetInstance()->GetPanning() );
			break;
		}
	}

	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_RETURN ) )
		if( m_nCursorPosition == 3 )
			CGame::GetInstance()->RemoveTopState();

	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_ESCAPE ) )
		CGame::GetInstance()->RemoveTopState( );

	return true;
}

void COptionState::Update(float fElapsedTime)
{

}
void COptionState::SaveSettings(void)
{
	TiXmlDocument outDoc;

	TiXmlDeclaration* pDec = new TiXmlDeclaration("1.0", "utf-8", "yes");

	outDoc.LinkEndChild(pDec);

	TiXmlElement* pOutRoot = new TiXmlElement("settings");

	outDoc.LinkEndChild(pOutRoot);

	TiXmlElement* pSettings = new TiXmlElement("sound");
	
	pSettings->SetAttribute("music_vol", CGame::GetInstance()->GetBGMVolume());
	pSettings->SetAttribute("sfx_vol", CGame::GetInstance()->GetSFXVolume());
	pSettings->SetAttribute("pan", CGame::GetInstance()->GetPanning());

	pOutRoot->LinkEndChild(pSettings);

	outDoc.SaveFile("Resource/Data/Settings.xml");
}
void COptionState::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw( m_nBGImageID, 0, 0);

	char optionsString[100] = {0};
	CBitmapFont::GetInstance()->Draw("OPTIONS MENU", 300, 150, 0.75f );
	sprintf_s( optionsString, "CHANGE SFX VOLUME: %d", CGame::GetInstance()->GetSFXVolume() );
	
	switch(m_nCursorPosition)
	{
	case 0:
		CBitmapFont::GetInstance()->Draw( optionsString, 250, 250, 0.5f, -1, true);
		sprintf_s( optionsString, "CHANGE BGM VOLUME: %d", CGame::GetInstance()->GetBGMVolume() );
		CBitmapFont::GetInstance()->Draw( optionsString, 300, 270, 0.35f);
		sprintf_s( optionsString, "CHANGE PANNING: L %d R %d", int( 50 + (CGame::GetInstance()->GetPanning() * -0.5f ) ), 
																int( 50 + (CGame::GetInstance()->GetPanning() * 0.5f ) ) );
		CBitmapFont::GetInstance()->Draw( optionsString, 300, 290, 0.35f);
		CBitmapFont::GetInstance()->Draw( "BACK", 300, 310, 0.35f);
		break;
	case 1:
		CBitmapFont::GetInstance()->Draw( optionsString, 300, 250, 0.35f);
		sprintf_s( optionsString, "CHANGE BGM VOLUME: %d", CGame::GetInstance()->GetBGMVolume() );
		CBitmapFont::GetInstance()->Draw( optionsString, 250, 270, 0.5f, -1, true);
		sprintf_s( optionsString, "CHANGE PANNING: L %d R %d", int( 50 + (CGame::GetInstance()->GetPanning() * -0.5f ) ), 
																int( 50 + (CGame::GetInstance()->GetPanning() * 0.5f ) ) );
		CBitmapFont::GetInstance()->Draw( optionsString, 300, 290, 0.35f);
		CBitmapFont::GetInstance()->Draw( "BACK", 300, 310, 0.35f);
		break;
	case 2:
		CBitmapFont::GetInstance()->Draw( optionsString, 300, 250, 0.35f);
		sprintf_s( optionsString, "CHANGE BGM VOLUME: %d", CGame::GetInstance()->GetBGMVolume() );
		CBitmapFont::GetInstance()->Draw( optionsString, 300, 270, 0.35f);
		sprintf_s( optionsString, "CHANGE PANNING: L %d R %d", int( 50 + (CGame::GetInstance()->GetPanning() * -0.5f ) ), 
																int( 50 + (CGame::GetInstance()->GetPanning() * 0.5f ) ) );
		CBitmapFont::GetInstance()->Draw( optionsString, 225, 290, 0.5f, -1, true);
		CBitmapFont::GetInstance()->Draw( "BACK", 300, 310, 0.35f);
		break;
	case 3:
		CBitmapFont::GetInstance()->Draw( optionsString, 300, 250, 0.35f);
		sprintf_s( optionsString, "CHANGE BGM VOLUME: %d", CGame::GetInstance()->GetBGMVolume() );
		CBitmapFont::GetInstance()->Draw( optionsString, 300, 270, 0.35f);
		sprintf_s( optionsString, "CHANGE PANNING: L %d R %d", int( 50 + (CGame::GetInstance()->GetPanning() * -0.5f ) ), 
																int( 50 + (CGame::GetInstance()->GetPanning() * 0.5f ) ) );
		CBitmapFont::GetInstance()->Draw( optionsString, 300, 290, 0.35f);
		CBitmapFont::GetInstance()->Draw( "BACK", 270, 310, 0.5f, -1, true);
		break;
	}
}

void COptionState::Exit(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture( m_nBGImageID );
	SaveSettings();

}