#pragma once
#include "../../Object.h"

class ThunderCloud :
	public Object
{
public:
	ThunderCloud();
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

