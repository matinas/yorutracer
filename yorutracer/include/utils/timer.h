#ifndef TIMER_H
#define TIMER_H

#include <chrono>

namespace yoru {
namespace utils {

	typedef std::chrono::system_clock::time_point ChronoTime;
	typedef std::chrono::duration<double, std::milli> ChronoTimeDuration;

	class Timer
	{
	public:
		enum TimeUnit { MILISECONDS, SECONDS };

		Timer();
		~Timer();

		void start();
		void stop();
		double getElapsedTime(TimeUnit unit);

	private:
		ChronoTime startTime;
		ChronoTimeDuration elapsedMilis;

		bool isStarted;
		bool timeAvailable;
	};
}}

#endif
