#ifndef CGAMEPLAYSUBSTATE_H_
#define CGAMEPLAYSUBSTATE_H_

#include "IGameState.h"
//#include "CShop.h"
//#include "CResearch.h"
#include "CStats.h"

class CGamePlaySubState : public IGameState
{
private:
	//CShop m_Shop;
	//CResearch m_Research;
	CStats m_Stats;

public:
	void LoadShop(void);
	void UnloadShop(void);
	void LoadResearch(void);
	void UnloadResearch(void);
	void LoadStats(void);
	void UnloadStats(void);

};
#endif