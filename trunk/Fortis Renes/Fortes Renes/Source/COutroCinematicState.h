//////////////////////////////////////////////////////////////
// File: "COutroCinematicState.h"
//
// Date Edited: 11/2/2010
//
// Purpose:
//////////////////////////////////////////////////////////////

#ifndef COUTROCINEMATICSTATE_H_
#define COUTROCINEMATICSTATE_H_

#include "IGameState.h"

class COutroCinematicState : public IGameState
{
private:
	int		m_nImageOne;
	int		m_nImageTwo;
	int		m_nImageThree;
	int		m_nImageFour;

	float	m_fFrameTimer;

	char	m_cCurrFrame;

	COutroCinematicState(void);
	~COutroCinematicState(void);

public:
	static COutroCinematicState* GetInstance(void);

	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);

};

#endif