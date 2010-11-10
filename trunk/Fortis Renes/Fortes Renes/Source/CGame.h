#ifndef	_CGAME_H_
#define _CGAME_H_

//SGD Wrappers

#include "DirectX Wrappers/CSGD_Direct3D.h"
#include "DirectX Wrappers/CSGD_DirectSound.h"
#include "DirectX Wrappers/CSGD_DirectInput.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "DirectX Wrappers/CSGD_WaveManager.h"
#include "CMessageSystem.h"
#include "CEventSystem.h"
#include "IGameState.h"
#include "CMessages.h"
#include "IListener.h"

class CGame : public IListener
{
private:

	//Singletons:
	CSGD_Direct3D*			m_pD3D;
	CSGD_DirectSound*		m_pDS;
	CSGD_DirectInput*		m_pDI;
	CSGD_TextureManager*	m_pTM;
	CSGD_WaveManager*		m_pWM;
	CMessageSystem*			m_pMS;
	CEventSystem*			m_pES;

	vector<IGameState*>		m_pGS;

	//	Asset IDs
	int						m_nImageID;
	int						m_nSoundID;

	int						m_nPanning;
	int						m_nBGMVolume;
	int						m_nSFXVolume;

	DWORD					m_dwTimeStamp;
	DWORD					m_dwPreviousTime;
	float					m_fElapsedTime;
	float					m_fGameTime;

	//	Proper Singleton:
	//	Constructor
	CGame(void);
	//	Trilogy of Evil
	//		copy constructor
	CGame( const CGame&);
	//		assignment operator
	CGame& operator=(const CGame&);
	//		destructor
	~CGame(void);

	// Exit out of all states
	void ClearAllStates(void);

	//Utility function
	bool Input(void);
	void Update(void);
	void Render(void);

public:
	// Handle Event function for IListener
	void HandleEvent(CEvent* pEvent);
	//	Singleton accessor
	static CGame* GetInstance(void);
	//	3 steps a game uses in its lifetime
	//		Initialization
	void Initialize( HWND hWnd, HINSTANCE hInstance, int nScreenWidth, int nScreenHeight, bool bIsWindowed );
	//		Execution
	bool Main(void);
	//		Cleanup
	void Shutdown(void);
	void ChangeState( IGameState* newState );
	void AddState( IGameState* newState );
	void RemoveTopState( void );

	int GetBGMVolume(void) { return m_nBGMVolume; }
	int GetSFXVolume(void) { return m_nSFXVolume; }
	int GetPanning(void) { return m_nPanning; }
	vector<IGameState*>* GetGameStates(void) { return &m_pGS; }

	void SetBGMVolume( int nBGMVolume );
	void SetSFXVolume( int nSFXVolume );
	void SetPanning( int nPanning );

	static void MessageProc( CBaseMessage* pMsg );

};

#endif