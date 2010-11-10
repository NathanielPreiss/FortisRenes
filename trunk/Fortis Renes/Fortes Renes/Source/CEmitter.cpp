#include "CEmitter.h"
#include "DirectX Wrappers/CSGD_TextureManager.h"
#include "DirectX Wrappers/CSGD_Direct3D.h"
#include <fstream>
#include <string>
using namespace std;

CEmitter::CEmitter()
{
	m_vParticle.empty();

	m_nNumberOfParticles = 0;
	m_dLife = 0;

	m_nPosX = 0;
	m_nPosY = 0;
	m_nImageID = 0;

	m_nMinVelX = 0;
	m_nMinVelY = 0;
	m_nMaxVelX = 0;
	m_nMaxVelY = 0;

	m_dMinScale = 0;
	m_dMaxScale = 0;

	m_cStartColor = 0;
	m_cEndingColor = 0;

	m_nSourceBlend = 0;
	m_nDestBlend = 0;

	m_fCounter = 1.0f;
}

void CEmitter::LoadEmitter(string szFileName)
{
	std::ifstream in;

	in.open(szFileName.c_str(), ios_base::in | ios_base::binary);

	if(in.is_open())
	{
		in.read((char*)&m_nNumberOfParticles, sizeof(int));
		in.read((char*)&m_dLife, sizeof(double));

		// Loading String
		//////////////////////////////////////////////////////////////////////////////
		char c;
		in.read(&c, sizeof(c));
		char* buffer = new char[(int)c+1];
		in.read(buffer, c);
		buffer[c] = '\0';
		string sztemp = "Resource/Graphics/";
		sztemp += buffer;
		delete[] buffer;
		m_nImageID = CSGD_TextureManager::GetInstance()->LoadTexture(sztemp.c_str());
		//////////////////////////////////////////////////////////////////////////////

		in.read((char*)&m_nMinVelX, sizeof(int));
		in.read((char*)&m_nMinVelY, sizeof(int));
		in.read((char*)&m_nMaxVelX, sizeof(int));
		in.read((char*)&m_nMaxVelY, sizeof(int));

		in.read((char*)&m_dMinScale, sizeof(double));
		in.read((char*)&m_dMaxScale, sizeof(double));

		in.read((char*)&m_nPosX, sizeof(int));
		in.read((char*)&m_nPosY, sizeof(int));

		in.read((char*)&alpha, sizeof(int));
		in.read((char*)&red, sizeof(int));
		in.read((char*)&green, sizeof(int));
		in.read((char*)&blue, sizeof(int));
		in.read((char*)&ealpha, sizeof(int));
		in.read((char*)&ered, sizeof(int));
		in.read((char*)&egreen, sizeof(int));
		in.read((char*)&eblue, sizeof(int));
		in.read((char*)&m_nDestBlend, sizeof(int));
		in.read((char*)&m_nSourceBlend, sizeof(int));
	}
	in.close();

	Colors();
}

void CEmitter::Update(float fElapsedTime)
{
	float DS, SR;
	float randomLife;

	m_fCounter -= fElapsedTime;

	

	DS = (float)(m_dMaxScale - m_dMinScale);
    SR = (float)(DS/30);

    for (int i = 0; i < m_nNumberOfParticles; i++)
    {
        m_vParticle[i]->SetLife(m_vParticle[i]->GetLife() - fElapsedTime);

        m_vParticle[i]->SetScale(m_vParticle[i]->GetScale() + SR * fElapsedTime);

        int talpha   = m_vParticle[i]->GetAlpha();
        int tred     = m_vParticle[i]->GetRed();
        int tgreen   = m_vParticle[i]->GetGreen();
        int tblue    = m_vParticle[i]->GetBlue();

        talpha   += (int)(CCA * fElapsedTime);
        tred     += (int)(CCR * fElapsedTime);
        tgreen   += (int)(CCG * fElapsedTime);
        tblue    += (int)(CCB * fElapsedTime);

        if (talpha > 255)
            talpha = 255;
        if (tred > 255)
            tred = 255;
        if (tgreen > 255)
            tgreen = 255;
        if (tblue > 255)
            tblue = 255;

        if (talpha < 0)
            talpha = 0;
        if (tred < 0)
            tred = 0;
        if (tgreen < 0)
            tgreen = 0;
        if (tblue < 0)
            tblue = 0;

        m_vParticle[i]->SetAlpha(talpha);
		m_vParticle[i]->SetRed(tred);
		m_vParticle[i]->SetGreen(tgreen);
		m_vParticle[i]->SetBlue(tblue);

		m_vParticle[i]->Update(fElapsedTime);

        if (m_vParticle[i]->GetLife() < 0 )
        {
            randomLife = (float)(rand() % (int)(m_dLife * 1000)) / 1000.0f + 1.0f;
            m_vParticle[i]->SetPosX(m_nPosX);
            m_vParticle[i]->SetPosY(m_nPosY);

            m_vParticle[i]->SetVelX((float)(rand() % (m_nMaxVelX - m_nMinVelX + 1) + m_nMinVelX));
            m_vParticle[i]->SetVelY((float)(rand() % (m_nMaxVelY - m_nMinVelY + 1) + m_nMinVelY));
            m_vParticle[i]->SetLife(randomLife / m_dLife);
            m_vParticle[i]->SetScale((float)m_dMinScale);
            m_vParticle[i]->SetColor(alpha, red, green, blue);
        }

        m_vParticle[i]->SetPosX(m_vParticle[i]->GetPosX() + (int)(m_vParticle[i]->GetVelX() * fElapsedTime));
        m_vParticle[i]->SetPosY(m_vParticle[i]->GetPosY() + (int)(m_vParticle[i]->GetVelY() * fElapsedTime));

    }
}

void CEmitter::Colors()
{
	int talpha	= ealpha;
	int tred	= ered;
	int tgreen	= egreen;
	int tblue	= eblue;

	int talpha2	= alpha;
	int tred2	= red;
	int tgreen2 = green;
	int tblue2	= blue; 

	int DCA = talpha;
	int DCR = (tred - tred2);
	int DCG = (tgreen - tgreen2);
	int DCB = (tblue - tblue2);

	for (int i = 0; i < m_nNumberOfParticles; i++)
	{
		CCA = (int)(DCA / m_dLife);
		CCR = (int)(DCR / m_dLife);
		CCG = (int)(DCG / m_dLife);
		CCB = (int)(DCB / m_dLife);
	}

	int talpha3	= ealpha;
	int tred3	= ered;
	int tgreen3 = egreen;
	int tblue3	= eblue;
				  
	int talpha4	= alpha;
	int tred4	= red;
	int tgreen4 = green;
	int tblue4	= blue;

	int DCA2 = (talpha3 - talpha4);
	int DCR2 = (tred3 - tred4);
	int DCG2 = (tgreen3 - tgreen4);
	int DCB2 = (tblue3 - tblue4);

	for (int i = 0; i < m_nNumberOfParticles; i++)
	{
		CCA = (int)(DCA2 / m_dLife);
		CCR = (int)(DCR2 / m_dLife);
		CCG = (int)(DCG2 / m_dLife);
		CCB = (int)(DCB2 / m_dLife);
	}
	
	m_cStartColor = D3DCOLOR_ARGB(alpha, red, green, blue);
	m_cEndingColor = D3DCOLOR_ARGB(ealpha, ered, egreen, eblue);
}