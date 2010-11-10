///////////////////////////////////////////////////
// File: "COpeningCinematicState.cpp"
//
// Date Edited: 11/2/2010
//
// Purpose: Fill functions that are declared in
//			class header
//////////////////////////////////////////////////

#include "COpeningCinematicState.h"
#include "DirectX Wrappers/CSGD_WaveManager.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "CGamePlayState.h"
#include "CGame.h"

COpeningCinematicState::COpeningCinematicState(void)
{
	m_nImageOne = 0;
	m_nImageTwo = 0;
	m_nImageThree = 0;
	m_nImageFour = 0;
	m_fFrameTimer = 0.0f;
}
COpeningCinematicState::~COpeningCinematicState(void)
{
}
COpeningCinematicState* COpeningCinematicState::GetInstance(void)
{
	static COpeningCinematicState instance;
	return &instance;
}
void COpeningCinematicState::Enter(void)
{
	// Load texture
	m_nImageOne = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/OpeningCinematic1.png");
	m_nImageTwo = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/OpeningCinematic2.png");
	m_nImageThree = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/OpeningCinematic3.png");
	m_nImageFour = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/OpeningCinematic4.png");

	m_cCurrFrame = 1;
	m_fFrameTimer = 0.0f;
}
bool COpeningCinematicState::Input(void)
{
	if(CSGD_DirectInput::GetInstance()->CheckBufferedKeysEx())
	{
		m_cCurrFrame++;
		m_fFrameTimer = 0.0f;
	}

	return true;
}
void COpeningCinematicState::Update(float fElapsedTime)
{
	m_fFrameTimer += fElapsedTime;
	if(m_fFrameTimer >= 10.0f)
	{
		m_cCurrFrame++;
		m_fFrameTimer = 0.0f;
	}
	if(m_cCurrFrame == 5)
		CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
}
void COpeningCinematicState::Render(void)
{
	switch(m_cCurrFrame)
	{
	case 1:
		CSGD_TextureManager::GetInstance()->Draw( m_nImageOne, 0, 0 );
		break;
	case 2:
		CSGD_TextureManager::GetInstance()->Draw( m_nImageTwo, 0, 0 );
		break;
	case 3:
		CSGD_TextureManager::GetInstance()->Draw( m_nImageThree, 0, 0 );
		break;
	case 4:
		CSGD_TextureManager::GetInstance()->Draw( m_nImageFour, 0, 0 );
		break;
	}
}
void COpeningCinematicState::Exit(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nImageOne);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nImageTwo);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nImageThree);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nImageFour);
}