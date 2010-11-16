/**
 * 
 * Description:
 * The sheet structure which will contain all the animations for a particular game object. It will be able to be identified by the name of the file.
 * 
 * Stipulations:
 * The vector of animations must contain at least one animation.
 * 
 * Interface:
 * Contains no functions.
 */
#include "tAnimation.h"

#pragma once

struct tSheet
{
	/**
	 * Image ID
	 */
	int ImageID;
	/**
	 * Vector of animations
	 */
	vector<tAnimation*> m_vAnimations;
	/**
	 * file name animations
	 */
	const char* szFilePath;

	tSheet();
};


