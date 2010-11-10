#include "CEnemySquad.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include "CAttackState.h"

CEnemySquad::CEnemySquad(void)
{
	m_fTimeBucket = 0.0f;
	m_fGroupUpTime = 0.5f;
	m_fAttackTimer = 2.5f;
	CEventSystem::GetInstance()->RegisterClient("player.detected",this);
	CEventSystem::GetInstance()->RegisterClient("enemy.died",this);
	CEventSystem::GetInstance()->RegisterClient("join.squad",this);
}

CEnemySquad::~CEnemySquad(void)
{
	CEventSystem::GetInstance()->UnregisterClient("player.detected",this);
	CEventSystem::GetInstance()->UnregisterClient("join.squad",this);
	CEventSystem::GetInstance()->UnregisterClient("enemy.died",this);
}

CEnemySquad* CEnemySquad::GetInstance(void)
{
	static CEnemySquad instance;
	return &instance;
}

void CEnemySquad::Update(float fElapsedTime)
{
	m_fTimeBucket += fElapsedTime;
	if( m_fTimeBucket > m_fGroupUpTime )
	{
		if( m_vSquad.size() == 1 )
		{
			CEventSystem::GetInstance()->SendEvent("engage.player");
			EmptySquad();
			return;
		}
	}

	if( m_fTimeBucket > m_fAttackTimer )
	{
		CEventSystem::GetInstance()->SendEvent("engage.player");
		EmptySquad();
	}
	else if( m_pLeader != NULL )
	{	
		// Set Up a vector to the player
		tVector2D toPlayer;
		toPlayer.fX = CPlayer::GetInstance()->GetPosX() - m_pLeader->GetPosX();
		toPlayer.fY = CPlayer::GetInstance()->GetPosY() - m_pLeader->GetPosY();

		// Loop through th e squad and issue commands based on enemy type
		for( unsigned int index = 0; index < m_vSquad.size(); index++ )
		{
			if( m_vSquad[index] != NULL )
			{
				switch(m_vSquad[index]->GetEnemyID())
				{
				case ENEMY_LIGHT:
					{
						tVector2D targetPosition = toPlayer;
						if( m_vSquad[index]->GetPosX() < CPlayer::GetInstance()->GetPosX() )
							targetPosition.fX -= 100.0f;
						else
							targetPosition.fX += 100.0f;

						targetPosition = Vector2DNormalize(targetPosition);
						m_vSquad[index]->SetVelX(targetPosition.fX * m_vSquad[index]->GetSpeed());
						m_vSquad[index]->SetVelY(targetPosition.fY * m_vSquad[index]->GetSpeed());
					}
					break;
				case ENEMY_MEDIUM:
					{
						tVector2D targetPosition = toPlayer;
						if( m_vSquad[index]->GetPosX() < CPlayer::GetInstance()->GetPosX() )
							targetPosition.fX -= 100.0f;
						else
							targetPosition.fX += 100.0f;

						targetPosition = Vector2DNormalize(targetPosition);
						m_vSquad[index]->SetVelX(targetPosition.fX * m_vSquad[index]->GetSpeed());
						m_vSquad[index]->SetVelY(targetPosition.fY * m_vSquad[index]->GetSpeed());
					}
					break;
				case ENEMY_HEAVY:
					{
						tVector2D targetPosition = toPlayer;

						targetPosition = Vector2DNormalize(targetPosition);
						m_vSquad[index]->SetVelX(targetPosition.fX * m_vSquad[index]->GetSpeed());
						m_vSquad[index]->SetVelY(targetPosition.fY * m_vSquad[index]->GetSpeed());
					}
					break;
				};
			}
		}
		CEventSystem::GetInstance()->SendEvent("form.up");
	}
}

void CEnemySquad::EmptySquad(void)
{
	m_pLeader = NULL;
	m_vSquad.clear();
}

void CEnemySquad::HandleEvent(CEvent* pEvent)
{
	if( pEvent->GetEventID() == "player.detected" )
	{
		m_fTimeBucket = 0.0f;
		CEnemy* pEnemy = (CEnemy*)pEvent->GetParam();

		pEnemy->SetTarget(CPlayer::GetInstance());
		pEnemy->ChangeState(CAttackState::GetInstance());

		m_pLeader = pEnemy;

		m_vSquad.push_back(pEnemy);
		CEventSystem::GetInstance()->SendEvent("form.up");
	}
	if( pEvent->GetEventID() == "join.squad" )
	{
		CEnemy* pEnemy = (CEnemy*)pEvent->GetParam();

		pEnemy->SetTarget(CPlayer::GetInstance());
		pEnemy->ChangeState(CAttackState::GetInstance());

		if( pEnemy->GetEnemyID() > m_pLeader->GetEnemyID() )
		{
			m_pLeader = pEnemy;
		}

		m_vSquad.push_back(pEnemy);
		CEventSystem::GetInstance()->SendEvent("form.up");
	}
	if( pEvent->GetEventID() == "enemy.died" )
	{
		for( unsigned int index = 0; index < m_vSquad.size(); index++ )
		{
			if( m_vSquad[index] == pEvent->GetParam() )
			{
				m_vSquad[index] = NULL;
			}
		}
	}
}