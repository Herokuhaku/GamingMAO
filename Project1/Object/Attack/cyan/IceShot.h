#pragma once
#include "../../Object.h"

class IceShot :
	public Object
{
public:
	IceShot() = delete;
	// owner:所有者
	// pos:座標			dir:方向
	// vec:移動ベクトル( vec.x > 0 でdir方向に、vec.x < 0 で反対側に)
	// time:時間軸		stage:ステージ
	// target:目標
	IceShot(std::weak_ptr<Object> owner, Vector2 offset, DIR dir, Vector2 vec, TIME time, int stage, OBJ_TYPE target);
	~IceShot();

	void Update(void);
	void Draw(void)override;

	void IfHitAttack(std::shared_ptr<Object> target)override;

private:
	void Init(void);

	void ChargeUpdate(void);
	void ShotUpdate(void);
	void FlyingUpdate(void);
	void DestroyUpdate(void);
	void(IceShot::* _update)(void);

	void ChargeDraw(void);
	void ShotDraw(void);
	void FlyingDraw(void);
	void(IceShot::* _draw)(void);

	Vector2 _vec;
	OBJ_TYPE _target;

	std::weak_ptr<Object> _owner;
	Vector2 _offset;
	double _shotRad;

	int _screen;

	int _timer;
};

