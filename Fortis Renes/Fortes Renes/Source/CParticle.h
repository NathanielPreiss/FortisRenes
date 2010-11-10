#ifndef CPARTICLE_H_
#define CPARTICLE_H_
#include <windows.h>

#include <string>
using namespace std;

#include "CBullet.h"
class CEmitter;

class CParticle : public CBullet
{
private:
	
	int m_nPosX;
	int m_nPosY;
	int m_nImageID;
	int m_nSourceBlend;
	int m_nDestinationBlend;
	DWORD m_dwColor;
	int m_nAlpha, m_nRed, m_nGreen, m_nBlue;
	float m_fLife;
	float m_fScale;
	float m_fVelX;
	float m_fVelY;

public:
	CParticle(void);

	// Mutators
	void SetPosX(int nPosX) { m_nPosX = nPosX; }
	void SetPosY(int nPosY) { m_nPosY = nPosY; }
	void SetImageID(int nImageID) { m_nImageID = nImageID; }
	void SetLife(double dLife) { m_fLife = (float)dLife; }
	void SetVelX(float fVelX) { if(fVelX == 0) fVelX = 1; m_fVelX = fVelX; }
	void SetVelY(float fVelY) { if(fVelY == 0) fVelY = 1; m_fVelY = fVelY; }
	void SetScale(float fScale) { m_fScale = fScale; }
	void SetAlpha(int cColor) { m_nAlpha = cColor; }
	void SetRed(int cColor) { m_nRed = cColor; }
	void SetGreen(int cColor) { m_nGreen = cColor; }
	void SetBlue(int cColor) { m_nBlue = cColor; }
	void SetColor(int nA, int nR, int nG, int nB);

	// Accessors
	float GetLife() { return m_fLife; }
	int GetPosX() { return m_nPosX; }
	int GetPosY() { return m_nPosY; }
	float GetScale() { return m_fScale; }
	float GetVelX() { return m_fVelX; }
	float GetVelY() { return m_fVelY; }
	int GetAlpha() { return m_nAlpha; }
	int GetRed() { return m_nRed; }
	int GetGreen() { return m_nGreen; }
	int GetBlue() { return m_nBlue; }

	void Update(float fElapstedTime);
	void Render(void);
	void LoadParticle(string szFileName);

};
#endif