#pragma once
#include "../../Object.h"

class BlackHole :
	public Object
{
public:
	BlackHole() = delete;
	// pos:座標			dir:方向
	// vec:移動ベクトル( vec.x > 0 でdir方向に、vec.x < 0 で反対側に)
	// lifetime:生存時間
	// time:時間軸		stage:ステージ
	// target:目標
	BlackHole(Vector2 pos, DIR dir, Vector2 vec, int lifetime, TIME time, int stage, OBJ_TYPE target);
	~BlackHole();

	void Update(void);

	void Draw(void)override;

	void IfHitAttack(std::shared_ptr<Object> target)override;

private:
	void Init(void);

	void NormalUpdate(void);
	void FinishUpdate(void);
	void(BlackHole::* _update)(void);

	Vector2 _vec;
	OBJ_TYPE _target;

	int _lifetime;

	int _timer;
};

