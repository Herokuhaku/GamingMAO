#pragma once
#include "../../Object.h"
#include <DxLib.h>
#include <array>

class Flash :
	public Object
{
public:
	Flash() = delete;
	// pos:座標			time:時間軸
	// stage:ステージ	target:目標
	Flash(Vector2* pos, TIME time, int stage, OBJ_TYPE target);
	~Flash();

	void Update(void)override;
	void Draw(void)override;

	void IfHitAttack(std::shared_ptr<Object> target)override;
private:
	void Init(void);
	void OnceInit(void);

	void ExpandUpdate(void);
	void ShrinkUpdate(void);
	void (Flash::*_update)(void);

	OBJ_TYPE _target;
	Vector2* _ownerPos;

	std::array<VERTEX2D, 37> _lightVer;

	int _timer;
};

