#include "CWeapon.h"
#include "Tinyxml/tinyxml.h"
#include "CPlayer.h"
#include "CEventSystem.h"
#include "CMessageSystem.h"

CWeapon::CWeapon(void)
{
	m_fReloadTimer = 0.0f;
	m_fFireDelayTimer = 0.0f;
}
CWeapon::CWeapon(int nWeapon)
{
	m_nWeaponID = nWeapon;
	LoadWeapon(nWeapon);
	m_fReloadTimer = 0.0f;
	m_fFireDelayTimer = 0.0f;
}
void CWeapon::Update(float fElapsedTime)
{
	m_fReloadTimer += fElapsedTime;
	m_fFireDelayTimer += fElapsedTime;
}
//void CWeapon::Render(float fCamPosX, float fCamPosY)
//{
	

//}
void CWeapon::FireWeapon(CBase *pShooter)
{
	if(m_fReloadTime > m_fReloadTimer || m_fRateOfFire > m_fFireDelayTimer)
		return;
	if(m_nCurrMagazine == 0)
	{	
		m_fReloadTimer = 0.0f;

		if(m_nCurrAmmo == 0)
		{
			return;
		}
		else if(m_nCurrAmmo <= m_nMaxMagazine)
		{
			m_nCurrMagazine = m_nCurrAmmo;
			m_nCurrAmmo = 0;
		}
		else
		{
			m_nCurrMagazine = m_nMaxMagazine;
			m_nCurrAmmo -= m_nMaxMagazine;
		}
		return;
	}
	m_nCurrMagazine--;
	m_fFireDelayTimer = 0.0f;
	if( pShooter == CPlayer::GetInstance() )
	{
		CEventSystem::GetInstance()->SendEvent("big.bang", CPlayer::GetInstance());
	
		for(int i = 0; i < m_nNumBulletsFired; i++)
			CMessageSystem::GetInstance()->SendMsg(new CCreatePlayerBullet(CPlayer::GetInstance()));
	}
	else
	{
		for( int i = 0; i < m_nNumBulletsFired; i++ )
		{
			CMessageSystem::GetInstance()->SendMsg(new CCreateEnemyBullet((CBase*)pShooter));
		}
	}
}
void CWeapon::LoadWeapon(int nWeapon)
{
	TiXmlDocument doc;
	if(doc.LoadFile("Resource/Data/Weapons.xml") == false)
		return;

	TiXmlElement* pRoot = doc.RootElement();
	if(!pRoot)
		return;

	TiXmlElement* pWeaponAttribute;

	switch(nWeapon)
	{
	//case WEP_KNIFE:
	//	pWeaponAttribute = pRoot->FirstChildElement("knife");
	//	SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/Pistol.png"));
	//	break;
	case WEP_PISTOL:
		pWeaponAttribute = pRoot->FirstChildElement("pistol");
		SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/Pistol.png"));
		break;
	case WEP_MACHINEGUN:
		pWeaponAttribute = pRoot->FirstChildElement("machinegun");
		SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/MachineGun.png"));
		break;
	case WEP_RIFLE:
		pWeaponAttribute = pRoot->FirstChildElement("rifle");
		SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/Rifle.png"));
		break;
	case WEP_SHOTGUN:
		pWeaponAttribute = pRoot->FirstChildElement("shotgun");
		SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/Shotgun.png"));
		break;
	case WEP_BAZOOKA:
		pWeaponAttribute = pRoot->FirstChildElement("bazooka");
		SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/Bazooka.png"));
		break;
	case WEP_RYNOV:
		pWeaponAttribute = pRoot->FirstChildElement("rynov");
		SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/RynoV.png"));
		break;
	};

	double temp;

	pWeaponAttribute = pWeaponAttribute->FirstChildElement("m_nRange");
	pWeaponAttribute->Attribute("value", &this->m_nRange);
	pWeaponAttribute = pWeaponAttribute->NextSiblingElement("m_nDamage");
	pWeaponAttribute->Attribute("value", &this->m_nDamage);
	pWeaponAttribute = pWeaponAttribute->NextSiblingElement("m_nMaxAmmo");
	pWeaponAttribute->Attribute("value", &this->m_nMaxAmmo);
	m_nCurrAmmo = m_nMaxAmmo;
	pWeaponAttribute = pWeaponAttribute->NextSiblingElement("m_nWeaponID");
	pWeaponAttribute->Attribute("value", &this->m_nWeaponID);
	pWeaponAttribute = pWeaponAttribute->NextSiblingElement("m_nBulletID");
	pWeaponAttribute->Attribute("value", &this->m_nBulletID);
	pWeaponAttribute = pWeaponAttribute->NextSiblingElement("m_fAccuracy");
	pWeaponAttribute->Attribute("value", (&temp));
	this->m_fAccuracy = (float)(temp);
	pWeaponAttribute = pWeaponAttribute->NextSiblingElement("m_fRateOfFire");
	pWeaponAttribute->Attribute("value", &temp);
	this->m_fRateOfFire = (float)(temp);
	pWeaponAttribute = pWeaponAttribute->NextSiblingElement("m_nMaxMagazine");
	pWeaponAttribute->Attribute("value", &this->m_nMaxMagazine);
	m_nCurrMagazine = m_nMaxMagazine;
	pWeaponAttribute = pWeaponAttribute->NextSiblingElement("m_fReloadTime");
	pWeaponAttribute->Attribute("value", &temp);
	this->m_fReloadTime = (float)(temp);	
	pWeaponAttribute = pWeaponAttribute->NextSiblingElement("m_nBulletSpeed");
	pWeaponAttribute->Attribute("value", &this->m_nBulletSpeed);
	pWeaponAttribute = pWeaponAttribute->NextSiblingElement("m_nSoundDistance");
	pWeaponAttribute->Attribute("value", &this->m_nSoundDistance);
	pWeaponAttribute = pWeaponAttribute->NextSiblingElement("m_nNumBulletsFired");
	pWeaponAttribute->Attribute("value", &this->m_nNumBulletsFired);

	
}