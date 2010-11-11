#include "CHeavyInfantry.h"
#include "CEvent.h"
#include "CPlayer.h"
#include "CAttackState.h"
#include "CFleeState.h"
#include "CEventSystem.h"
#include "CMessageSystem.h"
#include "CBullet.h"

CHeavyInfantry::CHeavyInfantry(void) : CEnemy(WEP_PISTOL)
{
	SetEnemyID(ENEMY_HEAVY);
	SetMaxHealth(200);
	SetHealth(GetMaxHealth());
//	SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource\\Graphics\\HeavyInfantry_editor.png"));
	SetAnimation(CAnimationManager::GetInstance()->LoadAnimation("Resource\\Data\\Animations\\JeG_HeavyInfantry.bin"));
	GetAnimation()->currAnimation->Play();
	SetMoneyReward(25);
	SetRepReward(10);
	SetWidth(32);
	SetHeight(32);
	SetArmor(25);
	SetSpeed(25.0f);
	CEventSystem::GetInstance()->RegisterClient("big.bang",this);
	CEventSystem::GetInstance()->RegisterClient("form.up",this);
	CEventSystem::GetInstance()->RegisterClient("engage.player",this);
	CEventSystem::GetInstance()->RegisterClient("over.here",this);
	CEventSystem::GetInstance()->RegisterClient("player.detected",this);
	CEventSystem::GetInstance()->RegisterClient("fire.bullet",this);
}

CHeavyInfantry::~CHeavyInfantry(void)
{
	CEventSystem::GetInstance()->UnregisterClient("big.bang",this);
	CEventSystem::GetInstance()->UnregisterClient("form.up",this);
	CEventSystem::GetInstance()->UnregisterClient("engage.player",this);
	CEventSystem::GetInstance()->UnregisterClient("over.here",this);
	CEventSystem::GetInstance()->UnregisterClient("player.detected",this);
	CEventSystem::GetInstance()->UnregisterClient("fire.bullet",this);
}

void CHeavyInfantry::Update(float fElapsedTime)
{
	if( GetDead() == false )
	{
		// If the unit is either not in a squad or it has been issued the order to attack from the squad
		if( Attack() == true )
		{
			if( GetCalculate() == true )
			{
				GetState()->CalculateAI(fElapsedTime, this);
			}

			if( GetHealth() < GetMaxHealth() * 0.5f )
			{
				SetCalculate(false);
				tVector2D vectorToPlayer;
				vectorToPlayer.fX = GetTarget()->GetPosX() - GetPosX();
				vectorToPlayer.fY = GetTarget()->GetPosY() - GetPosY();
				vectorToPlayer = Vector2DNormalize(vectorToPlayer);
				SetVelX(vectorToPlayer.fX*(GetSpeed()*2));
				SetVelX(vectorToPlayer.fY*(GetSpeed()*2));
			}
		}

		// Set Facing
		if( GetVelX() > GetVelY() )
		{
			SetFacing(1.0f,0.0f);
		}
		else if( -GetVelX() < -GetVelY() )
		{
			SetFacing(-1.0f,0.0f);
		}
		else if( GetVelY() > GetVelX() )
		{
			SetFacing(0.0f,1.0f);
		}
		else if( -GetVelY() < -GetVelX() )
		{
			SetFacing(0.0f,-1.0f);
		}

		SetPosX(GetPosX()+(GetVelX()*fElapsedTime));
		SetPosY(GetPosY()+(GetVelY()*fElapsedTime));
	}

	CEnemy::Update(fElapsedTime);
}

void CHeavyInfantry::HandleEvent(CEvent* pEvent)
{
	if( pEvent->GetEventID() == "big.bang" && GetTarget() == NULL )
	{
		CPlayer* player = (CPlayer*)pEvent->GetParam();
		tVector2D distanceToPlayer;

		distanceToPlayer.fX = player->GetPosX()-GetPosX();
		distanceToPlayer.fY = player->GetPosY()-GetPosY();

		player->GetCurrWeapon();

		if( Vector2DLength(distanceToPlayer) <= player->GetCurrWeapon()->GetSoundDistance())
		{
			ChangeState(CAttackState::GetInstance());
			SetTarget(player);
			CEventSystem::GetInstance()->SendEvent("player.detected",this);
		}
	}
	if( pEvent->GetEventID() == "player.detected" && pEvent->GetParam() != this )
	{
		CEnemy* pEnemy = (CEnemy*)pEvent->GetParam();
		tVector2D toTarget;
		toTarget.fX = pEnemy->GetPosX() - GetPosX();
		toTarget.fY = pEnemy->GetPosY() - GetPosY();

		if( Vector2DLength(toTarget) < 200 )
		{
			CEventSystem::GetInstance()->SendEvent("join.squad",this);
		}
	}
	if( pEvent->GetEventID() == "form.up" )
	{
		SetAttack(false);
	}

	if( pEvent->GetEventID() == "engage.player")
	{
		SetAttack(true);
	}

	if( pEvent->GetEventID() == "fire.bullet" )
	{
		GetWeapon()->FireWeapon(this);
	}
}

bool CHeavyInfantry::CheckCollision( CBase *pBase )
{
	if( pBase->GetType() == OBJECT_PLAYER )
	{
		if(CBase::CheckCollision(pBase))
		{
			CPlayer::GetInstance()->SetPosX(CPlayer::GetInstance()->GetPosX()+GetVelX());
			CPlayer::GetInstance()->SetPosY(CPlayer::GetInstance()->GetPosY()+GetVelY());
		}
	}
	return CEnemy::CheckCollision(pBase);
}
/*
void CHeavyInfantry::Shoot(void)
{
	if( GetFacing().fX == 1.0f )
	{
		if( GetAnimation() != NULL )
		{
			SetCurrAnimation("FireRight");
		}
	}
	else if( GetFacing().fX == -1.0f )
	{
		if( GetAnimation() != NULL )
		{
			SetCurrAnimation("FireLeft");
		}
	}
	else if( GetFacing().fY == 1.0f )
	{
		if( GetAnimation() != NULL )
		{
			SetCurrAnimation("FireDown");
		}
	}
	else if( GetFacing().fY == -1.0f )
	{
		if( GetAnimation() != NULL )
		{
			SetCurrAnimation("FireUp");
		}
	}
}

void CHeavyInfantry::Walk(void)
{
	if( GetFacing().fX == 1.0f )
	{
		if( GetAnimation() != NULL )
		{
			SetCurrAnimation("WalkRight");
		}
	}
	else if( GetFacing().fX == -1.0f )
	{
		if( GetAnimation() != NULL )
		{
			SetCurrAnimation("WalkLeft");
		}
	}
	else if( GetFacing().fY == 1.0f )
	{
		if( GetAnimation() != NULL )
		{
			SetCurrAnimation("WalkDown");
		}
	}
	else if( GetFacing().fY == -1.0f )
	{
		if( GetAnimation() != NULL )
		{
			SetCurrAnimation("WalkUp");
		}
	}
}*/