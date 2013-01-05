#pragma once
#include <list>
class Camera;
class Input;
class GameManager
{
private:
	static GameManager* gameManagerInstance;
	Input* input;
public:
	static GameManager* Instance();
	GameManager();
	~GameManager();

	void Run();

};