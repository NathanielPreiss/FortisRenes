//////////////////////////////////////////////////////////////////////////////
// File: "CIntroState.h"
//
// Date Edited: 10/12/2010 
//
// Purpose: Opening state of the game presenting an image of the game art
//
//////////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef CINTROSTATE_H_
#define CINTROSTATE_H_

// Nessisary includes
#include "IGameState.h"

//////////////////////////////////////////////////////////////////////////////
//	Class: CIntroState
//
//	Notes: State class that displays an opening image
//////////////////////////////////////////////////////////////////////////////
class CIntroState : public IGameState
{
private:
	
	// Background Image ID
	int m_nBackgroundID;

	// Constructor
	CIntroState(void);
	// Destructor
	~CIntroState(void);

public:
	// Gets pointer to the singleton
	static CIntroState* GetInstance(void);

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

};
#endif