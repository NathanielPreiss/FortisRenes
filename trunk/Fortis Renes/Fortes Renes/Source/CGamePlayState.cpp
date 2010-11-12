#include "CGamePlayState.h"
#include "CBase.h"
#include "CObjectManager.h"
#include "CCamera.h"
#include "CGame.h"
#include "CPlayer.h"
#include "CJeep.h"
#include "CTank.h"
#include "CEnemySquad.h"
#include "CBoss1.h"
#include "CBoss2.h"
#include "CBoss3.h"
#include "CFinalBoss.h"
#include "CParticle.h"
#include "CMainMenuState.h"
#include "CResearchCenterState.h"
#include "CShopState.h"
#include "CProgressCenterState.h"
#include "CGamePausedState.h"
#include "COutroCinematicState.h"
#include "CDialogueManager.h"
#include "CLoadState.h"
#include "CPlayerInfantryState.h"
#include "Tinyxml/tinyxml.h"
#include "CTalkingState.h"
#include <fstream>
#include <string>
using namespace std;


CGamePlayState::CGamePlayState(void)
{
}

CGamePlayState::~CGamePlayState(void)
{
}

void CGamePlayState::Enter(void)
{
	m_fTimeBucket = 0.0f;
	m_fHelicopterTimer = 10.0f;
	m_bLevelBegun = false;
	m_bLevelEnd = false;
	m_bAllyRescue = false;
	m_bNextLevel = false;
	m_bLevel1 = false;
	m_bLevel2 = false;
	m_bLevel3 = false;
	m_bLevel4 = false;
	m_bLevel4a = false;
	m_bLevel4b = false;
	CEmitter* pEmitter = new CEmitter();
	pEmitter->LoadEmitter("Resource/Graphics/last flame.bin");
	for(int i = 0; i < pEmitter->GetNumberOfParticles(); i++)
	{
		CParticle* pParticle = new CParticle();
		pEmitter->GetParticles()->push_back(pParticle);
	}

	m_vEmitter.push_back(pEmitter);

	//LoadLevel("Resource/Levels/ArtilleryLevel.bin");
	//LoadLevel("Resource/Levels/JeG_Level1.bin");
	//LoadLeveld("Resource/Levels/JeG_Level2.bin");
	//LoadLevel("Resource/Levels/JeG_Level4BossFight.bin");
	//LoadLevel("Resource/Levels/testtesttest.bin");
	LoadLevel("Resource/Levels/JeG_TutorialLevel.bin");
	//LoadLevel("Resource/Levels/JeG_RebelBase.bin");

	m_nBGMID = CSGD_WaveManager::GetInstance()->LoadWave("Resource/Sounds/GamePlayStateBG.wav");
	CSGD_WaveManager::GetInstance()->SetPan(m_nBGMID, CGame::GetInstance()->GetPanning() );
	CSGD_WaveManager::GetInstance()->SetVolume(m_nBGMID, CGame::GetInstance()->GetBGMVolume() );
	CSGD_WaveManager::GetInstance()->Play( m_nBGMID, DSBPLAY_LOOPING );
	

	CCamera::GetInstance()->UpdateCameraPos(CPlayer::GetInstance()->GetPosX(), CPlayer::GetInstance()->GetPosY());

	CEventSystem::GetInstance()->RegisterClient("begin.level",this);
	CEventSystem::GetInstance()->RegisterClient("continue.level",this);
	CEventSystem::GetInstance()->RegisterClient("end.level",this);
	CEventSystem::GetInstance()->RegisterClient("level.one",this);
	CEventSystem::GetInstance()->RegisterClient("level.two",this);
	CEventSystem::GetInstance()->RegisterClient("level.three",this);
	CEventSystem::GetInstance()->RegisterClient("spawn.helicopter",this);
	CEventSystem::GetInstance()->RegisterClient("ally.rescue",this);
	CEventSystem::GetInstance()->RegisterClient("seige.level",this);
	CEventSystem::GetInstance()->RegisterClient("enter.lobby",this);
	CEventSystem::GetInstance()->RegisterClient("leave.lobby",this);

}
bool CGamePlayState::Input(void)
{
	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_ESCAPE ) )
		CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
	else if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_P ) )
		CGame::GetInstance()->AddState(CGamePausedState::GetInstance());
	else if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_BACK ) )
		CGame::GetInstance()->ChangeState(COutroCinematicState::GetInstance());
	return true;
}

void CGamePlayState::LoadLevelHelper()
{
	switch(CPlayer::GetInstance()->GetProgress())
	{
	case 0:
		{
			LoadLevel("Resource/Levels/JeG_TutorialLevel.bin");
		}
		break;
	case 1:
		{
			LoadLevel("Resource/Levels/JeG_Level1.bin");
		}
		break;
	case 2:
		{
			LoadLevel("Resource/Levels/JeG_Level2.bin");
		}
		break;
	case 3:
		{
			LoadLevel("Resource/Levels/ArtilleryLevel.bin");
		}
		break;
	case 4:
		{
			LoadLevel("Resource/Levels/JeG_Level4Siege.bin");
		}
		break;
	case 5:
		{
			//LoadLevel("Resource/Levels/JeG_Level3.bin");
		}
		break;
	}
}

void CGamePlayState::Update(float fElapsedTime)
{
	m_fTimeBucket += fElapsedTime;

	if( m_bLevelEnd == true )
	{
		if( CPlayer::GetInstance()->GetProgress() > 4 )
		{
			CGame::GetInstance()->ChangeState(COutroCinematicState::GetInstance());
		}
		else
		{
			CMessageSystem::GetInstance()->ClearMessages();
			CEventSystem::GetInstance()->ClearEvents();
			CEnemySquad::GetInstance()->EmptySquad();
			UnloadLevel();
			CPlayer::GetInstance()->ChangeState(CPlayerInfantryState::GetInstance());
			LoadLevel("Resource/Levels/JeG_RebelBase.bin");

			m_bLevelEnd = false;
		}
	}

	if( m_bLevel1 == true )
	{
		CMessageSystem::GetInstance()->ClearMessages();
		CEventSystem::GetInstance()->ClearEvents();
		UnloadLevel();
		LoadLevel("Resource/Levels/JeG_Level1.bin");
		m_bLevel1 = false;

	}

	if( m_bLevel2 == true )
	{
		CMessageSystem::GetInstance()->ClearMessages();
		CEventSystem::GetInstance()->ClearEvents();
		UnloadLevel();
		LoadLevel("Resource/Levels/JeG_Level2.bin");
		m_bLevel2 = false;
	}

	if( m_bLevel3 == true )
	{
		CMessageSystem::GetInstance()->ClearMessages();
		CEventSystem::GetInstance()->ClearEvents();
		UnloadLevel();
		LoadLevel("Resource/Levels/ArtilleryLevel.bin");
		m_bLevel3 = false;
	}

	if( m_bLevel4 == true )
	{
		CMessageSystem::GetInstance()->ClearMessages();
		CEventSystem::GetInstance()->ClearEvents();
		UnloadLevel();
		LoadLevel("Resource/Levels/JeG_Level4Siege.bin");
		m_bLevel4 = false;
	}

	if( m_bLevel4a == true )
	{
		CMessageSystem::GetInstance()->ClearMessages();
		CEventSystem::GetInstance()->ClearEvents();
		UnloadLevel();
		LoadLevel("Resource/Levels/JeG_Level4Lobby.bin");
		m_bLevel4a = false;
	}

	if( m_bLevel4b == true )
	{
		CMessageSystem::GetInstance()->ClearMessages();
		CEventSystem::GetInstance()->ClearEvents();
		UnloadLevel();
		LoadLevel("Resource/Levels/JeG_Level4BossFight.bin");
		m_bLevel4b = false;
	}

	if( m_bNextLevel == true )
	{
		CMessageSystem::GetInstance()->ClearMessages();
		CEventSystem::GetInstance()->ClearEvents();
		UnloadLevel();
		LoadLevelHelper();
		m_bNextLevel = false;
	}

	if( CPlayer::GetInstance()->GetHealth() <= 0 )
	{
		CEventSystem::GetInstance()->ClearEvents();
		UnloadLevel();
		LoadLevelHelper();
	}

	CObjectManager::GetInstance()->UpdateObjects(fElapsedTime);

	for(unsigned int i = 0; i < m_vEmitter.size(); i++)
		m_vEmitter[i]->Update(fElapsedTime);

	CEnemySquad::GetInstance()->Update(fElapsedTime);
	CCamera::GetInstance()->Update(fElapsedTime);
}

void CGamePlayState::Render(void)
{
	CObjectManager::GetInstance()->RenderObjects();

	for(unsigned int i = 0; i< m_vEmitter.size(); i++)
	{
		for(int x = 0; x < m_vEmitter[i]->GetNumberOfParticles(); x++)
			m_vEmitter[i]->GetParticle(x)->Render();
	}
	if(m_bRhinoCheat)
	{
		CBitmapFont::GetInstance()->Draw("CHEAT ENABLED", 5, 5, 0.5f);
	}
}
void CGamePlayState::Exit(void)
{
	for(unsigned int i = 0; i < m_vEmitter.size(); i++)
	{
		for(int j = 0; j < m_vEmitter[i]->GetNumberOfParticles(); j++)
		{
			delete m_vEmitter[i]->GetParticle(j);
		}
		delete m_vEmitter[i];
	}	
	m_vEmitter.clear();

	CSGD_WaveManager::GetInstance()->UnloadWave(m_nBGMID);
	CPlayer::GetInstance()->SaveProfile();
	CPlayer::GetInstance()->ClosePlayer();
	UnloadLevel();
	CObjectManager::GetInstance()->DeleteInstance();

	CEventSystem::GetInstance()->UnregisterClient("begin.level",this);
	CEventSystem::GetInstance()->UnregisterClient("continue.level",this);
	CEventSystem::GetInstance()->UnregisterClient("end.level",this);
	CEventSystem::GetInstance()->UnregisterClient("level.one",this);
	CEventSystem::GetInstance()->UnregisterClient("level.two",this);
	CEventSystem::GetInstance()->UnregisterClient("level.three",this);
	CEventSystem::GetInstance()->UnregisterClient("spawn.helicopter",this);
	CEventSystem::GetInstance()->UnregisterClient("ally.rescue",this);
	CEventSystem::GetInstance()->UnregisterClient("seige.level",this);
	CEventSystem::GetInstance()->UnregisterClient("enter.lobby",this);
	CEventSystem::GetInstance()->UnregisterClient("leave.lobby",this);

	for(unsigned int i = 0; i < m_vEmitter.size(); i++)
	{
		for(int j = 0; j < m_vEmitter[i]->GetNumberOfParticles(); j++)
		{
			delete m_vEmitter[i]->GetParticle(j);
		}
		delete m_vEmitter[i];
	}	
	m_vEmitter.clear();

	CSGD_WaveManager::GetInstance()->UnloadWave(m_nBGMID);
	CPlayer::GetInstance()->SaveProfile();
	CPlayer::GetInstance()->ClosePlayer();
	CObjectManager::GetInstance()->RemoveAllObjects();
	CObjectManager::GetInstance()->DeleteInstance();

}

CGamePlayState* CGamePlayState::GetInstance(void)
{
	static CGamePlayState instance;
	return &instance;
}
// this new enum is a mirror of the editor, it's for the coming switch statement to correctly parse the objects for creation
enum EDITOR{ED_PLAYER, ED_LIGHT_INFANTRY, ED_MEDIUM_INFANTRY, ED_HEAVY_INFANTRY, ED_ENEMY_TANK, ED_ENEMY_JEEP, ED_FIRST_BOSS, ED_SECOND_BOSS, ED_THIRD_BOSS, ED_FOURTH_BOSS, ED_JEEP, ED_TANK, ED_FIRSTAID, ED_AMMO, ED_ADRENALINE, ED_RUBBLE, ED_TREE, ED_BUILDING, ED_BOMB, ED_RADIOTOWER, ED_HILL, ED_WALL, ED_REBEL, ED_HOSTAGE, ED_ENEMY_EMITTER, ED_GATE};

bool CGamePlayState::LoadLevel(const char* filename, bool loadXML)
{
	CGame::GetInstance()->AddState(CLoadState::GetInstance());
	// Make sure to unload any loaded level
	UnloadLevel();
	// buffers for reading in
	char strLength;
	char* buffer;

	// if loadXML is true, we'll load in the xml file.
	if( loadXML )
	{
		// will come to later
	}
	//if loadXML is false, we'll load in the binary file.
	else
	{
		// binary save format
		//	-	1 byte for the length of the coming string
		//	-	name of map, the length of this string is read in above
		//	-	6 ints in order: map columns, map rows, map tilesize, set columns, set rows, set tilesize
		//	-	1 byte for the length of the coming string
		//	-	file name of the image for the tileset, string size determined above
		//	-	for each tile: imagepos, num of triggers, size of coming string, event triggered, object that triggers
		//	-	how many objects in map
		//	-	for each object: PosX, PosY, type, width, height, byte for lenght of coming string, file name for object

		ifstream in;
		
		in.open( filename,ios_base::in | ios_base::binary );

		if( in.is_open() )
		{
			//	-	1 byte for the length of the coming string
			in.read(&strLength,1);

			buffer = new char[(int)strLength+1];

			//	-	name of map, the length of this string is read in above
			in.read(buffer, strLength);

			buffer[strLength] = '\0';

			delete[] buffer;

			//	-	6 ints in order: map columns, map rows, map tilesize, set columns, set rows, set tilesize
			//	-	1 byte for the length of the coming string
			//	-	file name of the image for the tileset, string size determined above
			//	-	for each tile: imagepos, num of triggers, size of coming string, event triggered, object that triggers
			// these next reads will be dealt with by the ObjectManager
			CObjectManager::GetInstance()->LoadWorldMap(in);

			//	-	how many objects in map
			//	-	for each object: PosX, PosY, type, width, height, bool for whether it is a cover object, bool for if it's destructable, 
			//	-	byte for lenght of coming string, file name for object

			int numObj, x, y;
			int type, w, h, id;
			bool destruct, cover;
			in.read((char*)&numObj,4);
			CLoadState::GetInstance()->SetNumObjects(numObj-1);
			for( int n = 0; n < numObj; n++ )
			{
		
				in.read((char*)&type,4);

				in.read((char*)&x,4);
				in.read((char*)&y,4);				
				in.read((char*)&w,4);
				in.read((char*)&h,4);
				in.read((char*)&cover,sizeof(bool));
				in.read((char*)&destruct,sizeof(bool));

				in.read(&strLength,1);
				buffer = new char[(int)strLength+1];
				in.read(buffer,strLength);
				buffer[strLength] = '\0';
				string filename = "Resource\\Graphics\\";
				filename += buffer;
				// Here we find out what object should be made (i.e. enemy, ally, consumable, or just a base object
				switch(type)
				{
				case ED_PLAYER:
					{
						// since creating another singleton is silly and not allowed, we just set the player's position to the editors position
						CPlayer::GetInstance()->SetPosX(x-(w*0.5f));
						CPlayer::GetInstance()->SetPosY(y-(w*0.5f));
						CPlayer::GetInstance()->SetHealth(CPlayer::GetInstance()->GetMaxHealth());
						// and we will always add the player to the object manager here...ask me why if you are curious
						CObjectManager::GetInstance()->AddObject(CPlayer::GetInstance());
						CLoadState::GetInstance()->SetNumLoaded(CLoadState::GetInstance()->GetNumLoaded()+1);
					}
					break;
				case ED_LIGHT_INFANTRY:
					{
						CMessageSystem::GetInstance()->SendMsg( new CCreateLightInfantry((float)(x-(w*0.5f)),(float)(y-(h*0.5f))));
					}
					break;
				case ED_MEDIUM_INFANTRY:
					{
						CMessageSystem::GetInstance()->SendMsg( new CCreateMediumInfantry((float)(x-(w*0.5f)),(float)(y-(h*0.5f))));
					}
					break;
				case ED_HEAVY_INFANTRY:
					{
						CMessageSystem::GetInstance()->SendMsg( new CCreateHeavyInfantry((float)(x-(w*0.5f)),(float)(y-(h*0.5f))));
					}
					break;
				case ED_ENEMY_TANK:
					{
						CMessageSystem::GetInstance()->SendMsg( new CCreateEnemyTank((float)(x-(w*0.5f)),(float)(y-(h*0.5f))));
					}
					break;
				case ED_ENEMY_JEEP:
					{
						// Remember to change this to add gates
						CLoadState::GetInstance()->SetNumLoaded(CLoadState::GetInstance()->GetNumLoaded()+1);
					}
					break;
				case ED_FIRST_BOSS:
					{
						CMessageSystem::GetInstance()->SendMsg( new CCreateBoss((float)(x-(w*0.5f)),(float)(y-(h*0.5f)),1));
					}
					break;
				case ED_SECOND_BOSS:
					{
						CMessageSystem::GetInstance()->SendMsg( new CCreateBoss((float)(x-(w*0.5f)),(float)(y-(h*0.5f)),2));
					}
					break;
				case ED_THIRD_BOSS:
					{
						CMessageSystem::GetInstance()->SendMsg( new CCreateBoss((float)(x-(w*0.5f)),(float)(y-(h*0.5f)),3));
					}
					break;
				case ED_FOURTH_BOSS:
					{
						CMessageSystem::GetInstance()->SendMsg( new CCreateBoss((float)(x-(w*0.5f)),(float)(y-(h*0.5f)),4));
					}
					break;
				case ED_JEEP:
					{
						CMessageSystem::GetInstance()->SendMsg( new CCreateJeep((float)(x-(w*0.5f)),(float)(y-(h*0.5f))));
					}
					break;
				case ED_TANK:
					{
						CMessageSystem::GetInstance()->SendMsg( new CCreateTank((float)(x-(w*0.5f)),(float)(y-(h*0.5f))));
					}
					break;
				case ED_FIRSTAID:
					{
						// Remember to change this to add gates
						CLoadState::GetInstance()->SetNumLoaded(CLoadState::GetInstance()->GetNumLoaded()+1);
					}
					break;
				case ED_AMMO:
					{
						// Remember to change this to add gates
						CLoadState::GetInstance()->SetNumLoaded(CLoadState::GetInstance()->GetNumLoaded()+1);
					}
					break;
				case ED_ADRENALINE:
					{
						// Remember to change this to add gates
						CLoadState::GetInstance()->SetNumLoaded(CLoadState::GetInstance()->GetNumLoaded()+1);
					}
					break;
				case ED_BOMB:
					{
						// Remember to change this to add gates
						CLoadState::GetInstance()->SetNumLoaded(CLoadState::GetInstance()->GetNumLoaded()+1);
					}
					break;
				case ED_REBEL:
					{
						CMessageSystem::GetInstance()->SendMsg(new CCreateAlly((float)x+(w*0.5f),(float)y+(h*0.5f)));
					}
					break;
				case ED_HOSTAGE:
					{
						CMessageSystem::GetInstance()->SendMsg(new CCreateAlly((float)x+(w*0.5f),(float)y+(h*0.5f),true));
					}
					break;
				case ED_ENEMY_EMITTER:
					{
						// Remember to change this to add gates
						CLoadState::GetInstance()->SetNumLoaded(CLoadState::GetInstance()->GetNumLoaded()+1);
					}
					break;
				case ED_GATE:
					{
						id = CSGD_TextureManager::GetInstance()->LoadTexture(filename.c_str());
						CMessageSystem::GetInstance()->SendMsg(new CCreateGate(x+(int)(w*0.5f),y+(int)(h*0.5f),id,w,h));
					}
					break;
				default:
					{
						id = CSGD_TextureManager::GetInstance()->LoadTexture(filename.c_str());
						CMessageSystem::GetInstance()->SendMsg(new CCreateBaseObject((float)x+(w*0.5f),(float)y+(h*0.5f),id,w,h,type,cover,destruct));
					}
				};
				delete[] buffer;
			}

		}
		else
		{
			return false;
		}
	}
	CCamera::GetInstance()->SetBoundaries();
	return true;
}

bool CGamePlayState::UnloadLevel(void)
{
	CObjectManager::GetInstance()->UnLoadWorldMap();
	CObjectManager::GetInstance()->RemoveAllObjects();
	return true;
}

void CGamePlayState::HandleEvent( CEvent* pEvent )
{
	if( m_bLevelBegun == false && pEvent->GetEventID() == "begin.level" )
	{
		CEventSystem::GetInstance()->SendEvent("call.ally");
		CCamera::GetInstance()->Shake();
		m_bLevelBegun = true;
		m_bLevelEnd = false;
	}
	if( pEvent->GetEventID() == "ally.rescue" )
	{
		if( m_bAllyRescue == false )
		{
			CDialogueManager::GetInstance()->SetDialogue("AllyRescue");
			CGame::GetInstance()->AddState(CTalkingState::GetInstance());
			m_bAllyRescue = true;
		}
	}
	if( pEvent->GetEventID() == "continue.level" )
	{
		CEventSystem::GetInstance()->SendEvent("return.ally");
		CCamera::GetInstance()->Shake();
	}
	if( pEvent->GetEventID() == "end.level" )
	{
		// here we will go to the rebel base
		CPlayer::GetInstance()->LevelFinished();
		m_bLevelEnd = true;
	}

	if( pEvent->GetEventID() == "level.one" )
	{
		if( CPlayer::GetInstance()->GetNumWeapons() < 2 )
		{
		}
		else if( m_bLevel1 == false )
			m_bLevel1 = true;
	}

	if( pEvent->GetEventID() == "level.two" )
	{
		if( CPlayer::GetInstance()->GetProgress() < 2 )
		{
		}
		else if( CPlayer::GetInstance()->GetNumWeapons() < 4 )
		{
		}
		else if( m_bLevel2 == false )
			m_bLevel2 = true;
	}

	if( pEvent->GetEventID() == "level.three" )
	{
		if( CPlayer::GetInstance()->GetProgress() < 2 )
		{
		}
		else if( CPlayer::GetInstance()->GetNumWeapons() < 5 )
		{
		}
		else if( m_bLevel3 == false )
			m_bLevel3 = true;
	}

	if( pEvent->GetEventID() == "seige.level" )
	{
		if( m_bLevel4 == false )
			m_bLevel4 = true;
	}

	if( pEvent->GetEventID() == "enter.lobby" )
	{
		if( m_bLevel4a == false )
			m_bLevel4a = true;
	}

	if( pEvent->GetEventID() == "leave.lobby" )
	{
		if( m_bLevel4b == false )
			m_bLevel4b = true;
	}

	if( pEvent->GetEventID() == "spawn.helicopter" )
	{
		CMessageSystem::GetInstance()->SendMsg( new CCreateHelicopter(CPlayer::GetInstance()->GetPosX()-500.0f,100.0f,100.0f,0.0f));
	}
}