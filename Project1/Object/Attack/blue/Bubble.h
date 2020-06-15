#pragma once
#include "../../Object.h"
#include "../AttackMng.h"



class Bubble :
	public Object
{
public:
	Bubble() = delete;
	// pos:座標			time:時間軸
	// stage:ステージ	target:目標
	Bubble(Vector2 pos, TIME time, int stage, OBJ_TYPE target);
	~Bubble();

	void Update(void)override;

	void IfHitAttack(void)override;

private:
	void Init(void);

	OBJ_TYPE _target;

	int _floatCount;

	int _basePos_y;
	
	static constexpr int LIFE_TIME = 1800;	// 生存時間
};

