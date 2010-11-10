#ifndef CANIMATION_H_
#define CANIMATION_H_
	
#include <vector>
using std::vector;

#include "CFrame.h"

class CAnimation
{
private:
	vector<CFrame*> m_vFrames;
	int m_nImageID;
	float m_fSpeed;
	float m_fAnimationTime;
	bool m_bIsPlaying;
	int m_nCurrentFrame;

public:
	void Update(float fElapsedTime);
	void Render(void);
	void Play(void);
	void Pause(void);
	void Stop(void);
	void Reset(void);

};
#endif