#ifndef CBULLET_H_
#define CBULLET_H_

#include "CBase.h"

class CEvent;

class CBullet : public CBase
{
	float	m_fRotation;
	CBase*	m_pOwner;
	int		m_nDamage;
	int		m_nWeaponID;

public:
	CBullet(void);
	~CBullet(void);

	virtual void Update( float fElapsedTime );
	virtual void Render( float fCamPosX, float fCamPosY );

	float GetRotation( void ) { return m_fRotation; }
	int GetDamage( void ) { return m_nDamage; }
	CBase* GetOwner(void) { return m_pOwner; }
	int GetWeaponID(void) { return m_nWeaponID; }

	void SetRotation( float fRotation ) { m_fRotation = fRotation; }
	void SetOwner( CBase* pOwner ) { m_pOwner = pOwner; }
	void SetDamage( int nDamage ) { m_nDamage = nDamage; }
	void SetWeaponID( int nWeaponID ) { m_nWeaponID = nWeaponID; }

	RECT GetRect( void );
	bool CheckCollision(CBase* pBase);

	void HandleEvent( CEvent* pEvent );
};
#endif