#include "CFinalBoss.h"
#include "CPlayer.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "CIdleState.h"
#include "CAttackState.h"
#include "CBullet.h"
#include "CEventSystem.h"
#include "CMessageSystem.h"

CFinalBoss::CFinalBoss(void) : CEnemy(WEP_RIFLE)
{
	SetType(OBJECT_ENEMY);
	SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/NaP_Gundam.png"));
	SetMoneyReward(100);
	SetRepReward(50);
	SetWidth(32);
	SetHeight(32);
	SetVelX(0.0f);
	SetVelY(0.0f);
	SetHealth(20000);
	SetArmor(50);
	m_vDirection.fX = 0.0f;
	m_vDirection.fY = 1.0f;
	SetAnimation(0);
	m_nPhase = 1;

	los.left = (LONG)((GetPosX() + GetWidth()*0.5f) - 250.0f);
	los.top = (LONG)((GetPosY() + GetHeight()*0.5f) - 250.0f);
	los.right = (LONG)(los.left + 500.0f);
	los.bottom = (LONG)(los.top + 500.0f);
}

CFinalBoss::~CFinalBoss(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(GetImageID());
}

void CFinalBoss::Update(float fElapsedTime)
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

		if(Attack())
		{
			ChangeState(CAttackState::GetInstance());
		}
		else
		{
			//ChangeState(CIdleState::GetInstance());
		}

		GetState()->CalculateAI(fElapsedTime, this);

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

		if(m_nPhase < 2)
			SetHealth(100);
	}
}

void CFinalBoss::Render(float fCamPosX, float fCamPosY)
{
	CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)((GetPosX() - GetWidth()*0.5f) - fCamPosX), 
								(int)((GetPosY() - GetHeight() *0.5f) - fCamPosY), 1.0f, 1.0f, 0, GetWidth()*0.5f, GetHeight()*0.5f, 0);
}

void CFinalBoss::HandleEvent(CEvent* pEvent)
{
	if(pEvent->GetEventID() == "Increment.Phase" && pEvent->GetParam() == this)
	{
		m_nPhase++;
	}
}