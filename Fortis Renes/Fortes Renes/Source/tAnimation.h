/**
 * 
 * Description:
 * This is the animation structure that contains frames for the animation of a game object. It can play, stop, reset, or resume the animation.
 * 
 * Stipulations:
 * The vector of frames must contain more than one frame.
 * 
 * Interface:
 * Will contain functions to play, stop, reset, and resume the animation.
 */
#pragma once

#include <vector>
using std::vector;

#include "tFrame.h"

struct tAnimation
{
	/**
	 * name of animation
	 */
	char* szName;
	/**
	 * looping variable
	 */
	bool bIsLooping;

	unsigned int nCurrFrame;

	float fTimeWaited;

	//float fPosX, fPosY;

	bool bIsPlaying;

	/**
	 * vector of frames for animation
	 */
	vector<tFrame*> m_vFrames;

	tAnimation();
	/**
	 * will play the animation
	 */
	void Play();
	/**
	 * will stop the animation
	 */
	void Stop();
	/**
	 * will reset the animation
	 */
	void Reset();
	/**
	 * will resume the animation
	 */
	void Resume();
};


