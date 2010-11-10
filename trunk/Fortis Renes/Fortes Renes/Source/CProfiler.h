////////////////////////////////////////////////////////////////////
// Name: CProfiler.h
// Purpose: This singleton class is to allow the timing and frequency checking of funtions for debug purposes
// Author: JFullerton
////////////////////////////////////////////////////////////////////
#ifndef CPROFILER_H_
#define CPROFILER_H_

#include <windows.h>

class CProfiler
{
private:
	int timesFunctionRan;
	LARGE_INTEGER startCounter;
	LARGE_INTEGER endCounter;
	LARGE_INTEGER frequencyCounter;

	CProfiler();
	CProfiler(const CProfiler& that);
	CProfiler& operator=(const CProfiler& that);

public:
	static CProfiler* GetInstance();
	void StartCount();
	void EndCount();
	void CheckFrequency();
	void Result();
	void IncrementCount() { timesFunctionRan++; }
	void ResetCount() { timesFunctionRan = 0; }

};

#endif