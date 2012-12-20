#include "Timer.h"
#include <SFML/System/Clock.hpp>
Timer::Timer()
{
	clock = new sf::Clock();
}

Timer::~Timer()
{
	delete clock;
}

void Timer::Restart()
{
	clock->restart();
}

float Timer::GetSeconds()
{
	return clock->getElapsedTime().asSeconds();
}

int Timer::GetMilliseconds()
{
	return clock->getElapsedTime().asMilliseconds();
}