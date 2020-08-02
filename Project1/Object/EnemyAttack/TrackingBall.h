#pragma once
#include "../Object.h"
class TrackingBall :
	public Object
{
public:
	TrackingBall(Vector2& ePos, Vector2& pPos, TIME time, int stage, OBJ_TYPE target);
	~TrackingBall();

	void Update(void)override;
	void Draw(void) override;

private:

	Vector2 _ePos;
	Vector2 _pPos;

	OBJ_TYPE _target;
	DIR _dir;

	bool Init(void);
};

