//////////////////////////////////////////////////////////////
// File: "CGameOverState.h"
//
// Date Edited: 11/3/2010
//
// Purpose:
//////////////////////////////////////////////////////////////

#ifndef CGAMEOVERSTATE_H_
#define CGAMEOVERSTATE_H_

#include "IGameState.h"

class CGameOverState : public IGameState
{
private:
	int		m_nBackgroundID;
	int				m_nCursorPosition;
	//int		m_nPortraitID;

	vector<IGameState*>* m_pGS;

	CGameOverState(void);
	~CGameOverState(void);

public:
	static CGameOverState* GetInstance(void);

	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);

};

#endif