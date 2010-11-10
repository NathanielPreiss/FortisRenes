//////////////////////////////////////////////////////////////
// File: "COptionState.h"
//
// Date Edited: 10/14/2010
//
// Purpose:
//////////////////////////////////////////////////////////////

#ifndef COPTIONSTATE_H_
#define COPTIONSTATE_H_

#include "IGameState.h"
#include "CBitmapFont.h"

class COptionState : public IGameState
{
private:
	int		m_nBGImageID;
	int		m_nCursorPosition;

	void SaveSettings(void);

	COptionState(void);
	~COptionState(void);

public:
	static COptionState* GetInstance(void);

	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);

};
#endif