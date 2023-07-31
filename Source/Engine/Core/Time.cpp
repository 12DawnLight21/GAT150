#include "Time.h"
#include "MathUtils.h"

namespace umbra
{
	Time g_time;

	void Time::Tick() //used to scale movement depending on framerate
	{
		clock_duration duration = clock::now() - m_startTime;
		m_time = duration.count() / static_cast<float>(clock_duration::period::den); //a special way of casting, can specify what youre casting

		duration = clock::now() - m_frameTime;
		m_deltaTime = duration.count() / static_cast<float>(clock_duration::period::den);
		m_deltaTime = Min(m_deltaTime, 0.25f); //dt never goes over 0.25 seconds

		m_frameTime = clock::now();
	}
	Time::clock_rep Time::GetElapsedNanoseconds()
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(clock::now() - m_startTime).count();
	}

	Time::clock_rep Time::GetElapsedMicroseconds()
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(clock::now() - m_startTime).count();
	}

	Time::clock_rep Time::GetElapsedMilliseconds()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - m_startTime).count();
	}

	float Time::GetElapsedSeconds()
	{
		return (clock::now() - m_startTime).count() / static_cast<float>(clock_duration::period::den);
	}


}