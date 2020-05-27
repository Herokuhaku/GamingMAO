#pragma once
#include "Enemy.h"

class sorcerer :
	public Enemy
{
public:
	void Update(void);
	sorcerer(Vector2 pos,int stage);
	sorcerer(Vector2 pos,int stage,int pPos, bool flag);		// lpMapMng‚Ì’†‚Åƒ‹[ƒv‚·‚é‚©‚çEnemy‚ÌÀ•W‚ğ‰º‚É‰º‚°‚é‚â‚Â‚ğœ‚¢‚½‚à‚Ì
	~sorcerer();
private:
	void Init(void);
};
