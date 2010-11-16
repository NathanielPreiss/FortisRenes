/**
 * 
 * Description:
 * The animation manager will be able to hold sheets of animations for the game objects.
 * 
 * Stipulations:
 * The animation manager is a singleton so only one instance of the animation manager can be created and must be manually deleted.
 * 
 * Interface:
 * The animation manager will contain functions to load new animations and remove old ones.
 */
#pragma once

#include <vector>
using std::vector;
#include <string>
using std::string;
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "tSheet.h"
#include "tAnimation.h"
#include "tFrame.h"
//#include "tAnimationInstance.h"
struct tAnimationInstance;

class CAnimationManager
{

	CSGD_TextureManager* m_pTM;
	/**
	 * All the sheets for animations
	 */
	vector<tSheet*> m_vSheets;
	/**
	 * static member instance of the animation manager
	 */
	static CAnimationManager* m_pAnimationInstance;

	CAnimationManager(void);
	~CAnimationManager(void);
	CAnimationManager( const CAnimationManager& );
	CAnimationManager& operator=( const CAnimationManager& );

public:
	
	tAnimationInstance* LoadAnimation(const char* szFilePath);

	void UnloadAnimation(tAnimationInstance* instance);



	static CAnimationManager* GetInstance(void);

	static void DeleteInstance(void);


};

