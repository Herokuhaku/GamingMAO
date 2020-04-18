#include "Player.h"

Player::Player()
{
}

Player::Player(Vector2Template<int> pos)
{
	_pos = pos;
	_state_dir = { OBJ_STATE::NORMAL, DIR::RIGHT };
	Init();
}

Player::~Player()
{
}

void Player::Update(void)
{
	if(CheckHitKey(KEY_INPUT_LEFT))
	{
		_state_dir.second = DIR::LEFT;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		_state_dir.second = DIR::RIGHT;
	}

	Object::Draw();
}

void Player::Init(void)
{
	AnmVec data;
	data.emplace_back(lpImageMng.getImage("player")[0], 30);
	data.emplace_back(lpImageMng.getImage("player")[1], 60);
	setAnm({OBJ_STATE::NORMAL, DIR::LEFT}, data);

	data.emplace_back(lpImageMng.getImage("player")[2], 30);
	data.emplace_back(lpImageMng.getImage("player")[3], 60);
	setAnm({OBJ_STATE::NORMAL, DIR::RIGHT}, data);
}
