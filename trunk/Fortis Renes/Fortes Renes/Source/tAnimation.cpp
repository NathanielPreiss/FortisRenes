#include "tAnimation.h"

tAnimation::tAnimation()
{
	szName = "Name";

	bIsLooping = true;

	nCurrFrame = 0;

	//fPosX, fPosY;

	fTimeWaited = 0.0f;

	bIsPlaying = false;
	
	m_vFrames.begin();
}

void tAnimation::Play() 
{
	Reset();
	Resume();
}

void tAnimation::Stop() 
{
	bIsPlaying = false;
}

void tAnimation::Reset() 
{
	nCurrFrame = 0;
	fTimeWaited = 0.0f;
}

void tAnimation::Resume() 
{
	bIsPlaying = true;
	
}