#include "CLightInfantry.h"
#include "CEvent.h"
#include "CPlayer.h"
#include "CAttackState.h"
#include "CFleeState.h"
#include "CEventSystem.h"
#include "CMessageSystem.h"

CLightInfantry::CLightInfantry(void) : CEnemy(WEP_MACHINEGUN)
{
	SetEnemyID(ENEMY_LIGHT);
	SetMaxHealth(100);
	SetHealth(GetMaxHealth());
	SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource\\Graphics\\LightInfantry_editor.png"));
//	SetAnimation(CAnimationManager::GetInstance()->LoadAnimation("Resource\\Data\\Animations\\JeG_LightInfantry.bin"));
//	GetAnimation()->currAnimation->Play();
	SetMoneyReward(5);
	SetRepReward(1);
	SetWidth(32);
	SetHeight(32);
	SetArmor(5);
	SetSpeed(50.0f);
	CEventSystem::GetInstance()->RegisterClient("big.bang",this);
	CEventSystem::GetInstance()->RegisterClient("form.up",this);
	CEventSystem::GetInstance()->RegisterClient("engage.player",this);
	CEventSystem::GetInstance()->RegisterClient("over.here",this);
	CEventSystem::GetInstance()->RegisterClient("fire.bullet",this);
}

CLightInfantry::~CLightInfantry(void)
{
	CAnimationManager::GetInstance()->UnloadAnimation(GetAnimation());
	CEventSystem::GetInstance()->UnregisterClient("big.bang",this);
	CEventSystem::GetInstance()->UnregisterClient("form.up",this);
	CEventSystem::GetInstance()->UnregisterClient("engage.player",this);
	CEventSystem::GetInstance()->UnregisterClient("over.here",this);
	CEventSystem::GetInstance()->UnregisterClient("fire.bullet",this);
}

void CLightInfantry::Update(float fElapsedTime)
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
				ChangeState(CFleeState::GetInstance());
			}
		}

		// Set Facing
		if( abs(GetVelX()) > abs(GetVelY()) )
		{
			if( GetVelX() > 0 )
				SetFacing(1.0f,0.0f);
			else
				SetFacing(-1.0f,0.0f);
		}
		if( abs(GetVelY()) > abs(GetVelX()) )
		{
			if( GetVelY() > 0 )
				SetFacing(0.0f,1.0f);
			else
				SetFacing(0.0f,-1.0f);
		}

		SetPosX(GetPosX()+(GetVelX()*fElapsedTime));
		SetPosY(GetPosY()+(GetVelY()*fElapsedTime));
	}

	CEnemy::Update(fElapsedTime);
}

void CLightInfantry::HandleEvent(CEvent* pEvent)
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

	if( this->GetState() == CFleeState::GetInstance() && pEvent->GetEventID() == "over.here" )
	{
		CBase* newTarget = (CBase*)pEvent->GetParam();

		if( newTarget != this && newTarget->GetType() != OBJECT_CURSOR && newTarget->GetType() != OBJECT_ALLY )
		{
			if( GetTarget() == NULL || GetTarget()->GetType() == OBJECT_PLAYER )
			{
				SetTarget(newTarget);
			}
			else if( newTarget->GetType() == OBJECT_BASE )
			{
				tVector2D distanceToTarget;
				tVector2D distanceToNewTarget;

				distanceToTarget.fX = GetTarget()->GetPosX() - GetPosX();
				distanceToTarget.fY = GetTarget()->GetPosY() - GetPosY();

				distanceToNewTarget.fX = newTarget->GetPosX() - GetPosX();
				distanceToNewTarget.fY = newTarget->GetPosY() - GetPosY();

				if( Vector2DLength(distanceToNewTarget) < Vector2DLength(distanceToTarget) )
				{
					SetTarget(newTarget);
				}
			}
		}
	}
}

bool CLightInfantry::CheckCollision( CBase *pBase )
{
	return CEnemy::CheckCollision(pBase);
}

void CLightInfantry::Shoot(void)
{
	if( GetFacing().fX == 1.0f )
	{
		if( GetAnimation() != NULL )
		{
			SetCurrAnimation("FireRight");
			GetAnimation()->currAnimation->Play();
		}
	}
	else if( GetFacing().fX == -1.0f )
	{
		if( GetAnimation() != NULL )
		{
			SetCurrAnimation("FireLeft");
			GetAnimation()->currAnimation->Play();
		}
	}
//	else if( GetFacing().fY == 1.0f )
//	{
//		if( GetAnimation() != NULL )
//		{
//			SetCurrAnimation("LI Shoot");
//			GetAnimation()->currAnimation->Play();
//		}
//	}
//	else if( GetFacing().fY == -1.0f )
//	{
//		if( GetAnimation() != NULL )
//		{
//			SetCurrAnimation("LI Up Shoot");
//			GetAnimation()->currAnimation->Play();
//		}
//	}
}

void CLightInfantry::Walk(void)
{
	if( GetFacing().fX == 1.0f )
	{
		if( GetAnimation() != NULL )
		{
			SetCurrAnimation("WalkRight");
			GetAnimation()->currAnimation->Play();
		}
	}
	else if( GetFacing().fX == -1.0f )
	{
		if( GetAnimation() != NULL )
		{
			SetCurrAnimation("WalkLeft");
			GetAnimation()->currAnimation->Play();
		}
	}
	else if( GetFacing().fY == 1.0f )
	{
		if( GetAnimation() != NULL )
		{
			SetCurrAnimation("WalkDown");
			GetAnimation()->currAnimation->Play();
		}
	}
	else if( GetFacing().fY == -1.0f )
	{
		if( GetAnimation() != NULL )
		{
			SetCurrAnimation("WalkUp");
			GetAnimation()->currAnimation->Play();
		}
	}
}