#pragma once
#include "Enemy.h"

class wizard :
	public Enemy
{
public:
	void Update(void);
	int Attack(Vector2& pos)override;
	wizard(Vector2 pos,int stage);
	wizard(Vector2 pos,int stage,int pPos, bool flag);		// lpMapMng‚Ì’†‚Åƒ‹[ƒv‚·‚é‚©‚çEnemy‚ÌÀ•W‚ğ‰º‚É‰º‚°‚é‚â‚Â‚ğœ‚¢‚½‚à‚Ì
	~wizard();
private:
	void Init(void);
};
