#include "Enemy.h"

void Enemy::Update(void)
{
	if (_state_dir.first != OBJ_STATE::ATTACK && CheckHitKey(KEY_INPUT_SPACE))		// ‹ß‚­‚ÉPL‚ª‚¢‚½‚ç
	{
		setState({ OBJ_STATE::ATTACK, _state_dir.second });
	}
	Object::Draw();
}

Enemy::Enemy()
{
	Init();
}

void Enemy::Init(void)
{

}

Enemy::~Enemy()
{
}

