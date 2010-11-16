#include "CBoss3.h"
#include "CPlayer.h"
#include "CWeapon.h"
#include "CAttackState.h"
#include "CIdleState.h"
#include "CObjectManager.h"
#include "CCamera.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"
#include "CBitmapFont.h"
#include "CEventSystem.h"
#include "CMessageSystem.h"

CBoss3::CBoss3(void) : CEnemy(WEP_RIFLE)
{
	SetType(OBJECT_ENEMY);
	SetEnemyID(ENEMY_BOSS);
	SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/SaT_BossThree.png", D3DCOLOR_XRGB(255,255,255)));
	SetAnimation(CAnimationManager::GetInstance()->LoadAnimation("Resource\\Data\\Animations\\JeG_Boss3.bin"));
	GetAnimation()->currAnimation->Play();
	SetMoneyReward(100);
	SetRepReward(50);
	SetPosX(900);
	SetPosY(300);
	SetWidth(38);
	SetHeight(66);
	SetVelX(0.0f);
	SetVelY(0.0f);
	SetArmor(0);
	SetHealth(100);
	m_vDirection.fX = 0.0f;
	m_vDirection.fY = 1.0f;
	tankmode = false;
	m_fRot = 0.0f;

	los.left = (LONG)((GetPosX() + GetWidth()*0.5f) - 350.0f);
	los.top = (LONG)((GetPosY() + GetHeight()*0.5f) - 350.0f);
	los.right = (LONG)(los.left + 700.0f);
	los.bottom = (LONG)(los.top + 700.0f);
}

CBoss3::~CBoss3(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(GetImageID());
}

void CBoss3::Update(float fElapsedTime)
{
	los.left = (LONG)((GetPosX() + GetWidth()*0.5f) - 350.0f);
	los.top = (LONG)((GetPosY() + GetHeight()*0.5f) - 350.0f);
	los.right = (LONG)(los.left + 700.0f);
	los.bottom = (LONG)(los.top + 700.0f);

	if( GetHealth() < 0 )
	{
		SetDead(true);
		CEventSystem::GetInstance()->SendEvent("end.level");
		CMessageSystem::GetInstance()->SendMsg( new CDestroyEnemy(this));
	}

	if( GetDead() == false )
	{
		if(GetHealth() < 75)
		{

			if(GetHealth() > 75 && GetHealth() <= 100)
			{
				SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/SaT_BossThree.png"));
				SetWidth(38);
				SetHeight(66);
				GetWeapon()->LoadWeapon(WEP_RIFLE);
				tankmode = false;
			}

			if(GetHealth() > 50 && GetHealth() <= 75)
			{
				SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/Idle Tank.png", D3DCOLOR_XRGB(255,0,255)));
				SetWidth(64);
				SetHeight(64);
				GetWeapon()->LoadWeapon(WEP_RYNOV);
				// Rotation
				tVector2D vDirection;
				tVector2D player;
				player.fX = 0.0f;
				player.fY = -1.0f;
				vDirection.fX = ((CPlayer::GetInstance()->GetPosX() - GetPosX()));
				vDirection.fY = ((CPlayer::GetInstance()->GetPosY() - GetPosY()));
				vDirection = Vector2DNormalize(vDirection);

				m_fRot = AngleBetweenVectors(player, vDirection);
				if(CPlayer::GetInstance()->GetPosX() < GetPosX())
					m_fRot = -m_fRot;

				tankmode = true;
			}

			if(GetHealth() <= 50 && GetHealth() > 25)
			{
				SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/SaT_BossThree.png"));
				SetWidth(38);
				SetHeight(66);
				GetWeapon()->LoadWeapon(WEP_RIFLE);
				tankmode = false;
			}

			if(GetHealth() > 0 && GetHealth() <= 25)
			{
				SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/Idle Tank.png", D3DCOLOR_XRGB(255,0,255)));
				SetWidth(64);
				SetHeight(64);
				GetWeapon()->LoadWeapon(WEP_RYNOV);
				// Rotation
				tVector2D vDirection;
				tVector2D player;
				player.fX = 0.0f;
				player.fY = -1.0f;
				vDirection.fX = ((CPlayer::GetInstance()->GetPosX() - GetPosX()));
				vDirection.fY = ((CPlayer::GetInstance()->GetPosY() - GetPosY()));
				vDirection = Vector2DNormalize(vDirection);

				m_fRot = AngleBetweenVectors(player, vDirection);
				if(CPlayer::GetInstance()->GetPosX() < GetPosX())
					m_fRot = -m_fRot;
				tankmode = true;
			}
		}

		CPlayer* pPlayer = CPlayer::GetInstance();

		if(IntersectRect(&empty, &los, &pPlayer->GetRect()))
		{
			SetAttack(true);
			SetTarget(pPlayer);
		}
		else
			SetAttack(false);

		if(Attack())
		{
			ChangeState(CAttackState::GetInstance());
		}
		else
		{
			ChangeState(CIdleState::GetInstance());
		}

		GetState()->CalculateAI(fElapsedTime, this);

		if(GetVelX() > 50.0f)
			SetVelX(50.0f);
		if(GetVelY() > 50.0f)
			SetVelY(50.0f);

		if(GetVelX() < -50.0f)
			SetVelX(-50.0f);
		if(GetVelY() < -50.0f)
			SetVelY(-50.0f);
	}

	//SetPosX(GetPosX() - GetVelX() * fElapsedTime);
	//SetPosY(GetPosY() - GetVelY() * fElapsedTime);
}

void CBoss3::Render(float fCamPosX, float fCamPosY)
{
	RECT boss = {0,0,38,66};
	if(!tankmode)
	{
		CEnemy::Render(fCamPosX,fCamPosY);
	}
	else
	{
		CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)((GetPosX() - GetWidth()*0.5f) - fCamPosX), 
						(int)((GetPosY() - GetHeight() *0.5f) - fCamPosY), 1.0f, 1.0f, 0, GetWidth()*0.5f, GetHeight()*0.5f, m_fRot);
	
	}
}

void CBoss3::HandleEvent(CEvent* pEvent)
{
}