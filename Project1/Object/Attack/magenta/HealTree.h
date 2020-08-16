#pragma once
#include "../../Object.h"
class HealTree :
	public Object
{
public:
	HealTree() = delete;
	// pos:座標			time:時間軸
	// stage:ステージ	target:目標
	HealTree(Vector2 pos, TIME time, int stage, OBJ_TYPE target);
	~HealTree();

	void Update(void);
private:
	void Init(void);

	void GrowUpdate(void);
	void ActiveUpdate(void);
	void WitherUpdate(void);

	void (HealTree::*_update)(void);

	int FindSF(int);

	int _timer;
	int _healCount;

	OBJ_TYPE _target;
};

