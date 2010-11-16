///////////////////////////////////////////////////
// File: "CHowToPlayState.cpp"
//
// Date Edited: 10/14/2010
//
// Purpose: Fill functions that are declared in
//			class header
//////////////////////////////////////////////////

#include "CHowToPlayState.h"
#include "DirectX Wrappers/CSGD_WaveManager.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "CGame.h"
#include "CBitmapFont.h"

CHowToPlayState::CHowToPlayState(void)
{
	m_nBackgroundID = 0;
}
CHowToPlayState::~CHowToPlayState(void)
{
}
CHowToPlayState* CHowToPlayState::GetInstance(void)
{
	static CHowToPlayState instance;
	return &instance;
}
void CHowToPlayState::Enter(void)
{
	// Load texture
	m_nBackgroundID = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/IntroStateBG.bmp");
}
bool CHowToPlayState::Input(void)
{
	if(CSGD_DirectInput::GetInstance()->CheckBufferedKeysEx())
			CGame::GetInstance()->RemoveTopState();

	return true;
}
void CHowToPlayState::Update(float fElapsedTime)
{
}
void CHowToPlayState::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw( m_nBackgroundID, 0, 0 );
	CBitmapFont::GetInstance()->Draw("Movement: W A S D",325,100,0.75f);
	CBitmapFont::GetInstance()->Draw("Switch Weapons: Up Down Arrow",150,25,0.75f);
	CBitmapFont::GetInstance()->Draw("                Mouse Scroll Wheel", 150, 50, 0.75f);
	CBitmapFont::GetInstance()->Draw("Shoot: Left Click",350,150,0.75f);
	CBitmapFont::GetInstance()->Draw("Talk: Enter",425,200,0.75f);
}
void CHowToPlayState::Exit(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBackgroundID);
}