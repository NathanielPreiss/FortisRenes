#include "CBoss1.h"
#include "CPlayer.h"
#include "CIdleState.h"
#include "CAttackState.h"
#include "CBase.h"
#include "CAlly.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"
#include "CObjectManager.h"
#include "CEventSystem.h"
#include "CMessageSystem.h"

CBoss1::CBoss1(void) : CEnemy(WEP_RIFLE)
{
	SetType(OBJECT_ENEMY);
	SetEnemyID(ENEMY_BOSS);
	SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/SaT_BossOne.png", D3DCOLOR_XRGB(255,255,255)));
	SetMoneyReward(100);
	SetRepReward(50);
	SetWidth(40);
	SetHeight(70);
	SetVelX(0.0f);
	SetVelY(0.0f);
	SetHealth(100);
	SetArmor(0);
	m_vDirection.fX = 0.0f;
	m_vDirection.fY = 1.0f;
	SetAnimation(0);
	m_fCounter = 0.5f;
	m_fDestroyCounter = 7.0f;
	m_bForCounter = false;
	bomb = new CBase();
	bomb2 = new CBase();
	bomb3 = new CBase();

	bomb->SetPosX(550.0f);
	bomb->SetPosY(270.0f);
	bomb->SetWidth(32);
	bomb->SetHeight(32);
	bomb->SetHealth(1);
	bomb->SetArmor(0);
	bomb->SetType(OBJECT_BOMB);
	bomb->SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/Object Sprites/JeG_Bomb.png", D3DCOLOR_XRGB(0,255,0)));

	bomb2->SetPosX(500.0f);
	bomb2->SetPosY(320.0f);
	bomb2->SetWidth(32);
	bomb2->SetHeight(32);
	bomb2->SetHealth(1);
	bomb2->SetArmor(0);
	bomb2->SetType(OBJECT_BOMB);
	bomb2->SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/Object Sprites/JeG_Bomb.png", D3DCOLOR_XRGB(0,255,0)));

	bomb3->SetPosX(450.0f);
	bomb3->SetPosY(270.0f);
	bomb3->SetWidth(32);
	bomb3->SetHeight(32);
	bomb3->SetHealth(1);
	bomb3->SetArmor(0);
	bomb3->SetType(OBJECT_BOMB);
	bomb3->SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/Object Sprites/JeG_Bomb.png", D3DCOLOR_XRGB(0,255,0)));

	los.left = (LONG)((GetPosX() + GetWidth()*0.5f) - 250.0f);
	los.top = (LONG)((GetPosY() + GetHeight()*0.5f) - 250.0f);
	los.right = (LONG)(los.left + 700.0f);
	los.bottom = (LONG)(los.top + 700.0f);
}

CBoss1::~CBoss1(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(GetImageID());
	delete bomb;
	delete bomb2;
	delete bomb3;
}

void CBoss1::Update(float fElapsedTime)
{
	if( GetHealth() < 0 )
	{
		SetDead(true);
		CEventSystem::GetInstance()->SendEvent("end.level");
		CMessageSystem::GetInstance()->SendMsg( new CDestroyEnemy(this));
	}


	los.left = (LONG)((GetPosX() + GetWidth()*0.5f) - 250.0f);
	los.top = (LONG)((GetPosY() + GetHeight()*0.5f) - 250.0f);
	los.right = (LONG)(los.left + 700.0f);
	los.bottom = (LONG)(los.top + 700.0f);

	m_fCounter -= fElapsedTime;
	if(m_bForCounter)
		m_fDestroyCounter -= fElapsedTime;

	if( GetDead() == false )
	{
		CPlayer* pPlayer = CPlayer::GetInstance();

		if(IntersectRect(&empty, &los, &pPlayer->GetRect()))
		{
			SetAttack(true);
			SetTarget(pPlayer);
		}
		else
			SetAttack(false);

		GetState()->CalculateAI(fElapsedTime, this);

		if(Attack())
		{
			ChangeState(CAttackState::GetInstance());
		}
		else
		{
			ChangeState(CIdleState::GetInstance());
		}

		if(GetVelX() > 100.0f)
			SetVelX(100.0f);
		if(GetVelY() > 100.0f)
			SetVelY(100.0f);

		if(GetVelX() < -100.0f)
			SetVelX(-100.0f);
		if(GetVelY() < -100.0f)
			SetVelY(-100.0f);

		SetPosX(GetPosX() - GetVelX() * fElapsedTime);
		SetPosY(GetPosY() - GetVelY() * fElapsedTime);

//		if(GetHealth() < 75)
//		{
//			// Spawn Bombs next to Ally
//			if(m_fCounter < 0)
//			{
//				if(m_fDestroyCounter > 0)
//				{
//					bomb->SetHealth(1);
//					bomb2->SetHealth(1);
//					bomb3->SetHealth(1);
//					CObjectManager::GetInstance()->AddObject(bomb);
//					CObjectManager::GetInstance()->AddObject(bomb2);
//					CObjectManager::GetInstance()->AddObject(bomb3);
//					m_bForCounter = true;
//				}
//				m_fCounter = 14.0f;
//			}
//
//			if(m_fDestroyCounter < 0)
//			{
//				// Destroy Bombs
//				CObjectManager::GetInstance()->RemoveObject(bomb);
//				CObjectManager::GetInstance()->RemoveObject(bomb2);
//				CObjectManager::GetInstance()->RemoveObject(bomb3);
//				m_fDestroyCounter = 7.0f;
//				m_bForCounter = false;
//			}
//		}
//
//		if(bomb->GetHealth() < 0)
//		{
//			CObjectManager::GetInstance()->RemoveObject(bomb);
//		}
//
//		if(bomb2->GetHealth() < 0)
//		{
//			CObjectManager::GetInstance()->RemoveObject(bomb2);
//		}
//
//		if(bomb3->GetHealth() < 0)
//		{
//			CObjectManager::GetInstance()->RemoveObject(bomb3);
//		}
	}
}

void CBoss1::Render(float fCamPosX, float fCamPosY)
{
	//RECT tempRect = los;
	//tempRect.top -= fCamPosY;
	//tempRect.left -= fCamPosX;
	//tempRect.right = tempRect.left + GetWidth();
	//tempRect.bottom = tempRect.top + GetHeight();

	RECT boss = {0,0,45,70};

	CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)((GetPosX() - GetWidth()*0.5f) - fCamPosX), 
								(int)((GetPosY() - GetHeight() *0.5f) - fCamPosY), 1.0f, 1.0f, &boss, GetWidth()*0.5f, GetHeight()*0.5f, 0);

	//CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
	//CSGD_Direct3D::GetInstance()->DrawRect(tempRect, 255,0,0);
}

void CBoss1::HandleEvent(CEvent* pEvent)
{
}

bool CBoss1::CheckCollision( CBase *pBase )
{
	return CEnemy::CheckCollision(pBase);
}