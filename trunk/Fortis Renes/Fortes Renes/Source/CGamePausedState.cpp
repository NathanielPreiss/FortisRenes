//////////////////////////////////////////////////////////////////////////////
// File: "CGamePausedState.cpp"
//
// Date Edited: 10/26/2010
//
// Purpose: 
//
//////////////////////////////////////////////////////////////////////////////

// Nessisary header includes
#include "CGamePausedState.h"
#include "CGame.h"
#include "COptionState.h"
#include "CMainMenuState.h"


////////////////////////////////////////////////////////
// Function: CGamePausedState (Constructor)
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
CGamePausedState::CGamePausedState(void)
{

}
////////////////////////////////////////////////////////
// Function: ~CGamePausedState (Destructor)
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
CGamePausedState::~CGamePausedState(void)
{

}
////////////////////////////////////////////////////////
// Function: GetInstance
// Paramaters: void
// Returns: CGamePausedState* instance - Singleton instance of class
////////////////////////////////////////////////////////
CGamePausedState* CGamePausedState::GetInstance(void)
{
	static CGamePausedState instance;
	return &instance;
}
////////////////////////////////////////////////////////
// Function: Enter
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
void CGamePausedState::Enter(void)
{
	m_nCursorPosition = 0;
	m_nShadow = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/AlphaBG.png");
}
////////////////////////////////////////////////////////
// Function: Input
// Paramaters: void
// Returns: bool 
////////////////////////////////////////////////////////
bool CGamePausedState::Input(void)
{
	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_UP))
	{
		if(--m_nCursorPosition < 0)
			m_nCursorPosition = 3;
	}
	else if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_DOWN))
	{
		if(++m_nCursorPosition > 3)
			m_nCursorPosition = 0;
	}
	else if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_RETURN))
	{
		switch(m_nCursorPosition)
		{
		case 0:
			CGame::GetInstance()->RemoveTopState();
			break;
		case 1:
			CGame::GetInstance()->AddState(COptionState::GetInstance());
			break;
		case 2:
			CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
			break;
		case 3:
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
void CGamePausedState::Update(float fElapsedTime)
{

}
////////////////////////////////////////////////////////
// Function: Render
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
void CGamePausedState::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw(m_nShadow, 0, 0);
	CBitmapFont::GetInstance()->Draw("Return To Game", 96, 200, 1.0f, -1, (m_nCursorPosition == 0)?true:false );
	CBitmapFont::GetInstance()->Draw("Options", 208, 250, 1.0f, -1, (m_nCursorPosition == 1)?true:false );
	CBitmapFont::GetInstance()->Draw("Main Menu", 176, 300, 1.0f, -1, (m_nCursorPosition == 2)?true:false );
	CBitmapFont::GetInstance()->Draw("Exit Game", 176, 350, 1.0f, -1, (m_nCursorPosition == 3)?true:false );
}
////////////////////////////////////////////////////////
// Function: Exit
// Paramaters: void
// Returns: void
////////////////////////////////////////////////////////
void CGamePausedState::Exit(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nShadow);
}