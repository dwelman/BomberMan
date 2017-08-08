#pragma once

#include <cstddef>
/*
 *	This is the game clock class, it is a singleton because it only needs to be
 *	accessed to query the time, the tick function will only be called in the main
*/

class Clock
{
private:
	std::size_t	m_nowTickTime;
	std::size_t	m_lastTickTime;
	double		m_delta;

	Clock();
	Clock(Clock const &c);

	Clock	&operator=(Clock const &c);
	~Clock();
public:
	static Clock	&Instance();
	void			Tick();
	double			GetDeltaTime();
};