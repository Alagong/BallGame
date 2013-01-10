#pragma once
#include <list>
class Camera;
class Input;
class Timer;
class GameManager
{
private:
	static GameManager* gameManagerInstance;
	Input* input;
	Timer* fpsTimer;
public:
	static GameManager* Instance();
	GameManager();
	~GameManager();

	void Run();

};