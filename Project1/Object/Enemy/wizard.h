#pragma once
#include "Enemy.h"

class wizard :
	public Enemy
{
public:
	void Update(void);
	int Attack(Vector2& pos)override;
	wizard(Vector2 pos,int stage);
	wizard(Vector2 pos,int stage,int pPos, bool flag);		// lpMapMngの中でループするからEnemyの座標を下に下げるやつを除いたもの
	~wizard();
private:
	void Init(void);
};
