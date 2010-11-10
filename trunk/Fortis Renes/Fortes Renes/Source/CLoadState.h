////////////////////////////////////////////////////
// File: "CLoadState.h"
//
// Date Edited: 10/14/2010
//
// Purpose: 
////////////////////////////////////////////////////

#ifndef CLOADSTATE_H_
#define CLOADSTATE_H_

#include "IGameState.h"

class CLoadState : public IGameState
{
private:
	int		m_nBackgroundID;
	int		m_nNumberOfObjects;
	int		m_nObjectsLoaded;
	int		m_nPercentFinished;

	CLoadState(void);
	~CLoadState(void);

public:
	static CLoadState* GetInstance(void);

	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);

	int GetPercentFinished(void) { return m_nPercentFinished; }
	int GetNumObj(void) { return m_nNumberOfObjects; }
	int GetNumLoaded(void) { return m_nObjectsLoaded; }

	void SetNumObjects(int nNum) { m_nNumberOfObjects = nNum; }
	void SetNumLoaded(int nNum) { m_nObjectsLoaded = nNum; }

};
#endif