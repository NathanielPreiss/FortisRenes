//////////////////////////////////////////////////////////////
// File: "CShopState.h"
//
// Date Edited: 10/30/2010
//
// Purpose:
//////////////////////////////////////////////////////////////

#ifndef CSHOPSTATE_H_
#define CSHOPSTATE_H_

#include "IGameState.h"

class CShopState : public IGameState
{
private:
	int		m_nBackgroundID;
	int		m_nSelectionBoxID;

	int		m_nBuySelection;
	int		m_nSellSelection;

	RECT m_MouseRECT;
	RECT m_BuyRECT;
	RECT m_SellRECT;
	RECT m_ExitRECT;

	vector<RECT*> m_vBuyList;
	vector<RECT*> m_vSellList;

	CShopState(void);
	~CShopState(void);

public:
	static CShopState* GetInstance(void);

	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);

};

#endif