//////////////////////////////////////////////////////////////////////////////
// File: "CGame.cpp"
//
// Date Edited: 10/14/2010
//
// Purpose: 
//
//////////////////////////////////////////////////////////////////////////////

#include "CGame.h"
#include "CBase.h"
#include "CIntroState.h"
#include "CMainMenuState.h"
#include "CBitmapFont.h"
#include "CAnimationManager.h"
#include "DirectX Wrappers/SGD_Math.h"
#include "CObjectManager.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CEnemy.h"
#include "CCamera.h"
#include "CCursor.h"
#include "CConsumable.h"
#include "CLightInfantry.h"
#include "CMediumInfantry.h"
#include "CHeavyInfantry.h"
#include "CEnemyTank.h"
#include "CPlayerInfantryState.h"
#include "CAlly.h"
#include "CTank.h"
#include "CJeep.h"
#include "CBoss1.h"
#include "CBoss2.h"
#include "CBoss3.h"
#include "CFinalBoss.h"
#include "CRocket.h"
#include "CShopState.h"
#include "CResearchCenterState.h"
#include "CProgressCenterState.h"
#include "CHelicopter.h"
#include "CLoadState.h"
#include "CGate.h"
#include "CDialogueManager.h"

//	Proper Singleton:
//	Constructor
CGame::CGame(void)
{
	m_pD3D	 = NULL;
	m_pDS	 = NULL;
	m_pDI	 = NULL;
	m_pTM	 = NULL;
	m_pWM	 = NULL;

	m_nImageID =	-1;
	m_nSoundID =	-1;

	m_nPanning =	0;
	m_nBGMVolume =	100;
	m_nSFXVolume =	100;

	m_dwTimeStamp = GetTickCount();
	m_fElapsedTime = 0.0f;
	m_fGameTime = 0.0f;

	CEventSystem::GetInstance()->RegisterClient("enter.shop",this);
	CEventSystem::GetInstance()->RegisterClient("enter.progress",this);
	CEventSystem::GetInstance()->RegisterClient("enter.research",this);
}

//		destructor
CGame::~CGame(void)
{
	CEventSystem::GetInstance()->UnregisterClient("enter.shop",this);
	CEventSystem::GetInstance()->UnregisterClient("enter.progress",this);
	CEventSystem::GetInstance()->UnregisterClient("enter.research",this);
}

//	Singleton accessor
CGame* CGame::GetInstance(void)
{
	static CGame instance;
	return &instance;
}

//	3 steps a game uses in its lifetime
//		Initialization
void CGame::Initialize( HWND hWnd, HINSTANCE hInstance, int nScreenWidth, int nScreenHeight, bool bIsWindowed )
{
	//Get singleton pointers
	m_pD3D	= CSGD_Direct3D::GetInstance();
	m_pDS	= CSGD_DirectSound::GetInstance();
	m_pDI	= CSGD_DirectInput::GetInstance();
	m_pTM	= CSGD_TextureManager::GetInstance();
	m_pWM	= CSGD_WaveManager::GetInstance();
	m_pMS	= CMessageSystem::GetInstance();
	m_pES	= CEventSystem::GetInstance();

	//Initialize singletons
	m_pD3D->InitDirect3D( hWnd, nScreenWidth, nScreenHeight, bIsWindowed, true );
	m_pTM->InitTextureManager( m_pD3D->GetDirect3DDevice(), m_pD3D->GetSprite() );
	m_pDS->InitDirectSound( hWnd );
	m_pWM->InitWaveManager( hWnd, m_pDS->GetDSObject() );
	m_pDI->InitDirectInput( hWnd, hInstance, DI_KEYBOARD );
	m_pDI->InitDirectInput( hWnd, hInstance, DI_MOUSE, DI_MOUSE );
	m_pMS->InitMessageSystem( CGame::MessageProc );

	//Load common assets:
	ChangeState( CMainMenuState::GetInstance() );		
	AddState( CIntroState::GetInstance() );		
	
	m_dwPreviousTime = m_dwTimeStamp = GetTickCount();
}

//		Cleanup
void CGame::Shutdown(void)
{
	ClearAllStates();

	m_pES->ShutdownEventSystem();
	m_pMS->ShutdownMessageSystem();


	//Shutting down in opposite order
	if( m_pDI )
	{
		m_pDI->ShutdownDirectInput();
		m_pDI = NULL;
	}

	if( m_pWM )
	{
		m_pWM->ShutdownWaveManager();
		m_pWM = NULL;
	}

	if( m_pDS )
	{
		m_pDS->ShutdownDirectSound();
		m_pDS = NULL;
	}

	if( m_pTM )
	{
		m_pTM->ShutdownTextureManager();
		m_pTM = NULL;
	}

	if( m_pD3D )
	{
		m_pD3D->ShutdownDirect3D();
		m_pD3D = NULL;
	}
}

//		Execution
bool CGame::Main(void)
{
	DWORD dwStartTime = GetTickCount();

	m_fElapsedTime = float(dwStartTime - m_dwPreviousTime) * 0.001f;
	m_fGameTime += m_fElapsedTime;

	m_dwPreviousTime = dwStartTime;

	//3 Steps a game does during execution:
	//	Input
	if( Input() == false )
		return false;
	//	Update
	Update();
	//	Render(Draw)
	Render();

	return true;
}

bool CGame::Input(void)
{
	//	Get the current state of our input
	m_pDI->ReadDevices();

	if( (m_pDI->KeyDown( DIK_LALT ) || m_pDI->KeyDown( DIK_RALT )) && m_pDI->KeyPressed( DIK_RETURN ) )
	{
		const D3DPRESENT_PARAMETERS* d3dpp = m_pD3D->GetPresentParams();
		m_pD3D->ChangeDisplayParam( d3dpp->BackBufferWidth, d3dpp->BackBufferHeight, !(d3dpp->Windowed) );
		m_pDI->ClearInput();
	}
	if(m_pGS.size())
		return m_pGS[m_pGS.size()-1]->Input();
	return true;
}

void CGame::Update()
{
	m_pES->ProcessEvents();
	m_pMS->ProcessMessages();

	if( m_pGS[m_pGS.size()-1] == CLoadState::GetInstance() && CLoadState::GetInstance()->GetPercentFinished() <= 100 )
	{
		CGame::RemoveTopState();
	}

	m_pGS[m_pGS.size()-1]->Update(m_fElapsedTime);
	m_pWM->Update();	// Clean up excess copies of sounds
	
	CBitmapFont::GetInstance()->Update(m_fElapsedTime);
	CCursor::GetInstance()->Update(m_fElapsedTime);
}

void CGame::Render(void)
{
	m_pD3D->Clear();
	m_pD3D->DeviceBegin();
	m_pD3D->SpriteBegin();

	for(unsigned int i = 0; i < m_pGS.size(); i++)
		m_pGS[i]->Render();

	CCursor::GetInstance()->Render();

	m_pD3D->SpriteEnd();
	m_pD3D->DeviceEnd();
	m_pD3D->Present();
}
void CGame::ClearAllStates(void)
{
	for(unsigned int i = 0; i < m_pGS.size(); i++)
		m_pGS[i]->Exit();
	m_pGS.clear();
}
void CGame::ChangeState( IGameState* newState )
{
	ClearAllStates();
	m_pGS.push_back(newState);

	if(newState)
		m_pGS[0]->Enter();
}
void CGame::AddState( IGameState* newState )
{
	m_pGS.push_back(newState);
	m_pGS[m_pGS.size()-1]->Enter();
}
void CGame::RemoveTopState(void)
{
	m_pGS[m_pGS.size()-1]->Exit();
	m_pGS.pop_back();
}
void CGame::SetBGMVolume( int nBGMVolume )
{
	if( nBGMVolume > 100 )
		m_nBGMVolume = 100;
	else if( nBGMVolume < 0 )
		m_nBGMVolume = 0;
	else
		m_nBGMVolume = nBGMVolume;
}

void CGame::SetSFXVolume( int nSFXVolume )
{
	if( nSFXVolume > 100 )
		m_nSFXVolume = 100;
	else if( nSFXVolume < 0 )
		m_nSFXVolume = 0;
	else
		m_nSFXVolume = nSFXVolume;
}

void CGame::SetPanning( int nPanning )
{ 
	if(nPanning < -100 )
		m_nPanning = -100;
	else if(nPanning > 100 )
		m_nPanning = 100;
	else
		m_nPanning = nPanning;
}
void CGame::MessageProc( CBaseMessage* pMsg )
{
	switch( pMsg->GetMsgID() )
	{
	case MSG_CREATE_PLAYER_BULLET:
		{
			CCreatePlayerBullet* pCB = (CCreatePlayerBullet*)pMsg;
			tVector2D vDirection;
			vDirection.fX = ((CCursor::GetInstance()->GetPosX() + CCamera::GetInstance()->GetPosX())- pCB->GetPlayer()->GetPosX());
			vDirection.fY = ((CCursor::GetInstance()->GetPosY() + CCamera::GetInstance()->GetPosY())- pCB->GetPlayer()->GetPosY());
			vDirection = Vector2DNormalize(vDirection);

			tVector2D player;
			player.fX = 0.0f;
			player.fY = -1.0f;
			float fAngle = AngleBetweenVectors(player, vDirection);
			if(CCursor::GetInstance()->GetPosX() + CCamera::GetInstance()->GetPosX()< pCB->GetPlayer()->GetPosX())
				fAngle = -fAngle;
			
			float temp = rand()/(float)RAND_MAX*D3DXToRadian(pCB->GetPlayer()->GetCurrWeapon()->GetAccuracy());
			CSGD_WaveManager::GetInstance()->Play(pCB->GetPlayer()->GetWeaponSound());

			CBullet *pBullet = new CBullet();
			pBullet->SetOwner( pCB->GetPlayer() );
			pBullet->SetDamage( pCB->GetPlayer()->GetCurrWeapon()->GetDamage() );
			pBullet->SetPosX( pCB->GetPlayer()->GetPosX() );
			pBullet->SetPosY( pCB->GetPlayer()->GetPosY() );
			pBullet->SetRange( pCB->GetPlayer()->GetCurrWeapon()->GetRange());
			pBullet->SetRotation( fAngle );
			pBullet->SetVelX( (vDirection.fX+temp) * (pCB->GetPlayer()->GetCurrWeapon()->GetBulletSpeed()));
			pBullet->SetVelY( (vDirection.fY+temp) * (pCB->GetPlayer()->GetCurrWeapon()->GetBulletSpeed()));
			pBullet->SetWeaponID( pCB->GetPlayer()->GetCurrWeapon()->GetWeaponID());
		
			CObjectManager::GetInstance()->AddObject(pBullet);
			pBullet->Release();
		}
		break;

	case MSG_DESTROY_BULLET:
		{
			CDestroyBullet* pDB = (CDestroyBullet*)pMsg;

			CObjectManager::GetInstance()->RemoveObject( pDB->GetBullet() );
		}
		break;
	
	case MSG_TESTER_MEDPACK:
		{
			CTesterMedPack* pTMP = (CTesterMedPack*)pMsg;
		
			CConsumable *pConsumable = new CConsumable(CON_HEALTH);
			pConsumable->SetType(OBJECT_CONSUMABLE);
			pConsumable->SetItemID(CON_HEALTH);
			pConsumable->SetPosX(pTMP->GetPlayer()->GetPosX());
			pConsumable->SetPosY(pTMP->GetPlayer()->GetPosY() - 50);
			pConsumable->SetVelX(0.0f);
			pConsumable->SetVelY(0.0f);
		
			CObjectManager::GetInstance()->AddObject(pConsumable);
			pConsumable->Release();
		}
		break;
	case MSG_DESTROY_CONSUMABLE:
		{
			CDestroyConsumable* pDC = (CDestroyConsumable*)pMsg;

			CObjectManager::GetInstance()->RemoveObject( pDC->GetConsumable() );
		}
		break;
	case MSG_CREATE_BASE_OBJECT:
		{
			CCreateBaseObject *msg = (CCreateBaseObject*)pMsg;

			CBase *pObject = new CBase();
			pObject->SetPosX(msg->GetPosX());
			pObject->SetPosY(msg->GetPosY());
			pObject->SetImageID(msg->GetImageID());
			pObject->SetWidth(msg->GetWidth());
			pObject->SetHeight(msg->GetHeight());
			pObject->SetCoverObject(msg->GetCoverBool());
			pObject->SetDestructable(msg->GetDestructableBool());
			CObjectManager::GetInstance()->AddObject(pObject);
			pObject->Release();
			CLoadState::GetInstance()->SetNumLoaded(CLoadState::GetInstance()->GetNumLoaded()+1);
		}
		break;
	case MSG_CREATE_ENEMY_BULLET:
		{
			CCreateEnemyBullet* pCB = (CCreateEnemyBullet*)pMsg;
			tVector2D vDirection;
			if( pCB->GetEnemy()->GetType() == OBJECT_ENEMY )
			{
				CEnemy* pEnemy = (CEnemy*)pCB->GetEnemy();
				vDirection.fX = (pEnemy->GetTarget()->GetPosX() - pEnemy->GetPosX());
				vDirection.fY = (pEnemy->GetTarget()->GetPosY() - pEnemy->GetPosY());
				vDirection = Vector2DNormalize(vDirection);

				tVector2D enemy;
				enemy.fX = pEnemy->GetFacing().fX;
				enemy.fY = pEnemy->GetFacing().fY;

				float fAngle = AngleBetweenVectors(enemy, vDirection);

				if(pEnemy->GetTarget()->GetPosX()+CCamera::GetInstance()->GetPosX() < pEnemy->GetPosX())
					fAngle = -fAngle;

				CBullet* pBullet;

				if( pEnemy->GetEnemyID() == ENEMY_TANK )
				{
					pEnemy->SetCurrAnimation("Fire");
					pBullet = new CRocket(1.0f);
					pBullet->SetOwner( pEnemy );
					pBullet->SetPosX( pEnemy->GetTarget()->GetPosX());
					pBullet->SetPosY( pEnemy->GetTarget()->GetPosY());
					pBullet->SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/Rocket.png"));
				}
				else
				{
					pBullet = new CBullet();
					pBullet->SetOwner( pEnemy );
					pBullet->SetPosX( pEnemy->GetPosX() );
					pBullet->SetPosY( pEnemy->GetPosY() );
					pBullet->SetRotation( fAngle );
					pBullet->SetDamage( pEnemy->GetWeapon()->GetDamage() );
					pBullet->SetVelX( vDirection.fX * (pEnemy->GetWeapon()->GetBulletSpeed()));
					pBullet->SetVelY( vDirection.fY * (pEnemy->GetWeapon()->GetBulletSpeed()));
					pBullet->SetRange( pEnemy->GetWeapon()->GetRange() );
					pBullet->SetWeaponID(pEnemy->GetWeapon()->GetWeaponID());
				}

				float percent = (pEnemy->GetPosX() - CPlayer::GetInstance()->GetPosX())/
							CSGD_Direct3D::GetInstance()->GetPresentParams()->BackBufferWidth;

				CSGD_WaveManager::GetInstance()->SetPan(pEnemy->GetWeaponSoundID(), (int)(100*percent));

				CSGD_WaveManager::GetInstance()->Play(pEnemy->GetWeaponSoundID());

				CObjectManager::GetInstance()->AddObject(pBullet);
				pBullet->Release();
			}
			else
			{
				CAlly* pShooter = (CAlly*)pCB->GetEnemy();

				if( pShooter->GetTarget() != NULL )
				{
					vDirection.fX = (pShooter->GetTarget()->GetPosX() - pShooter->GetPosX());
					vDirection.fY = (pShooter->GetTarget()->GetPosY() - pShooter->GetPosY());
					vDirection = Vector2DNormalize(vDirection);

					tVector2D enemy;
					enemy.fX = pShooter->GetFacing().fX;
					enemy.fY = pShooter->GetFacing().fY;

					float fAngle = AngleBetweenVectors(enemy, vDirection);

					if(pShooter->GetTarget()->GetPosX()+CCamera::GetInstance()->GetPosX() < pShooter->GetPosX())
						fAngle = -fAngle;


					CBullet *pBullet = new CBullet();
					pBullet->SetOwner( pShooter );
					pBullet->SetPosX( pShooter->GetPosX() );
					pBullet->SetPosY( pShooter->GetPosY() );
					pBullet->SetRotation( fAngle );
					pBullet->SetDamage( pShooter->GetWeapon()->GetDamage() );
					pBullet->SetVelX( vDirection.fX * (pShooter->GetWeapon()->GetBulletSpeed()));
					pBullet->SetVelY( vDirection.fY * (pShooter->GetWeapon()->GetBulletSpeed()));
					pBullet->SetRange( pShooter->GetWeapon()->GetRange() );
					pBullet->SetWeaponID(pShooter->GetWeapon()->GetWeaponID());

					float percent = (pShooter->GetPosX() - CPlayer::GetInstance()->GetPosX())/
							CSGD_Direct3D::GetInstance()->GetPresentParams()->BackBufferWidth;

					CSGD_WaveManager::GetInstance()->SetPan(pShooter->GetWeaponSoundID(), (int)(100*percent));

					CSGD_WaveManager::GetInstance()->Play(pShooter->GetWeaponSoundID());


					CObjectManager::GetInstance()->AddObject(pBullet);
					pBullet->Release();
				}
			}
		}
		break;
	case MSG_CREATE_LIGHTINFANTRY:
		{
			CCreateLightInfantry* Msg = (CCreateLightInfantry*)pMsg;

			CLightInfantry *pEnemy = new CLightInfantry();

			pEnemy->SetPosX(Msg->GetPosX());
			pEnemy->SetPosY(Msg->GetPosY());

			CObjectManager::GetInstance()->AddObject(pEnemy);
			pEnemy->Release();
			CLoadState::GetInstance()->SetNumLoaded(CLoadState::GetInstance()->GetNumLoaded()+1);
		}
		break;
	case MSG_CREATE_MEDIUMINFANTRY:
		{
			CCreateMediumInfantry* Msg = (CCreateMediumInfantry*)pMsg;

			CMediumInfantry *pEnemy = new CMediumInfantry();

			pEnemy->SetPosX(Msg->GetPosX());
			pEnemy->SetPosY(Msg->GetPosY());

			CObjectManager::GetInstance()->AddObject(pEnemy);
			pEnemy->Release();
			CLoadState::GetInstance()->SetNumLoaded(CLoadState::GetInstance()->GetNumLoaded()+1);
		}
		break;
	case MSG_CREATE_HEAVYINFANTRY:
		{
			CCreateHeavyInfantry* Msg = (CCreateHeavyInfantry*)pMsg;

			CHeavyInfantry *pEnemy = new CHeavyInfantry();

			pEnemy->SetPosX(Msg->GetPosX());
			pEnemy->SetPosY(Msg->GetPosY());

			CObjectManager::GetInstance()->AddObject(pEnemy);
			pEnemy->Release();
			CLoadState::GetInstance()->SetNumLoaded(CLoadState::GetInstance()->GetNumLoaded()+1);
		}
		break;
	case MSG_CREATE_ENEMY_TANK:
		{
			CCreateEnemyTank* Msg = (CCreateEnemyTank*)pMsg;

			CEnemyTank* pEnemy = new CEnemyTank();

			pEnemy->SetPosX(Msg->GetPosX());
			pEnemy->SetPosY(Msg->GetPosY());

			CObjectManager::GetInstance()->AddObject(pEnemy);
			CLoadState::GetInstance()->SetNumLoaded(CLoadState::GetInstance()->GetNumLoaded()+1);
		}
		break;
	case MSG_DESTROY_ENEMY:
		{
			CDestroyEnemy* Msg = (CDestroyEnemy*)pMsg;

			if( Msg->GetEnemy()->GetPlayerKill() == true )
			{
				CPlayer::GetInstance()->SetMoney(CPlayer::GetInstance()->GetMoney() + Msg->GetEnemy()->GetMoneyReward());
				CPlayer::GetInstance()->SetRep(CPlayer::GetInstance()->GetRep() + Msg->GetEnemy()->GetRepReward());
			}

			int consumable = rand() % 3;

			CMessageSystem::GetInstance()->SendMsg(new CCreateConsumable(Msg->GetEnemy()->GetPosX(),Msg->GetEnemy()->GetPosX(),consumable));

			CObjectManager::GetInstance()->RemoveObject(Msg->GetEnemy());
		}
		break;
	case MSG_CREATE_ALLY:
		{
			CCreateAlly* Msg = (CCreateAlly*)pMsg;

			CAlly* pAlly = new CAlly(Msg->GetHostage());
			pAlly->SetPosX(Msg->GetPosX());
			pAlly->SetPosY(Msg->GetPosY());

			CObjectManager::GetInstance()->AddObject(pAlly);
			pAlly->Release();
			CLoadState::GetInstance()->SetNumLoaded(CLoadState::GetInstance()->GetNumLoaded()+1);
		}
		break;
	case MSG_CREATE_TANK:
		{
			CCreateTank* Msg = (CCreateTank*)pMsg;

			CTank* Tank2 = new CTank();

			Tank2->SetType(OBJECT_TANK);
			Tank2->SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/Idle Tank.png", D3DCOLOR_XRGB(255,0,255)));
			Tank2->SetPosX(Msg->GetPosX());
			Tank2->SetPosY(Msg->GetPosY());
			Tank2->SetWidth(64);
			Tank2->SetHeight(64);
			Tank2->SetVelX(0.0f);
			Tank2->SetVelY(0.0f);
			Tank2->SetDirection(0.0f, -1.0f);
			Tank2->SetRotation(0.0f);

			CObjectManager::GetInstance()->AddObject(Tank2);
			Tank2->Release();
			CLoadState::GetInstance()->SetNumLoaded(CLoadState::GetInstance()->GetNumLoaded()+1);
		}
		break;
	case MSG_CREATE_JEEP:
		{
			CCreateJeep* Msg = (CCreateJeep*)pMsg;

			CJeep* Jeep = new CJeep();

			Jeep->SetType(OBJECT_JEEP);
			Jeep->SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/vehicle.png"));
			Jeep->SetPosX(Msg->GetPosX());
			Jeep->SetPosY(Msg->GetPosY());
			Jeep->SetWidth(32);
			Jeep->SetHeight(64);
			Jeep->SetVelX(0.0f);
			Jeep->SetVelY(0.0f);
			Jeep->SetDirection(0.0f, -1.0f);
			Jeep->SetRotation(0.0f);

			CObjectManager::GetInstance()->AddObject(Jeep);
			Jeep->Release();
			CLoadState::GetInstance()->SetNumLoaded(CLoadState::GetInstance()->GetNumLoaded()+1);
		}
		break;
	case MSG_CREATE_HELICOPTER:
		{
			CCreateHelicopter* Msg = (CCreateHelicopter*)pMsg;

			CHelicopter* pEnemy = new CHelicopter();

			pEnemy->SetPosX(Msg->GetPosX());
			pEnemy->SetPosY(Msg->GetPosY());
			pEnemy->SetVelX(Msg->GetVelX());
			pEnemy->SetVelY(Msg->GetVelY());

			CObjectManager::GetInstance()->AddObject(pEnemy);
			pEnemy->Release();
		}
		break;
	case MSG_CREATE_BOSS:
		{
			CCreateBoss* Msg = (CCreateBoss*)pMsg;

			switch(Msg->GetNumber())
			{
			case 1:
				{
					CBoss1* pEnemy = new CBoss1();

					pEnemy->SetPosX(Msg->GetPosX());
					pEnemy->SetPosY(Msg->GetPosY());

					CObjectManager::GetInstance()->AddObject(pEnemy);
					pEnemy->Release();
				}
				break;
			case 2:
				{
					CBoss2* pEnemy = new CBoss2();

					pEnemy->SetPosX(Msg->GetPosX());
					pEnemy->SetPosY(Msg->GetPosY());

					CObjectManager::GetInstance()->AddObject(pEnemy);
					pEnemy->Release();
				}
				break;
			case 3:
				{
					CBoss3* pEnemy = new CBoss3();

					pEnemy->SetPosX(Msg->GetPosX());
					pEnemy->SetPosY(Msg->GetPosY());

					CObjectManager::GetInstance()->AddObject(pEnemy);
					pEnemy->Release();
				}
				break;
			case 4:
				{
					CFinalBoss* pEnemy = new CFinalBoss();

					pEnemy->SetPosX(Msg->GetPosX());
					pEnemy->SetPosY(Msg->GetPosY());

					CObjectManager::GetInstance()->AddObject(pEnemy);
					pEnemy->Release();
				}
				break;
			};
			CLoadState::GetInstance()->SetNumLoaded(CLoadState::GetInstance()->GetNumLoaded()+1);
		}
		break;
	case MSG_DESTROY_BASE:
		{
			CDestroyBase* Msg = (CDestroyBase*)pMsg;

			CObjectManager::GetInstance()->RemoveObject(Msg->GetBase());
		}
		break;
	case MSG_CREATE_CONSUMABLE:
		{
			CCreateConsumable* pTMP = (CCreateConsumable*)pMsg;
		
			CConsumable *pConsumable = new CConsumable(pTMP->GetItemId());
			pConsumable->SetPosX(pTMP->GetPosX());
			pConsumable->SetPosY(pTMP->GetPosY());
		
			CObjectManager::GetInstance()->AddObject(pConsumable);
			pConsumable->Release();
		}
		break;
	case MSG_CREATE_GATE:
		{
			CCreateGate* Msg = (CCreateGate*)pMsg;

			CGate* pGate = new CGate();

			pGate->SetPosX((float)Msg->GetPosX());
			pGate->SetPosY((float)Msg->GetPosY());
			pGate->SetImageID(Msg->GetImadeID());
			pGate->SetWidth(Msg->GetWidth());
			pGate->SetHeight(Msg->GetHeight());

			CObjectManager::GetInstance()->AddObject(pGate);
			pGate->Release();
			CLoadState::GetInstance()->SetNumLoaded(CLoadState::GetInstance()->GetNumLoaded()+1);
		}
		break;
	}
}

void CGame::HandleEvent(CEvent* pEvent)
{
	if( pEvent->GetEventID() == "enter.shop" )
	{
		if(CPlayer::GetInstance()->GetState() == CPlayerInfantryState::GetInstance())
		{
			AddState(CShopState::GetInstance());
			CPlayer::GetInstance()->SetPosY(CPlayer::GetInstance()->GetPosY()+32);
		}
	}
	if( pEvent->GetEventID() == "enter.research" )
	{
		if(CPlayer::GetInstance()->GetState() == CPlayerInfantryState::GetInstance())
		{
			AddState(CResearchCenterState::GetInstance());
			CPlayer::GetInstance()->SetPosY(CPlayer::GetInstance()->GetPosY()+32);
		}
	}
	if( pEvent->GetEventID() == "enter.progress" )
	{
		if(CPlayer::GetInstance()->GetState() == CPlayerInfantryState::GetInstance())
		{
			AddState(CProgressCenterState::GetInstance());
			CPlayer::GetInstance()->SetPosY(CPlayer::GetInstance()->GetPosY()+32);
		}
	}
}