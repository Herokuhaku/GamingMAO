#include "Enemy.h"

void Enemy::Update(void)
{
	if (_state_dir.first != OBJ_STATE::ATTACK && cnt == 0)		// ‹ß‚­‚ÉPL‚ª‚¢‚½‚ç
	{
		setState({ OBJ_STATE::ATTACK, _state_dir.second });
		cnt++;
	}
	Object::Draw();
}

Enemy::Enemy()
{
	cnt = 0;
	Init();
}

void Enemy::Init(void)
{

}

Enemy::~Enemy()
{
}

