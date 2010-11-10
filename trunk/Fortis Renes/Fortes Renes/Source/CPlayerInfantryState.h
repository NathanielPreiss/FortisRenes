//////////////////////////////////////////////////////////////////////////////
// File: "CPlayerInfantryState.h"
//
// Date Edited: 10/21/2010
//
// Purpose: 
//
//////////////////////////////////////////////////////////////////////////////

#ifndef CPLAYERINFANTRYSTATE_H_
#define CPLAYERINFANTRYSTATE_H_

// Nessisary headers
#include "IPlayerState.h"
#include "CPlayer.h"
//////////////////////////////////////////////////////////////////////////////
//	Class: CPlayerInfantryState
//	
//	Notes: 
//////////////////////////////////////////////////////////////////////////////
class CPlayerInfantryState : public IPlayerState
{
private:
	CPlayer* m_pPlayer;
	int		 m_nHudID;

	CPlayerInfantryState(void);
	~CPlayerInfantryState(void);

public:
	static CPlayerInfantryState* GetInstance(void);	
	CPlayer* GetPlayer() { return m_pPlayer; }
	
	void Enter();
	void Update(float fElapsedTime);
	void Render(float fCamPosX, float fCamPosY);

};
#endif