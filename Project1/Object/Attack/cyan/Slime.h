#pragma once
#include "../../Object.h"
class Slime :
	public Object
{
public:
	// pos:À•W		dir::Œü‚«
	// target:•W“I‚Ìí—Ş
	Slime(const Vector2& pos, DIR dir, int stage, OBJ_TYPE target);
	~Slime() = default;

	void Update(void)override;

	void IfHitAttack(std::shared_ptr<Object> target)override;
private:
	void MoveUpdate(void);
	void AttackUpdate(void);
	void DeadUpdate(void);
	void (Slime::*_update)(void);
	
	void VelUpdate(void);

	OBJ_TYPE _target;
	double _vel;
	int _timer = 0;

	int _lifetime;
	bool _isNewObject = true;
};
