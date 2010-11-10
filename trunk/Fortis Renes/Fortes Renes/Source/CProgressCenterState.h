//////////////////////////////////////////////////////////////
// File: "CProgressCenterState.h"
//
// Date Edited: 10/30/2010
//
// Purpose:
//////////////////////////////////////////////////////////////

#ifndef CPROGRESSCENTERSTATE_H_
#define CPROGRESSCENTERSTATE_H_

#include "IGameState.h"
class CPlayer;

class CProgressCenterState : public IGameState
{
private:
	int		m_nBackgroundID;
	int		m_nCursorPosition;
	int		m_nSaveSound;
	CPlayer* m_pPlayer;

	CProgressCenterState(void);
	~CProgressCenterState(void);

public:
	static CProgressCenterState* GetInstance(void);

	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);

};

#endif