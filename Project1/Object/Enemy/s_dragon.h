#pragma once
#include "Enemy.h"

class s_dragon :
	public Enemy
{
public:
	void Update(void);
	s_dragon(Vector2 pos,int stage);
	s_dragon(Vector2 pos,int stage,bool flag);		// lpMapMng‚Ì’†‚Åƒ‹[ƒv‚·‚é‚©‚çEnemy‚ÌÀ•W‚ğ‰º‚É‰º‚°‚é‚â‚Â‚ğœ‚¢‚½‚à‚Ì
	~s_dragon();
private:
	void Init(void);
};
