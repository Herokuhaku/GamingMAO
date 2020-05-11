#pragma once
#include "Enemy.h"

class s_dragon :
	public Enemy
{
public:
	void Update(void);
//	s_dragon(Vector2Template<int> pos, double rad, TIME time, int stage, OBJ_TYPE type, std::pair<OBJ_STATE, DIR> state_dir);
	s_dragon();
	~s_dragon();
private:
	void Init(void);
};
