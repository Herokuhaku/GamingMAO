#include "Player.h"

Player::Player()
{
}

Player::Player(Vector2Template<int> pos)
{
	_pos = pos;
	_state_dir = { OBJ_STATE::NORMAL, DIR::RIGHT };
	_control = &Player::ControlNormal;
	Init();
}

Player::~Player()
{
}

void Player::Update(void)
{
	(this->*_control)();
	VelUpdate();

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

	data.emplace_back(lpImageMng.getImage("player_dash")[0], 5);
	data.emplace_back(lpImageMng.getImage("player_dash")[1], 10);
	setAnm({ OBJ_STATE::DASH, DIR::LEFT }, data);

	data.emplace_back(lpImageMng.getImage("player_dash")[2], 5);
	data.emplace_back(lpImageMng.getImage("player_dash")[3], 10);
	setAnm({ OBJ_STATE::DASH, DIR::RIGHT }, data);

	data.reserve(1);
	data.emplace_back(lpImageMng.getImage("player_jump")[0], 1);
	setAnm({ OBJ_STATE::JUMP, DIR::LEFT }, data);

	data.emplace_back(lpImageMng.getImage("player_jump")[2], 1);
	setAnm({ OBJ_STATE::JUMP, DIR::RIGHT }, data);

	data.emplace_back(lpImageMng.getImage("player_jump")[1], 1);
	setAnm({ OBJ_STATE::FALL, DIR::LEFT }, data);

	data.emplace_back(lpImageMng.getImage("player_jump")[3], 1);
	setAnm({ OBJ_STATE::FALL, DIR::RIGHT }, data);

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

	data.emplace_back(lpImageMng.getImage("player_walk")[8] , 15);
	data.emplace_back(lpImageMng.getImage("player_walk")[9] , 30);
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

void Player::ControlNormal(void)
{
	if (lpKeyMng.getBuf()[KEY_INPUT_LEFT])
	{
		_pos.x -= WALK_SPEED;
		if (!lpKeyMng.getOldBuf()[KEY_INPUT_LEFT] || _state_dir.first != OBJ_STATE::DASH || _state_dir.second != DIR::LEFT)
		{
			setState({ OBJ_STATE::DASH, DIR::LEFT });
		}
	}
	else if (lpKeyMng.getBuf()[KEY_INPUT_RIGHT])
	{
		_pos.x += WALK_SPEED;
		if (!lpKeyMng.getOldBuf()[KEY_INPUT_RIGHT] || _state_dir.first != OBJ_STATE::DASH || _state_dir.second != DIR::RIGHT)
		{
			setState({ OBJ_STATE::DASH, DIR::RIGHT });
		}
	}
	else
	{
		if(lpKeyMng.getOldBuf()[KEY_INPUT_LEFT] || lpKeyMng.getOldBuf()[KEY_INPUT_RIGHT])
		setState({ OBJ_STATE::NORMAL, _state_dir.second });
	}

	if (CheckHitKey(KEY_INPUT_UP) && static_cast<int>(_tmpPos.y) + PLAYER_SIZE_Y / 2 == 720)
	{
		_vel = INI_VEL_NORMAL;
		setState({ OBJ_STATE::JUMP, _state_dir.second });
		_control = &Player::ControlJump;
	}
}

void Player::ControlJump(void)
{
	if (lpKeyMng.getBuf()[KEY_INPUT_LEFT])
	{
		_pos.x -= WALK_SPEED;
		_state_dir.second = DIR::LEFT;
	}
	if (lpKeyMng.getBuf()[KEY_INPUT_RIGHT])
	{
		_pos.x += WALK_SPEED;
		_state_dir.second = DIR::RIGHT;
	}
}

void Player::VelUpdate(void)
{
	if (static_cast<int>(_tmpPos.y) + PLAYER_SIZE_Y / 2 < 720)
	{
		_vel = _vel - G_ACC_NORMAL;
	}

	if (_vel != 0 && static_cast<int>(_tmpPos.y) + PLAYER_SIZE_Y / 2 - _vel >= 720)
	{
		_tmpPos.y = 720.0 - PLAYER_SIZE_Y / 2;
		_vel = 0.0;
		if (lpKeyMng.getBuf()[KEY_INPUT_LEFT] || lpKeyMng.getBuf()[KEY_INPUT_RIGHT])
		{
			setState({ OBJ_STATE::DASH, _state_dir.second });
		}
		else
		{
			setState({ OBJ_STATE::NORMAL, _state_dir.second });
		}
		_control = &Player::ControlNormal;
	}

	if (_vel < 0)
	{
		setState({ OBJ_STATE::FALL, _state_dir.second });
	}

	_tmpPos.y -= _vel;
	_type = OBJ_TYPE::PLAYER;

	_pos.y = static_cast<int>(_tmpPos.y);
}
