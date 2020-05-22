#pragma once
#include "../Object.h"

class BubbleBlast :
	public Object
{
public:
	BubbleBlast();
	BubbleBlast(Vector2 pos, TIME time, int stage, OBJ_TYPE target);
	~BubbleBlast();
private:
};

