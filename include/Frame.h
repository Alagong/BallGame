#pragma once

struct Frame
{
	int posX;
	int posY;
	int frameTime;
	Frame(int posX, int posY, int frameTime)
	{
		this->posX = posX;
		this->posY = posY;
		this->frameTime = frameTime;
	}
};