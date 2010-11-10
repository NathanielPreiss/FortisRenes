//////////////////////////////////////////////////////////////
// File: "CResearchCenterState.h"
//
// Date Edited: 10/30/2010
//
// Purpose:
//////////////////////////////////////////////////////////////

#ifndef CRESEARCHCENTERSTATE_H_
#define CRESEARCHCENTERSTATE_H_

#include "IGameState.h"

class CResearchCenterState : public IGameState
{
private:
	int		m_nBackgroundID;
	int		m_nAlphaID;
	int		m_nSuccessfulSound;
	int		m_nFailSound;
	//int		m_nInvestAmount;

	RECT	m_MouseRECT;
	RECT	m_ReturnRECT;
	RECT	m_ArmorRECT;
	RECT	m_WeaponRECT;
	RECT	m_ConsumableRECT;

	

	CResearchCenterState(void);
	~CResearchCenterState(void);

public:
	static CResearchCenterState* GetInstance(void);

	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);

};

#endif