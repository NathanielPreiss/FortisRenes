///////////////////////////////////////////////////
// File: "CLoadState.cpp"
//
// Date Edited: 10/14/2010
//
// Purpose: Fill functions that are declared in
//			class header
//////////////////////////////////////////////////

#include "CMainMenuState.h"
#include "CLoadState.h"
#include "DirectX Wrappers/CSGD_WaveManager.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "CGamePlayState.h"
#include "CGame.h"
#include "CBitmapFont.h"

CLoadState::CLoadState(void)
{
	m_nBackgroundID = 0;
}
CLoadState::~CLoadState(void)
{
}
CLoadState* CLoadState::GetInstance(void)
{
	static CLoadState instance;
	return &instance;
}
void CLoadState::Enter(void)
{
	// Load texture
	m_nBackgroundID = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/HowToPlayStateBG.bmp");
	m_nNumberOfObjects = 0;
	m_nObjectsLoaded = 0;
	m_nPercentFinished = 0;
}
bool CLoadState::Input(void)
{
	return true;
}
void CLoadState::Update(float fElapsedTime)
{
	float per = (float)m_nObjectsLoaded / (float)m_nNumberOfObjects;
	m_nPercentFinished = (int)(per*100);
}
void CLoadState::Render(void)
{
	char buffer[100];
	CSGD_TextureManager::GetInstance()->Draw( m_nBackgroundID, 0, 0 );
	sprintf_s(buffer,100,"Loading %d",m_nPercentFinished);
	CBitmapFont::GetInstance()->Draw(buffer, (int)(0.33f * CSGD_Direct3D::GetInstance()->GetPresentParams()->BackBufferWidth), (int)(0.75f * CSGD_Direct3D::GetInstance()->GetPresentParams()->BackBufferHeight),1.0f);
}
void CLoadState::Exit(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBackgroundID);
	m_nNumberOfObjects = 0;
	m_nObjectsLoaded = 0;
	m_nPercentFinished = 0;
}