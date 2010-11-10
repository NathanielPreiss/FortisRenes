//////////////////////////////////////////////////////////////
// File: "CTalkingState.h"
//
// Date Edited: 11/3/2010
//
// Purpose:
//////////////////////////////////////////////////////////////

#ifndef CTALKINGSTATE_H_
#define CTALKINGSTATE_H_

#include "IGameState.h"

class CTalkingState : public IGameState
{
private:
	int		m_nBackgroundID;
	int		m_nPortraitID;

	IGameState* m_pGS;

	CTalkingState(void);
	~CTalkingState(void);

public:
	static CTalkingState* GetInstance(void);

	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);

};

#endif