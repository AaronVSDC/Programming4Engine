#pragma once
#include <chrono>
#include <thread>
class Time final
{
public:

	static Time& GetInstance()
	{
		static Time instance;
		return instance;
	}
	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;
	Time(const Time&&) = delete;
	Time& operator=(const Time&&) = delete;

	void Update(bool capFramerate, float maxFPS)
	{
		auto now = std::chrono::high_resolution_clock::now(); 
		std::chrono::duration<float> duration = now - m_LastTime; 

		m_DeltaTime = duration.count(); 

		float targetFrameTime = 1.0f / maxFPS; 

		if (capFramerate and m_DeltaTime < targetFrameTime)
		{
			float sleepTime = targetFrameTime - m_DeltaTime; 
			std::this_thread::sleep_for(std::chrono::duration<float>(sleepTime)); 

			auto afterSleep = std::chrono::high_resolution_clock::now(); 
			duration = std::chrono::duration_cast<std::chrono::duration<float>>(afterSleep - m_LastTime); 
			m_DeltaTime = duration.count(); 
			m_LastTime = afterSleep; 
		}
		else
		{
			m_LastTime = now;
		}
	}

	float GetDeltaTime() { return m_DeltaTime;  }
private: 

	Time()
	{
		m_LastTime = std::chrono::high_resolution_clock::now(); 
		m_DeltaTime = 0.f;
	}

	std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTime; 
	float m_DeltaTime; 

};

