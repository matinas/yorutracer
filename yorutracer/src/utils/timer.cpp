#include <iostream>

#include "utils\timer.h"

namespace yoru {
namespace utils {

	Timer::Timer()
	{
		isStarted = false;
	}

	Timer::~Timer()
	{
	}

	void Timer::start()
	{
		startTime = std::chrono::high_resolution_clock::now();

		isStarted = true;
		timeAvailable = false;
	}

	void Timer::stop()
	{
		if (isStarted)
		{
			ChronoTime stopTime = std::chrono::high_resolution_clock::now();
			elapsedMilis = stopTime - startTime;

			timeAvailable = true;
			isStarted = false;
		}
		else
		{
			std::cout << "Timer can't be stopped as it wasn't properly started\n";
		}
	}

	double Timer::getElapsedTime(Timer::TimeUnit unit)
	{
		if (!timeAvailable)
		{
			std::cout << "Can't get elapsed time as the timer wasn't properly started/stopped\n";
			return -1;
		}

		switch (unit)
		{
			case TimeUnit::MILISECONDS:
			{
				return elapsedMilis.count();
			}
			case TimeUnit::SECONDS:
			{
				return elapsedMilis.count() / 1000;
			}
			default:
				std::cout << "Can't get elapsed time as the time unit is unknown\n";
		}
	}
}}