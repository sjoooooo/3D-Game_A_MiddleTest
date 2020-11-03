#include "TimeManager.h"
#include <iostream>

TimeManager* TimeManager::instance = 0;

TimeManager::TimeManager()
{
	// 프레임 측정 관련 셋업
	_targetframe = 60;
	
	QueryPerformanceFrequency(&_frameInfo);
	QueryPerformanceCounter(&_prevFrameCounter);

	// fps 60 고정
	_perFrame = _frameInfo.QuadPart / (double)_targetframe;
	std::cout << _targetframe << std::endl;
}

bool TimeManager::IsRenderTiming()
{
	QueryPerformanceCounter(&_nowFrameCounter);

	double time_distance = _nowFrameCounter.QuadPart - (double)_prevFrameCounter.QuadPart;

	// 렌더링 타이밍
	if (time_distance > _perFrame)
	{
		_prevFrameCounter = _nowFrameCounter;

		// 1초 간격 동작 확인
		count = 0;

		if (count++ > _targetframe)
		{
			std::cout << "1초" << std::endl;

			count = 0;
		}

		std::cout << "dis:" << time_distance << " Fps:" << _frameInfo.QuadPart / time_distance << std::endl;

		return true;
	}
	
	return false;
}