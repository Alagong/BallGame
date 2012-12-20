#pragma once
#include <list>
class Player;
class Wall;
class Camera;
class GameManager
{
private:
	static GameManager* gameManagerInstance;
	Camera* camera;
public:
	static GameManager* Instance();
	GameManager();
	~GameManager();

	void Run();

	Camera* GetCamera() { return camera; }
};