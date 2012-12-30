#pragma once
#include <list>
class Camera;
class Input;
class GameManager
{
private:
	static GameManager* gameManagerInstance;
	Camera* camera;
	Input* input;
public:
	static GameManager* Instance();
	GameManager();
	~GameManager();

	void Run();

	Camera* GetCamera() { return camera; }
};