//////////////////////////////////////////////////////////////////////////////
// File: "CIntroState.cpp"
//
// Date Edited: 10/21/2010
//
// Purpose: Fills out the state class functions in "CIntroState.h"
//
//////////////////////////////////////////////////////////////////////////////

// Nessisary header includes
#include "CGame.h"
#include "CIntroState.h"
#include "CMainMenuState.h"

////////////////////////////////////////////////////////
// Function: CIntroState (Constructor)
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
CIntroState::CIntroState(void)
{
	m_nBackgroundID = 0;
}

////////////////////////////////////////////////////////
// Function: ~CIntroState (Destructor)
// Paramaters: void 
// Returns: void
////////////////////////////////////////////////////////
CIntroState::~CIntroState(void)
{
}

////////////////////////////////////////////////////////
// Function: Enter
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
void CIntroState::Enter(void)
{
	m_nBackgroundID = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/IntroStateBG.bmp");
}

////////////////////////////////////////////////////////
// Function: Input
// Paramaters: void
// Returns: bool - If false you are exiting
////////////////////////////////////////////////////////
bool CIntroState::Input(void)
{
	if( CSGD_DirectInput::GetInstance()->CheckBufferedKeysEx() )
	{
		CGame::GetInstance()->RemoveTopState();
	}
	return true;
}

////////////////////////////////////////////////////////
// Function: Update
// Paramaters: float fElapsedTime - Time since last update
// Returns: void
////////////////////////////////////////////////////////
void CIntroState::Update(float fElapsedTime)
{
}

////////////////////////////////////////////////////////
// Function: Render
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
void CIntroState::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw( m_nBackgroundID, 0, 0);
	CBitmapFont::GetInstance()->Draw("Press Any Key To Continue", 220, 460, 0.5F, -1, true);
}

////////////////////////////////////////////////////////
// Function: Exit
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
void CIntroState::Exit(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture( m_nBackgroundID );
}

////////////////////////////////////////////////////////
// Function: GetInstance
// Paramaters: void
// Returns: CIntroState* instance - Pointer to the singleton
////////////////////////////////////////////////////////
CIntroState* CIntroState::GetInstance(void)
{
	static CIntroState instance;
	return &instance;
}