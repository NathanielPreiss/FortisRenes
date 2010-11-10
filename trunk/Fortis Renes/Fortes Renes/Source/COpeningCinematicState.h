//////////////////////////////////////////////////////////////
// File: "COpeningCinematicState.h"
//
// Date Edited: 11/2/2010
//
// Purpose:
//////////////////////////////////////////////////////////////

#ifndef COPENINGCINEMATICSTATE_H_
#define COPENINGCINEMATICSTATE_H_

#include "IGameState.h"

class COpeningCinematicState : public IGameState
{
private:
	int		m_nImageOne;
	int		m_nImageTwo;
	int		m_nImageThree;
	int		m_nImageFour;

	float	m_fFrameTimer;

	char	m_cCurrFrame;

	COpeningCinematicState(void);
	~COpeningCinematicState(void);

public:
	static COpeningCinematicState* GetInstance(void);

	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);

};

#endif