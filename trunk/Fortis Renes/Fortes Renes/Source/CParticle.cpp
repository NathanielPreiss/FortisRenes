#include "CParticle.h"
#include "CEmitter.h"
#include "CCamera.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"
#include <fstream>

CParticle::CParticle(void)
{
	m_nPosX = 0;
	m_nPosY = 0;
	m_nImageID = 0;
	m_fLife = 0.0f;
	m_fScale = 0.0f;
	m_fVelX = 0.0f;
	m_fVelY = 0.0f;
	m_nSourceBlend = 0;
	m_nDestinationBlend = 0;

	m_dwColor = 0;
	m_nAlpha = 255;
	m_nRed = 255;
	m_nGreen = 255;
	m_nBlue = 255;
}

void CParticle::Update(float fElapstedTime)
{
	m_dwColor = D3DCOLOR_ARGB(m_nAlpha, m_nRed, m_nGreen, m_nBlue);
}

void CParticle::Render(void)
{
	RECT empty = {0,0,30,30};
	
	CSGD_TextureManager::GetInstance()->Draw(m_nImageID, (int)(m_nPosX - CCamera::GetInstance()->GetPosX()), (int)(m_nPosY - CCamera::GetInstance()->GetPosY()), m_fScale, m_fScale, &empty, 0.0f, 0.0f, 0.0f, m_dwColor);
}
void CParticle::SetColor(int nA, int nR, int nG, int nB) 
{
		m_nAlpha = nA;
		m_nRed = nR;
		m_nGreen = nG;
		m_nBlue = nB;
		m_dwColor = D3DCOLOR_ARGB(nA,nR,nG,nB);
}