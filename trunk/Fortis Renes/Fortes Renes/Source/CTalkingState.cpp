///////////////////////////////////////////////////
// File: "CAttractState.cpp"
//
// Date Edited: 11/3/2010
//
// Purpose: Fill functions that are declared in
//			class header
//////////////////////////////////////////////////

#include "CTalkingState.h"
#include "DirectX Wrappers/CSGD_WaveManager.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "CGame.h"
#include "CDialogueManager.h"
#include "CGamePlayState.h"

CTalkingState::CTalkingState(void)
{
}
CTalkingState::~CTalkingState(void)
{
}
CTalkingState* CTalkingState::GetInstance(void)
{
	static CTalkingState instance;
	return &instance;
}
void CTalkingState::Enter(void)
{
	// Load texture
	m_nBackgroundID = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/TalkingStateBG.png");
	m_pGS = CGamePlayState::GetInstance();
}
bool CTalkingState::Input(void)
{
	if(CSGD_DirectInput::GetInstance()->CheckBufferedKeysEx())
	{
		CDialogueManager::GetInstance()->NextSentence();
		CSGD_DirectInput::GetInstance()->ClearInput();
	}

	return true;
}
void CTalkingState::Update(float fElapsedTime)
{
	m_pGS->Update(fElapsedTime);
}
void CTalkingState::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw( m_nBackgroundID, 0, 0 );
	CDialogueManager::GetInstance()->Render();
}
void CTalkingState::Exit(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBackgroundID);
}