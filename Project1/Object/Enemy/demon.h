#pragma once
#include "Enemy.h"

class demon :
	public Enemy
{
public:
	void Update(void);
	demon(Vector2 pos,int stage);
	demon(Vector2 pos,int stage,int pPos, bool flag);		// lpMapMng�̒��Ń��[�v���邩��Enemy�̍��W�����ɉ�����������������
	~demon();
private:
	void Init(void);
};
