//////////////////////////////////////////////////////////////////////////////
// File: "IGameState.h"
//
// Date Edited: 10/14/2010
//
// Purpose: Provide all states with a base class to derive from so that the 
//			state machine will work properly in all states of the game
//
//////////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef	IGAMESTATE_H_
#define	IGAMESTATE_H_

// Including these headers will allow all states in the 
// game to use the DirectX wrappers and have access to the
// singleton bitmap font the game uses
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "DirectX Wrappers/CSGD_WaveManager.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"
#include "DirectX Wrappers/CSGD_DirectInput.h"

#include "CBitmapFont.h"

//////////////////////////////////////////////////////////////////////////////
//	Class: IGameState
//
//	Notes: Pure virtual, all states are derived from this class
//////////////////////////////////////////////////////////////////////////////
class IGameState
{
protected:
	IGameState(void){}

	virtual ~IGameState(void){}
public:


	virtual void Enter(void) = 0; 
	virtual bool Input(void) = 0; 
	virtual void Update(float) = 0;
	virtual void Render(void) = 0; 
	virtual void Exit(void) = 0; 
};
#endif