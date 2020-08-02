#pragma once
#include "Boss.h"

class sorcerer :
	public Boss
{
public:
	void Update(void);
	void damagingHP(int damage) override;
	sorcerer(Vector2 pos,int stage);
	sorcerer(Vector2 pos,int stage,int pPos, bool flag);		// lpMapMngの中でループするからEnemyの座標を下に下げるやつを除いたもの
	~sorcerer();
private:
	void Init(void);
};
