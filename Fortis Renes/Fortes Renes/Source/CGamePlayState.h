#ifndef CGAMEPLAYSTATE_H_
#define CGAMEPLAYSTATE_H_

#include <vector>
using std::vector;

#include "IGameState.h"
#include "CEmitter.h"
#include "CLightInfantry.h"
#include "IListener.h"

class CBase;
class CBoss1;
class CBoss2;
class CBoss3;
class CFinalBoss;

class CGamePlayState : public IGameState, public IListener
{
private:

	int m_nBGMID;
	int m_nCurrentLevel;
	vector<CEmitter*> m_vEmitter;

	bool m_bLevelBegun;
	bool m_bLevelEnd;
	bool m_bAllyRescue;
	bool m_bLevel1;
	bool m_bLevel2;
	bool m_bLevel3;
	bool m_bLevel4;
	bool m_bLevel4a;
	bool m_bLevel4b;
	bool m_bNextLevel;
	bool m_bDead;
	bool m_bRhinoCheat;

	CFinalBoss* FinalBoss;

	float m_fTimeBucket;
	float m_fHelicopterTimer;

	CGamePlayState(void);
	~CGamePlayState(void);

public:
	static CGamePlayState* GetInstance(void);

	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// LoadLevel
	//	-	Loads the information for the current level
	//	-	Takes in the const char* for the filename to be loaded
	//	-	Takes in a bool true for loading in xml default false for binary
	//
	// UnloadLevel
	//	-	Unloads the information and assets of the loaded level
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool LoadLevel(const char* filename, bool loadXML = false);
	void LoadLevelHelper();
	bool UnloadLevel(void);

	void SetDead(bool bDead) { m_bDead = bDead; }
	bool GetDead(void) { return m_bDead; }

	int GetBGMID(void)	{ return m_nBGMID; }
	CFinalBoss* GetFinalBoss() { return FinalBoss; }
	void PushEmitter(CEmitter* pEmitter) { m_vEmitter.push_back(pEmitter); }
	vector<CEmitter*> GetEmitter(void) { return m_vEmitter; }
	void HandleEvent( CEvent* pEvent );

};
#endif