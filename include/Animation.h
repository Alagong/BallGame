#pragma once
#include "Frame.h"
#include <vector>
class Animation
{
public:
	Animation()
	{
		looping = false;
	}

	void SetLooping(bool l) { looping = l; }
	bool IsLooping() const { return looping; }
	int FrameCount() { return (int)frames.size(); }

	void AddFrame(Frame* frame)
	{
		frames.push_back(frame);
	}

	Frame* GetFrame(int index)
	{
		if(index+1 > FrameCount())
			return NULL;
		return frames[index];
	}
private:
	bool looping;
	std::vector<Frame*> frames;
};