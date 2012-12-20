#pragma once

namespace sf
{
	class Clock;
};

class Timer
{
private:
	sf::Clock* clock;

public:
	Timer();
	~Timer();
	void Restart();

	float GetSeconds();

	int GetMilliseconds();

};