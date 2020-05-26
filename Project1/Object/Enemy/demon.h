#pragma once
#include "Enemy.h"

class demon :
	public Enemy
{
public:
	void Update(void);
	demon(Vector2 pos,int stage);
	demon(Vector2 pos,int stage,int pPos, bool flag);		// lpMapMng‚Ì’†‚Åƒ‹[ƒv‚·‚é‚©‚çEnemy‚ÌÀ•W‚ğ‰º‚É‰º‚°‚é‚â‚Â‚ğœ‚¢‚½‚à‚Ì
	~demon();
private:
	void Init(void);
};
