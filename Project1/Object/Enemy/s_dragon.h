#pragma once
#include "Enemy.h"

class s_dragon :
	public Enemy
{
public:
	void Update(void);
	int Attack(Vector2 pos) override;
	s_dragon(Vector2 pos,int stage);
	s_dragon(Vector2 pos,int stage,int pPos, bool flag);		// lpMapMng�̒��Ń��[�v���邩��Enemy�̍��W�����ɉ�����������������
	~s_dragon();
private:
	void Init(void);
};
