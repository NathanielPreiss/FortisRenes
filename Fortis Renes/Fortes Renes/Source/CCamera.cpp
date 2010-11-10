#include "CCamera.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"
#include "CObjectManager.h"

CCamera::CCamera(void)
{
	m_fPosX = 0;
	m_fPosY = 0;
	m_fShakeTimer = 1.0f;
}
CCamera::~CCamera(void)
{
}

void CCamera::SetBoundaries()
{
	m_nMinX = (int)(CSGD_Direct3D::GetInstance()->GetPresentParams()->BackBufferWidth*0.5f);
	m_nMinY = (int)(CSGD_Direct3D::GetInstance()->GetPresentParams()->BackBufferHeight*0.5f);
	m_nMaxX = (int)((CObjectManager::GetInstance()->GetMap()->MapRow*CObjectManager::GetInstance()->GetMap()->MapTileSize) - CSGD_Direct3D::GetInstance()->GetPresentParams()->BackBufferWidth*0.5f);
	m_nMaxY = (int)((CObjectManager::GetInstance()->GetMap()->MapColumn*CObjectManager::GetInstance()->GetMap()->MapTileSize) - CSGD_Direct3D::GetInstance()->GetPresentParams()->BackBufferHeight*0.5f);
}

CCamera* CCamera::GetInstance(void)
{
	static CCamera instance;
	return &instance;
}

void CCamera::UpdateCameraPos( float fFocusX, float fFocusY)
{
	if( m_bShake == false )
	{
		if(fFocusX < m_nMinX)
			m_fPosX = 0.0f;
		else if(fFocusX > m_nMaxX)
			m_fPosX = (float)(m_nMaxX - m_nMinX);
		else
			m_fPosX = fFocusX - m_nMinX;
	
		if(fFocusY < m_nMinY)
			m_fPosY = 0.0f;
		else if(fFocusY > m_nMaxY)
			m_fPosY = (float)(m_nMaxY - m_nMinY);
		else
			m_fPosY = (float)(fFocusY - m_nMinY);
	}
}

void CCamera::Update(float fElapsedTime)
{
	if( m_bShake == true )
	{
		m_fTimeBucket += fElapsedTime;

		if( m_fTimeBucket > m_fShakeTimer )
			m_bShake = false;

		SetPosX(GetPosX() + (rand()%40-20));
		SetPosY(GetPosY() + (rand()%40-20));
	}
}