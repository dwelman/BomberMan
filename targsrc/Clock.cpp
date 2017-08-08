#include "Clock.hpp"
#include "SDL.h"

Clock::Clock()
{
	m_nowTickTime = SDL_GetPerformanceCounter();
	m_lastTickTime = 0;
	m_delta = 0;
}

Clock::~Clock()
{

}

Clock & Clock::Instance()
{
	static Clock m_instance;
	return (m_instance);
}

void Clock::Tick()
{
	m_lastTickTime = m_nowTickTime;
	m_nowTickTime = SDL_GetPerformanceCounter();
	m_delta = (double)((m_nowTickTime - m_lastTickTime) * 1000 / SDL_GetPerformanceFrequency());
}

double	Clock::GetDeltaTime()
{
	return (m_delta);
}
