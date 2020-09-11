#pragma once
#include "../Object.h"
class SpearAttack :
	public Object
{
public:
	SpearAttack(Vector2& ePos, DIR dir, TIME time, int stage, OBJ_TYPE target);
	SpearAttack() {}
	~SpearAttack();

	void Update(void)override;
	void Draw(void) override;
	void IfHitAttack(std::shared_ptr<Object> target) override;

protected:
	int _farstY;
	OBJ_TYPE _target;
	virtual bool Init(void);
};

