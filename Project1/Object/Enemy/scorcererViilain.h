#pragma once
#include "Boss.h"

class sorcerer :
	public Boss
{
public:
	void Update(void);
	void damagingHP(int damage) override;
	int Attack(Vector2 pPos) override;
	sorcerer(Vector2 pos,int stage);
	sorcerer(Vector2 pos,int stage,int pPos, bool flag);		// lpMapMng�̒��Ń��[�v���邩��Enemy�̍��W�����ɉ�����������������
	~sorcerer();
private:
	void Init(void);
};
