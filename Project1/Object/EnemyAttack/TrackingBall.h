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
	void IfHitAttack(void) override;

private:

	Vector2 _ePos;
	Vector2 _fePos;	// first Pos
	Vector2 _pPos;
	Vector2F _vec;
	Vector2 _changePos;
	int addX;
	float angle;

	OBJ_TYPE _target;
	DIR _dir;

	bool Init(void);
};

