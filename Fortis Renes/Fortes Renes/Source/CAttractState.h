//////////////////////////////////////////////////////////////
// File: "CAttractState.h"
//
// Date Edited: 11/3/2010
//
// Purpose:
//////////////////////////////////////////////////////////////

#ifndef CATTRACTSTATE_H_
#define CATTRACTSTATE_H_

#include "IGameState.h"

class CAttractState : public IGameState
{
private:
	int		m_nBackgroundID;

	CAttractState(void);
	~CAttractState(void);

public:
	static CAttractState* GetInstance(void);

	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);

};

#endif