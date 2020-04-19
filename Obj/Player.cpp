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
	Control();
	VelUpdate();

	_pos.y = 400;
	Object::Draw();
}

void Player::Init(void)
{
	AnmVec data;
	data.emplace_back(lpImageMng.getImage("player")[0], 30);
	data.emplace_back(lpImageMng.getImage("player")[1], 60);
	setAnm({ OBJ_STATE::NORMAL, DIR::LEFT }, data);

	data.emplace_back(lpImageMng.getImage("player")[2], 30);
	data.emplace_back(lpImageMng.getImage("player")[3], 60);
	setAnm({ OBJ_STATE::NORMAL, DIR::RIGHT }, data);

	data.reserve(8);
	data.emplace_back(lpImageMng.getImage("player_walk")[0], 15);
	data.emplace_back(lpImageMng.getImage("player_walk")[1], 30);
	data.emplace_back(lpImageMng.getImage("player_walk")[2], 45);
	data.emplace_back(lpImageMng.getImage("player_walk")[3], 60);
	data.emplace_back(lpImageMng.getImage("player_walk")[4], 75);
	data.emplace_back(lpImageMng.getImage("player_walk")[5], 90);
	data.emplace_back(lpImageMng.getImage("player_walk")[6], 105);
	data.emplace_back(lpImageMng.getImage("player_walk")[7], 120);
	setAnm({ OBJ_STATE::WALK, DIR::LEFT }, data);

	data.emplace_back(lpImageMng.getImage("player_walk")[8], 15);
	data.emplace_back(lpImageMng.getImage("player_walk")[9], 30);
	data.emplace_back(lpImageMng.getImage("player_walk")[10], 45);
	data.emplace_back(lpImageMng.getImage("player_walk")[11], 60);
	data.emplace_back(lpImageMng.getImage("player_walk")[12], 75);
	data.emplace_back(lpImageMng.getImage("player_walk")[13], 90);
	data.emplace_back(lpImageMng.getImage("player_walk")[14], 105);
	data.emplace_back(lpImageMng.getImage("player_walk")[15], 120);
	setAnm({ OBJ_STATE::WALK, DIR::RIGHT }, data);


	_vel = 0.0;
	_tmpPos.y = static_cast<double>(_pos.y);
}

void Player::Control(void)
{
//-----------------------------------------------------------------------------------------
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		_pos.x -= WALK_SPEED;
			setState({ OBJ_STATE::WALK, DIR::LEFT });
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		_pos.x += WALK_SPEED;
			setState({ OBJ_STATE::WALK, DIR::RIGHT });
	}
	else
	{
		if (lpKeyMng.getOldBuf()[KEY_INPUT_LEFT] || lpKeyMng.getOldBuf()[KEY_INPUT_RIGHT])
			setState({ OBJ_STATE::NORMAL, _state_dir.second });
	}




//-----------------------------------------------------------------------------------------










	if (lpKeyMng.getBuf()[KEY_INPUT_LEFT])
	{
		_pos.x -= WALK_SPEED;
		if (!lpKeyMng.getOldBuf()[KEY_INPUT_LEFT] || _state_dir.second == DIR::RIGHT)
		{
			setState({ OBJ_STATE::WALK, DIR::LEFT });
		}
	}
	else if (lpKeyMng.getBuf()[KEY_INPUT_RIGHT])
	{
		_pos.x += WALK_SPEED;
		if (!lpKeyMng.getOldBuf()[KEY_INPUT_RIGHT] || _state_dir.second == DIR::LEFT)
		{
			setState({ OBJ_STATE::WALK, DIR::RIGHT });
		}
	}
	else
	{
		if (lpKeyMng.getOldBuf()[KEY_INPUT_LEFT] || lpKeyMng.getOldBuf()[KEY_INPUT_RIGHT])
			setState({ OBJ_STATE::NORMAL, _state_dir.second });
	}

	if (CheckHitKey(KEY_INPUT_UP) && static_cast<int>(_tmpPos.y) + PLAYER_SIZE_Y / 2 == 720)
	{
		_vel = INI_VEL_NORMAL;

	}
}

void Player::VelUpdate(void)
{
	if (static_cast<int>(_tmpPos.y) + PLAYER_SIZE_Y / 2 < 720)
	{
		_vel = _vel - G_ACC_NORMAL;
	}

	if (static_cast<int>(_tmpPos.y) + PLAYER_SIZE_Y / 2 - _vel >= 720)
	{
		_tmpPos.y = 720.0 - PLAYER_SIZE_Y / 2;
		_vel = 0.0;
	}

	_tmpPos.y -= _vel;

	_pos.y = static_cast<int>(_tmpPos.y);
}
