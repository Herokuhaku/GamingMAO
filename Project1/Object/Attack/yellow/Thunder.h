#pragma once
#include "../../Object.h"

enum class RAD_TYPE
{
	VRT,	// 縦
	HRZ,	// 横
	EX		// それ以外(演出用)
};

class Thunder :
	public Object
{
public:
	Thunder() = delete;
	// pos1:始点座標		pos2:終点座標
	// useRef:refPosを参照するか(refPosの移動に合わせて動くようになる)
	// refPos:参照に使う座標
	// damage:ダメージ		time:時間軸
	// stage:ステージ		target:目標
	Thunder(Vector2 pos1, Vector2 pos2, bool useRef, Vector2* refPos, int damage, TIME time, int stage, OBJ_TYPE target);
	~Thunder();

	void Update(void)override;

	void Draw(void)override;

	void IfHitAttack(std::shared_ptr<Object> target)override;
private:
	void Init(void);

	Vector2* _refPos;
	Vector2 _offset;

	int _damage;
	OBJ_TYPE _target;

	RAD_TYPE _rType;

};

