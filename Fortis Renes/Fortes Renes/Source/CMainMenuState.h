//////////////////////////////////////////////////////////////////////////////
// File: "CMainMenuState.h"
//
// Date Edited: 10/21/2010 
//
// Purpose: Main menu allowing the player to select several options to proceed
//			including Start New Game, Load Game, Options, Exit Game
//
// TODO: Possibly Add in a Horde/Zombie Mode as another game type
//
//////////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef CMAINMENUSTATE_H_
#define CMAINMENUSTATE_H_

// Nessisary includes
#include "IGameState.h"

//////////////////////////////////////////////////////////////////////////////
//	Class: CMainMenuState
//
//	Notes: State class that allows player to procede to gameplay, change options,
//         or exit the application completely
//////////////////////////////////////////////////////////////////////////////
class CMainMenuState : public IGameState
{
private:
	
	// Currently selected option
	int m_nCurrSelected;
	// Time since last keypress
	float m_fAwayTimer;
	// Background Image ID
	int m_nBackgroundID;
	// Background Music ID
	int m_nBGM_ID;
	// SFX ID
	int m_nSFX_ID;

	// Constructor
	CMainMenuState(void);
	// Destructor
	~CMainMenuState(void);

	// Load previous game settings
	void LoadSettings(void);

public:
	// Gets pointer to the singleton
	static CMainMenuState* GetInstance(void);

	// Entering the state
	void Enter(void);

	// Main game loop functions
	///////////////////////////
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	///////////////////////////

	// Exiting the state
	void Exit(void);	

	// Get the 
	int GetSFXID(void) { return m_nSFX_ID; }
	int GetBGMID(void) { return m_nBGM_ID; }

};
#endif