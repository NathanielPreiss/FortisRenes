//////////////////////////////////////////////////////////////
// File: "CPausedState.h"
//
// Date Edited: 10/14/2010
//
// Purpose:
//////////////////////////////////////////////////////////////

#ifndef CGAMEPAUSEDSTATE_H_
#define CGAMEPAUSEDSTATE_H_

#include "IGameState.h"
#include "CBitmapFont.h"

class CGamePausedState : public IGameState
{
private:
	int				m_nCursorPosition;
	int				m_nShadow;

	CGamePausedState(void);
	~CGamePausedState(void);

public:
	static CGamePausedState* GetInstance(void);

	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);
};
#endif