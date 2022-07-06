#pragma once

#include <Windows.h>

class Timer
{
public:
	Timer()
	{
		QueryPerformanceFrequency((LARGE_INTEGER*)&tick);
	}

	void Start()
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&start);
	}

	void End()
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&end);
	}

	float RunningTime()
	{
		return (float)((double)(end - start) / tick * 1000.0f);
	}


private:
	__int64 tick;
	__int64 start, end;

};