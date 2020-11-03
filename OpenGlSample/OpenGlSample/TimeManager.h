#ifndef __TIMEMANAGER_H__
#define __TIMEMANAGER_H__

#include <Windows.h>

class TimeManager
{
private:
	static TimeManager* instance;

	TimeManager();

public:
	int _targetframe;
	int count;
	double _perFrame;

	LARGE_INTEGER _frameInfo;
	LARGE_INTEGER _prevFrameCounter;
	LARGE_INTEGER _nowFrameCounter;

public:
	static TimeManager* GetInstance()
	{
		if (instance == 0)
		{
			instance = new TimeManager();
		}
		return instance;
	};

	bool IsRenderTiming();
};

#endif