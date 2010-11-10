//////////////////////////////////////////////////////////////
// File: "CCrediState.h"
//
// Date Edited: 10/14/2010
//
// Purpose:
//////////////////////////////////////////////////////////////

#ifndef CCREDITSTATE_H_
#define CCREDITSTATE_H_

#include <vector>
using std::vector;

#include "IGameState.h"

class CCreditState : public IGameState
{
private:
	int		m_nBackgroundID;
	float	m_fScrollPosition;

	vector<char*> m_vCredits;

	CCreditState(void);
	~CCreditState(void);

	void LoadCredits(void);
	void UnloadCredits(void);

public:
	static CCreditState* GetInstance(void);

	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);

};

#endif