#pragma once
#include "../../Object.h"

class ThunderCloud :
	public Object
{
public:
	ThunderCloud() = delete;
	// pos:座標				dir:方向
	// speed:速度( speed > 0 でdir方向に、speed < 0 で反対側に)
	// count:落とす雷の数	dur:雷の間隔(フレーム数)
	// time:時間軸			stage:ステージ
	// target:目標
	ThunderCloud(Vector2 pos, DIR dir, int speed, int count, int dur, TIME time, int stage, OBJ_TYPE target);
	~ThunderCloud();

	void Update(void)override;
private:
	void Init(void);

	int FindSF(void);

	OBJ_TYPE _target;

	int _attackCount;
	int _countMax;

	int _attackDur;
	int _timer;

	int _speed;


};

