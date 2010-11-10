///////////////////////////////////////////////////
// File: "CAttractState.cpp"
//
// Date Edited: 11/3/2010
//
// Purpose: Fill functions that are declared in
//			class header
//////////////////////////////////////////////////

#include "CAttractState.h"
#include "DirectX Wrappers/CSGD_WaveManager.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "CGame.h"

CAttractState::CAttractState(void)
{
}
CAttractState::~CAttractState(void)
{
}
CAttractState* CAttractState::GetInstance(void)
{
	static CAttractState instance;
	return &instance;
}
void CAttractState::Enter(void)
{
	// Load texture
	m_nBackgroundID = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/CreditStateBG.jpg");
}
bool CAttractState::Input(void)
{
	if(CSGD_DirectInput::GetInstance()->CheckBufferedKeysEx())
			CGame::GetInstance()->RemoveTopState();

	return true;
}
void CAttractState::Update(float fElapsedTime)
{
}
void CAttractState::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw( m_nBackgroundID, 0, 0 );
}
void CAttractState::Exit(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBackgroundID);
}