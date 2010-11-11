#include "CPlayer.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"
#include "DirectX Wrappers/CSGD_DirectInput.h"
#include "CEventSystem.h"
#include "CMessageSystem.h"
#include "CCamera.h"
#include "CGame.h"
#include "CBase.h"
#include "CBitmapFont.h"
#include "CJeepState.h"
#include "CTankState.h"
#include "Tinyxml/tinyxml.h"
#include "CPlayerInfantryState.h"
#include "CGamePlayState.h"
#include "CBullet.h"
#include "CObjectManager.h"

CPlayer::CPlayer(void)
{
	SetTalkBool(false);
	SetCoverObject(false);
	m_nType = OBJECT_PLAYER;
	SetMaxHealth(100);
	SetHealth(GetMaxHealth());
	m_fTimeBucket = 0.0f;
	m_fConsumableTimer = 1.5f;
}
CPlayer::~CPlayer(void)
{
}
CPlayer* CPlayer::GetInstance(void)
{
	static CPlayer instance;
	return &instance;
}
void CPlayer::SaveProfile(void)
{
	TiXmlDocument outDoc;

	TiXmlDeclaration* pDec = new TiXmlDeclaration("1.0", "utf-8", "yes");

	outDoc.LinkEndChild(pDec);

	TiXmlElement* pOutRoot = new TiXmlElement("player_save");

	outDoc.LinkEndChild(pOutRoot);

	TiXmlElement* pMoney = new TiXmlElement("m_nMoney");
	pMoney->SetAttribute("value", m_nMoney);
	pOutRoot->LinkEndChild(pMoney);
	
	TiXmlElement* pRep = new TiXmlElement("m_nRep");
	pRep->SetAttribute("value", m_nRep);
	pOutRoot->LinkEndChild(pRep);

	TiXmlElement* pMaxHealth = new TiXmlElement("m_nMaxHealth");
	pMaxHealth->SetAttribute("value", GetMaxHealth());
	pOutRoot->LinkEndChild(pMaxHealth);

	TiXmlElement* pHealthPack = new TiXmlElement("m_nHealthPacks");
	pHealthPack->SetAttribute("value", m_Inventory.GetNumItem(CON_HEALTH));
	pOutRoot->LinkEndChild(pHealthPack);

	TiXmlElement* pAdrenaline = new TiXmlElement("m_nAdrenaline");
	pAdrenaline->SetAttribute("value", m_Inventory.GetNumItem(CON_ADRENALINE));
	pOutRoot->LinkEndChild(pAdrenaline);

	outDoc.SaveFile("Resource/Data/Save_File.xml");
}
void CPlayer::LoadProfile(void)
{
	// Load in player profile
	TiXmlDocument doc;
	if(doc.LoadFile("Resource/Data/Save_File.xml"))
	{	
		TiXmlElement* pRoot = doc.RootElement();
		int nTemp = 0;

		TiXmlElement* pSaveInfo = pRoot->FirstChildElement("m_nMoney");
		pSaveInfo->Attribute("value", &m_nMoney);
		
		pSaveInfo = pSaveInfo->NextSiblingElement("m_nRep");	
		pSaveInfo->Attribute("value", &m_nRep);
	
		pSaveInfo = pSaveInfo->NextSiblingElement("m_nMaxHealth");	
		pSaveInfo->Attribute("value", &nTemp);
		SetMaxHealth(nTemp);

		pSaveInfo = pSaveInfo->NextSiblingElement("m_nHealthPacks");	
		pSaveInfo->Attribute("value", &nTemp);
		for(int i = 0; i < nTemp; i++)
			m_Inventory.PickUpItem(CON_HEALTH);

		pSaveInfo = pSaveInfo->NextSiblingElement("m_nAdrenaline");	
		pSaveInfo->Attribute("value", &nTemp);
		for(int i = 0; i < nTemp; i++)
			m_Inventory.PickUpItem(CON_ADRENALINE);
	}
}
void CPlayer::NewPlayer(void)
{
	SetType(OBJECT_PLAYER);
	m_pPlayerState = CPlayerInfantryState::GetInstance();
	m_pPlayerState->Enter();
	//SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/Player.png"));
	CEventSystem::GetInstance()->RegisterClient("player_use_healthpack", this);
	CEventSystem::GetInstance()->RegisterClient("player_use_adrenaline", this);
	CEventSystem::GetInstance()->RegisterClient("next.weapon",this);
	m_nSpeed = 250;
	SetArmor(0);
	SetPosX(320.0f);
	SetPosY(240.0f);
	SetLayer(10);
	SetWidth(16);
	SetHeight(20);
	SetHealth(100);
	SetLayer(10);
	m_chResearchArmorLevel = 0;
	m_chResearchWeaponLevel = 0;
	m_chResearchConsumableLevel = 0;
	m_nMoney = 1000;

	m_pWeapon.clear();
	for(int i = 0; i < WEP_NUMBER; i++)
	{
		CWeapon *Weapon = new CWeapon(i);
		m_pWeapon.push_back(Weapon);
	}
	m_nCurrentWeapon = 0;
	m_nCurrentItem = 0;
	m_nNumWeapons = 0;
}
void CPlayer::AddWeapon(int nWeapon)
{
	for(unsigned int i = 0; i < m_pWeapon.size(); i++)
	{
		if(m_pWeapon[i]->GetType() == nWeapon)
			return;
	}
	CWeapon *Weapon = new CWeapon(nWeapon);
	m_pWeapon.push_back(Weapon);
}
bool CPlayer::SpendMoney(int nSpendingAmount)
{
	if(m_nMoney >= nSpendingAmount)
	{
		m_nMoney -= nSpendingAmount;
		return true;
	}
	return false;
}
void CPlayer::LevelFinished(void)
{
	m_chProgress++;
//	switch(m_chProgress)
//	{
//	case 0:
//		m_nNumWeapons = 1;
//		break;
//	case 1:
//		m_nNumWeapons = 2;
//		break;
//	case 2:
//		m_nNumWeapons = 4;
//		break;
//	case 3:
//		m_nNumWeapons = 5;
//		break;
//	case 4:
//		m_nNumWeapons = 6;
//		break;
//	}
}

void CPlayer::ClosePlayer(void)
{
	CEventSystem::GetInstance()->UnregisterClient("player_use_healthpack", this);
	CEventSystem::GetInstance()->UnregisterClient("player_use_adrenaline", this);
	CEventSystem::GetInstance()->UnregisterClient("next.weapon",this);
	CSGD_TextureManager::GetInstance()->UnloadTexture(GetImageID());

	vector<CWeapon*>::iterator iter = m_pWeapon.begin();
	CWeapon* temp;
	while(iter != m_pWeapon.end())
	{
		temp = *iter;
		delete temp;
		iter++;
	}
	m_pWeapon.clear();
}
void CPlayer::NextWeapon(void)
{
	if(++m_nCurrentWeapon == m_nNumWeapons)
		m_nCurrentWeapon = 0;
}
void CPlayer::PrevWeapon(void)
{
	if(--m_nCurrentWeapon < 0)
		m_nCurrentWeapon = m_nNumWeapons-1;
}
void CPlayer::NextItem(void)
{
	if(++m_nCurrentItem == CON_NUMBER)
		m_nCurrentItem = 0;
}
bool CPlayer::CheckCollision(CBase* pBase )
{
	if( pBase->GetType() == OBJECT_ALLY )
	{
		tVector2D toAlly;
		toAlly.fX = pBase->GetPosX() - GetPosX();
		toAlly.fY = pBase->GetPosY() - GetPosY();

		if( Vector2DLength(toAlly) < 40 )
			SetTalkBool(true);
		else
			SetTalkBool(false);
	}
	RECT collision;
	if( CBase::CheckCollision( pBase, &collision ) )
	{	
		if( pBase->GetType() == OBJECT_CONSUMABLE )
		{
			CConsumable* item = (CConsumable*)pBase;
			if(item->GetItemID() == CON_HEALTH)
			{
				m_Inventory.PickUpItem(CON_HEALTH);
				CEventSystem::GetInstance()->SendEvent( "picked_up", pBase );
				return false;
			}
			if( item->GetItemID() == CON_ADRENALINE )
			{
				m_Inventory.PickUpItem(CON_ADRENALINE);
				CEventSystem::GetInstance()->SendEvent( "picked_up", pBase );
				return false;
			}
			if( item->GetItemID() == CON_AMMO )
			{
				GetCurrWeapon()->SetAmmo(GetCurrWeapon()->GetCurrAmmo()+10);
				CEventSystem::GetInstance()->SendEvent( "picked_up", pBase );
				return false;
			}
		}
		else if( pBase->GetType() == OBJECT_BULLET )
		{
			CBullet* bullet = (CBullet*)pBase;
			if( bullet->GetOwner() != this )
			{
				SetHealth(GetHealth()-(bullet->GetDamage()-GetArmor()));
				CMessageSystem::GetInstance()->SendMsg( new CDestroyBullet(bullet));
			}
			return false;
		}
		else if( pBase->GetType() == OBJECT_ROCKET )
		{
			return false;
		}

		if( pBase->GetType() == OBJECT_JEEP)
		{
			if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_E))
			{
				m_pTempJeep = (CJeep*)pBase;
				CEventSystem::GetInstance()->SendEvent("Change_Position", pBase);
				ChangeState(CJeepState::GetInstance());
			}
		}

		if( pBase->GetType() == OBJECT_ENEMY)
		{			
			if(GetPlayerState() == CJeepState::GetInstance() || GetPlayerState() == CTankState::GetInstance())
			{
				CEventSystem::GetInstance()->SendEvent("enemy.died",pBase);
				CMessageSystem::GetInstance()->SendMsg( new CDestroyEnemy((CEnemy*)pBase) );
			}
		}

		if(pBase->GetType() == OBJECT_TANK)
		{
			if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_E))
			{
				m_pTempTank = (CTank*)pBase;
				CEventSystem::GetInstance()->SendEvent("Change_Position", pBase);
				ChangeState(CTankState::GetInstance());
			}
		}

		int rWidth, rHeight;
		rWidth = collision.right - collision.left;
		rHeight = collision.bottom - collision.top;
		if( rWidth >= rHeight )
		{
			if( GetPosY() < pBase->GetPosY() )
			{
				SetPosY(pBase->GetPosY() - ((GetHeight()*0.5f) + (pBase->GetHeight()*0.5f)));
				CCamera::GetInstance()->UpdateCameraPos(GetPosX(),GetPosY());
			}
			else
			{
				SetPosY(pBase->GetPosY() + ((GetHeight()*0.5f) + (pBase->GetHeight()*0.5f)));
				CCamera::GetInstance()->UpdateCameraPos(GetPosX(),GetPosY());
			}
		}
		if( rHeight >= rWidth )
		{
			if( GetPosX() < pBase->GetPosX() )
			{
				SetPosX(pBase->GetPosX() - ((GetWidth()*0.5f) + (pBase->GetWidth()*0.5f)));
				CCamera::GetInstance()->UpdateCameraPos(GetPosX(),GetPosY());
			}
			else
			{
				SetPosX(pBase->GetPosX() + ((GetWidth()*0.5f) + (pBase->GetWidth()*0.5f)));
				CCamera::GetInstance()->UpdateCameraPos(GetPosX(),GetPosY());
			}
		}
		SetVelX(0.0f);
		SetVelY(0.0f);

		return false;
	}
	return false;
}
void CPlayer::Update(float fElapsedTime)
{
	if( m_bConActive == true )
		m_fTimeBucket += fElapsedTime;

	if( m_bConActive == true && m_fTimeBucket > m_fConsumableTimer )
	{
		m_fTimeBucket = 0.0f;
		m_nSpeed = (int)(m_nSpeed * 0.5f);
		m_bConActive = false;
	}

	m_pPlayerState->Update(fElapsedTime);
	m_pWeapon[m_nCurrentWeapon]->Update(fElapsedTime);

	// Update facing normal
	m_vFacingNormal.fX = GetVelX();
	m_vFacingNormal.fY = GetVelY();

	m_vFacingNormal = Vector2DNormalize(m_vFacingNormal);

	// Make sure the player is still in the level
	int mapWidth = CObjectManager::GetInstance()->GetMap()->MapTileSize * CObjectManager::GetInstance()->GetMap()->MapRow;
	int mapHeight = CObjectManager::GetInstance()->GetMap()->MapTileSize * CObjectManager::GetInstance()->GetMap()->MapColumn;
	if( GetPosX()+GetWidth()*0.5f > mapWidth )
	{
		SetPosX(mapWidth-GetWidth()*0.5f);
	}
	if( GetPosY()+GetHeight()*0.5f > mapHeight )
	{
		SetPosY(mapHeight-GetHeight()*0.5f);
	}

	if(this->GetHealth() < 0)
		this->SetHealth(0);

	// Checking for and sending events of the tile I'm on
	int c, r;
	// Getting the tile co-ordinates
	c = (int)(GetPosY() / CObjectManager::GetInstance()->GetMap()->MapTileSize);
	r = (int)(GetPosX() / CObjectManager::GetInstance()->GetMap()->MapTileSize);

	CObjectManager::GetInstance()->GetMap()->m_vTileList[c][r].CallEvents(this);
	
	// Update the camera's position
	CCamera::GetInstance()->UpdateCameraPos(GetPosX(), GetPosY());
}
void CPlayer::Render(float fCamPosX, float fCamPosY)
{
	m_pPlayerState->Render(fCamPosX, fCamPosY);
}
RECT CPlayer::GetRect(void)
{
	RECT collisionRect;
	collisionRect.left = (LONG)(GetPosX() - GetWidth() * 0.5f);
	collisionRect.top = (LONG)(GetPosY() - GetHeight() * 0.5f);
	collisionRect.right = collisionRect.left + GetWidth();
	collisionRect.bottom  = collisionRect.top + GetHeight();

	return collisionRect;
}
void CPlayer::HandleEvent(CEvent* pEvent)
{
	if( pEvent->GetEventID() == "player_use_healthpack" && pEvent->GetParam() == this )
	{
		if(GetHealth() != GetMaxHealth())
		{
			SetHealth(GetHealth()+50);
			m_Inventory.ReduceNumItem(CON_HEALTH);
			if(GetHealth() > GetMaxHealth())
				SetHealth(GetMaxHealth());
		}
	}
	if( pEvent->GetEventID() == "player_use_adrenaline" && pEvent->GetParam() == this )
	{
		m_Inventory.ReduceNumItem(CON_ADRENALINE);
		m_bConActive = true;
		m_nSpeed *= 2;
	}

	if( pEvent->GetEventID() == "next.weapon" )
	{
		if( m_nNumWeapons < 6 )
			m_nNumWeapons++;
	}
}

void CPlayer::ChangeState( IPlayerState* newState )
{
	m_pPlayerState = newState;
	m_pPlayerState->Enter();
}