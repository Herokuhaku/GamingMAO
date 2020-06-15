#pragma once
#include <random>
#include "../../Object.h"

enum class FRUIT_TYPE
{
	WATERMELON,
	APPLE,
	ORANGE,
	GRAPE,
	MAX
};

class Fruit :
	public Object
{
public:
	Fruit() = delete;
	// pos:座標			dir:方向
	// speed:速度( speed > 0 でdir方向に、speed < 0 で反対側に)
	// time:時間軸		stage:ステージ
	// target:目標
	Fruit(Vector2 pos, DIR dir, int speed, TIME time, int stage, OBJ_TYPE target);
	~Fruit();

	void Update(void)override;

	void IfHitAttack(void)override;
private:
	void Init(void);

	int _speed;
	double _vel;

	OBJ_TYPE _target;

	FRUIT_TYPE _frType;

	double _radSpeed;

	static constexpr double G_ACC = 0.4;
	static constexpr double ACC_MAX = 8.0;

	void VelUpdate(void);
};

