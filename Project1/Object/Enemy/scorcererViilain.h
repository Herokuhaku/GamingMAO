#pragma once
#include "Enemy.h"

class sorcerer :
	public Enemy
{
public:
	void Update(void);
	sorcerer(Vector2 pos,int stage);
	sorcerer(Vector2 pos,int stage,int pPos, bool flag);		// lpMapMng�̒��Ń��[�v���邩��Enemy�̍��W�����ɉ�����������������
	~sorcerer();
private:
	void Init(void);
};
