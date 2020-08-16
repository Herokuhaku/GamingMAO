#pragma once
#include "../../Object.h"
class HealTree :
	public Object
{
public:
	HealTree() = delete;
	// pos:���W			time:���Ԏ�
	// stage:�X�e�[�W	target:�ڕW
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

