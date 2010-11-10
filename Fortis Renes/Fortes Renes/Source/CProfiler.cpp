////////////////////////////////////////////////////////////////////
// Name: CProfiler.h
// Purpose: This singleton class is to allow the timing and frequency checking of funtions for debug purposes
// Author: JFullerton
////////////////////////////////////////////////////////////////////
#include "CProfiler.h"
#include <fstream>
using namespace std;

CProfiler::CProfiler( )
{
	timesFunctionRan = 0;
}

CProfiler* CProfiler::GetInstance()
{
	static CProfiler instance;
	return &instance;
}

void CProfiler::StartCount()
{
	QueryPerformanceCounter(&startCounter);
}

void CProfiler::EndCount()
{
	QueryPerformanceCounter(&endCounter);
}

void CProfiler::CheckFrequency()
{
	QueryPerformanceFrequency(&frequencyCounter);
}

void CProfiler::Result()
{
	ofstream out;

	out.open("PROFILER.txt");

	if(out.is_open())
	{
		out << "Time function ran: " << (endCounter.QuadPart - startCounter.QuadPart)*1000/frequencyCounter.QuadPart << '\n';
		out << "Number of Times this function was called: " << timesFunctionRan << '\n';
	}
}