#ifndef CEMITTER_H_
#define CEMITTER_H_

#include <windows.h>
#include <vector>
#include <string>
using std::vector;

#include "CParticle.h"

class CEmitter
{
private:
	vector<CParticle*> m_vParticle;	
	
	int m_nNumberOfParticles;
	double m_dLife;
	float m_fCounter;

	int m_nPosX;
	int m_nPosY;
	int m_nImageID;

	int m_nMinVelX;
	int m_nMinVelY;
	int m_nMaxVelX;
	int m_nMaxVelY;

	double m_dMinScale;
	double m_dMaxScale;

	DWORD m_cStartColor;
	DWORD m_cEndingColor;

	int alpha, red, green, blue;
	int ealpha, ered, egreen, eblue;

	int m_nSourceBlend;
	int m_nDestBlend;
	int CCA, CCR, CCG, CCB;

	string m_szParticleName;

public:
	// Constructor
	CEmitter();

	// Accessors
	int GetNumberOfParticles() { return m_nNumberOfParticles; }
	vector<CParticle*>* GetParticles(void) { return &m_vParticle; }
	CParticle* GetParticle(int index) { return m_vParticle[index]; }
	int GetImageID() { return m_nImageID; }
	int GetPosX() { return m_nPosX; }
	int GetPosY() { return m_nPosY; }
	double GetLife() { return m_dLife; }
	int GetMinVelX() { return m_nMinVelX; }
	int GetMinVelY() { return m_nMinVelY; }
	int GetMaxVelX() { return m_nMaxVelX; }
	int GetMaxVelY() { return m_nMaxVelY; }
	float GetScale() { return (float)m_dMinScale; }
	// Mutators
	//void SetParticleVector(CParticle* pParticle) { m_vParticle.push_back(pParticle); }
	void SetPosX(int nPosX) { m_nPosX = nPosX; }
	void SetPosY(int nPosY) { m_nPosY = nPosY; }

	// Functions
	void Update(float fElapsedTime);
	void Render(void);
	void LoadEmitter(string szFileName);
	void EmitParticles(void);
	void Colors(void);

};
#endif