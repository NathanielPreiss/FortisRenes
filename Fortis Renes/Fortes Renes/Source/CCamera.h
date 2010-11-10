#ifndef CCAMERA_H_
#define CCAMERA_H_

class CCamera
{
private:
	float m_fPosX;
	float m_fPosY;

	int m_nMinX;
	int m_nMinY;
	int m_nMaxX;
	int m_nMaxY;

	bool m_bShake;
	float m_fShakeTimer;
	float m_fTimeBucket;

	CCamera(void);
	~CCamera(void);

public:
	static CCamera* GetInstance(void);

	void UpdateCameraPos( float fFocusX, float fFocusY);
	void Update(float fElapsedTime);

	void Shake(void){m_bShake = true;m_fTimeBucket = 0.0f;}


	float GetPosX(void) { return m_fPosX; }
	float GetPosY(void) { return m_fPosY; }

	int GetMinX(void)	{ return m_nMinX; }
	int GetMinY(void)	{ return m_nMinY; }
	int GetMaxX(void)	{ return m_nMaxX; }
	int GetMaxY(void)	{ return m_nMaxY; }

	void SetPosX(float fPosX)	{ m_fPosX = fPosX; }
	void SetPosY(float fPosY)	{ m_fPosX = fPosY; }
	
	void SetMinX(int nMinX)	{ m_nMinX = nMinX; }
	void SetMinY(int nMinY)	{ m_nMinY = nMinY; }
	void SetMaxX(int nMaxX)	{ m_nMaxX = nMaxX; }
	void SetMaxY(int nMaxY)	{ m_nMaxY = nMaxY; }
	void SetBoundaries();
};
#endif