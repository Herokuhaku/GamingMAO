#pragma once
#include "../Object.h"

class FireBall :
	public Object
{
public:
	FireBall();
	FireBall(Vector2 pos, DIR dir, int speed, TIME time, int stage);
	~FireBall();

	void Update(void)override;

private:
	void Init(void);

	int _speed;
};

