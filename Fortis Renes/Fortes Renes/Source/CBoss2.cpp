#include "CBoss2.h"
#include "CParticle.h"
#include "CGamePlayState.h"
#include "CPlayer.h"
#include "CIdleState.h"
#include "CAttackState.h"
#include "CEventSystem.h"
#include "CMessageSystem.h"

CBoss2::CBoss2(void) : CEnemy(WEP_RYNOV)
{
	SetType(OBJECT_ENEMY);
	SetEnemyID(ENEMY_BOSS);
//	SetImageID(CSGD_TxtureManager::GetInstance()->LoadTexture("Resource/Graphics/SaT_BossTwo.png", D3DCOLOR_XRGB(255,255,255)));
//	SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/SaT_BossTwo.png", D3DCOLOR_XRGB(255,255,255)));
	SetAnimation(CAnimationManager::GetInstance()->LoadAnimation("Resource\\Data\\Animations\\JeG_Boss2.bin"));
	GetAnimation()->currAnimation->Play();
	SetMoneyReward(100);
	SetRepReward(50);
	SetWidth(40);
	SetHeight(70);
	SetVelX(0.0f);
	SetVelY(0.0f);
	SetArmor(0);
	SetHealth(100);
	m_vDirection.fX = 0.0f;
	m_vDirection.fY = 1.0f;
	SetSpeed(50.0f);

	// Spot 1
	Spot1.fX = GetPosX() + 150.0f;
	Spot1.fY = GetPosY();
	// Spot 2
	Spot2.fX = GetPosX() + 200.0f;
	Spot2.fY = GetPosY() + 200.0f;
	// Spot 3
	Spot3.fX = GetPosX() + 100.0f;
	Spot3.fY = GetPosY() + 400.0f;

	m_fCounter = 10.0f;
	uno = true;
	dos = false;
	tres = false;

	los.left = (LONG)((GetPosX() + GetWidth()*0.5f) - 200.0f);
	los.top = (LONG)((GetPosY() + GetHeight()*0.5f) - 200.0f);
	los.right = (LONG)(los.left + 400.0f);
	los.bottom = (LONG)(los.top + 400.0f);
	once = true;
}

CBoss2::~CBoss2(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(GetImageID());
}

void CBoss2::Update(float fElapsedTime)
{
	if( GetHealth() < 0 )
	{
		SetDead(true);
		CEventSystem::GetInstance()->SendEvent("end.level");
		CMessageSystem::GetInstance()->SendMsg( new CDestroyEnemy(this));
	}

	m_fCounter -= fElapsedTime;

	los.left = (LONG)((GetPosX() + GetWidth()*0.5f) - 200.0f);
	los.top = (LONG)((GetPosY() + GetHeight()*0.5f) - 200.0f);
	los.right = (LONG)(los.left + 400.0f);
	los.bottom = (LONG)(los.top + 400.0f);

	if( GetDead() == false )
	{
		if(m_fCounter < 0)
		{
			if(uno == true && dos == false && tres == false)
			{
				tVector2D temp;
				temp.fX = Spot1.fX - GetPosX();
				temp.fY = Spot1.fY - GetPosY();
				temp = Vector2DNormalize(temp);
				SetVelX(temp.fX * GetSpeed());
				SetVelY(temp.fY * GetSpeed());
				uno = false;
				dos = true;
				tres = false;
			}
			else if(uno == false && dos == true && tres == false)
			{
				tVector2D temp;
				temp.fX = Spot2.fX - GetPosX();
				temp.fY = Spot2.fY - GetPosY();
				temp = Vector2DNormalize(temp);
				SetVelX(temp.fX * GetSpeed());
				SetVelY(temp.fY * GetSpeed());
				uno = false;
				dos = false;
				tres = true;
			}
			else if(uno == false && dos == false && tres == true)
			{
				tVector2D temp;
				temp.fX = Spot3.fX - GetPosX();
				temp.fY = Spot3.fY - GetPosY();
				temp = Vector2DNormalize(temp);
				SetVelX(temp.fX * GetSpeed());
				SetVelY(temp.fY * GetSpeed());
				uno = true;
				dos = false;
				tres = false;
			}

			m_fCounter = 5.0f;
		}

		CPlayer* pPlayer = CPlayer::GetInstance();

		if(IntersectRect(&empty, &los, &pPlayer->GetRect()))
		{
			if(once)
			{
				once = !once;
			}
		}
		else
//			CGamePlayState::GetInstance()->GetEmitter().pop_back();
	
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

		SetPosX(GetPosX() + GetVelX() * fElapsedTime);
		SetPosY(GetPosY() + GetVelY() * fElapsedTime);
	}
}

void CBoss2::Render(float fCamPosX, float fCamPosY)
{
	CEnemy::Render(fCamPosX,fCamPosY);
}

void CBoss2::HandleEvent(CEvent* pEvent)
{
}
