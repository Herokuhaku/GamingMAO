#include "Player.h"

Player::Player()
{
}

Player::Player(Vector2Template<int> pos)
{
	_pos = pos;
	_tmpPos = {static_cast<double>(pos.x),static_cast<double>(pos.y)};
	_state_dir = { OBJ_STATE::NORMAL, DIR::RIGHT };
	_coolTime = 0;
	_anmEfkHd = -1;
	_rotateFlag = false;
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

	MagicUpdate();

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

	data.emplace_back(lpImageMng.getImage("player_attack")[0], 1);
	setAnm({ OBJ_STATE::A_NORMAL, DIR::LEFT }, data);

	data.emplace_back(lpImageMng.getImage("player_attack")[1], 1);
	setAnm({ OBJ_STATE::A_NORMAL, DIR::RIGHT }, data);

	data.emplace_back(lpImageMng.getImage("player_attack")[2], 1);
	setAnm({ OBJ_STATE::A_JUMP, DIR::LEFT }, data);

	data.emplace_back(lpImageMng.getImage("player_attack")[3], 1);
	setAnm({ OBJ_STATE::A_JUMP, DIR::RIGHT }, data);

	data.reserve(2);
	data.emplace_back(lpImageMng.getImage("player_attack")[4], 5);
	data.emplace_back(lpImageMng.getImage("player_attack")[5], 10);
	setAnm({ OBJ_STATE::A_DASH, DIR::LEFT }, data);

	data.emplace_back(lpImageMng.getImage("player_attack")[6], 5);
	data.emplace_back(lpImageMng.getImage("player_attack")[7], 10);
	setAnm({ OBJ_STATE::A_DASH, DIR::RIGHT }, data);

	data.reserve(8);
	data.emplace_back(lpImageMng.getImage("player_attack")[8], 15);
	data.emplace_back(lpImageMng.getImage("player_attack")[9], 30);
	data.emplace_back(lpImageMng.getImage("player_attack")[10], 45);
	data.emplace_back(lpImageMng.getImage("player_attack")[11], 60);
	data.emplace_back(lpImageMng.getImage("player_attack")[12], 75);
	data.emplace_back(lpImageMng.getImage("player_attack")[13], 90);
	data.emplace_back(lpImageMng.getImage("player_attack")[14], 105);
	data.emplace_back(lpImageMng.getImage("player_attack")[15], 120);
	setAnm({ OBJ_STATE::A_WALK, DIR::LEFT }, data);

	data.emplace_back(lpImageMng.getImage("player_attack")[16], 15);
	data.emplace_back(lpImageMng.getImage("player_attack")[17], 30);
	data.emplace_back(lpImageMng.getImage("player_attack")[18], 45);
	data.emplace_back(lpImageMng.getImage("player_attack")[19], 60);
	data.emplace_back(lpImageMng.getImage("player_attack")[20], 75);
	data.emplace_back(lpImageMng.getImage("player_attack")[21], 90);
	data.emplace_back(lpImageMng.getImage("player_attack")[22], 105);
	data.emplace_back(lpImageMng.getImage("player_attack")[23], 120);
	setAnm({ OBJ_STATE::A_WALK, DIR::RIGHT }, data);

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
		
		if (_state_dir.first == OBJ_STATE::JUMP)
		{
			_state_dir.second = DIR::LEFT;
		}
		else if (!lpKeyMng.getOldBuf()[KEY_INPUT_LEFT] || _state_dir.first != OBJ_STATE::WALK || _state_dir.second != DIR::LEFT)
		{
			setState({ OBJ_STATE::WALK, DIR::LEFT });
		}
		else
		{
			// ‚È‚µ
		}
	}
	else if (lpKeyMng.getBuf()[KEY_INPUT_RIGHT])
	{
		_pos.x += WALK_SPEED;

		if (_state_dir.first == OBJ_STATE::JUMP)
		{
			_state_dir.second = DIR::RIGHT;
		}
		else if (!lpKeyMng.getOldBuf()[KEY_INPUT_RIGHT] || _state_dir.first != OBJ_STATE::WALK || _state_dir.second != DIR::RIGHT)
		{
			setState({ OBJ_STATE::WALK, DIR::RIGHT });
		}
		else
		{
			// ‚È‚µ
		}
	}
	else
	{
		if ((lpKeyMng.getOldBuf()[KEY_INPUT_LEFT] || lpKeyMng.getOldBuf()[KEY_INPUT_RIGHT]) && _state_dir.first != OBJ_STATE::JUMP)
		{
			setState({ OBJ_STATE::NORMAL, _state_dir.second });
		}
	}

	if (CheckHitKey(KEY_INPUT_UP) && static_cast<int>(_tmpPos.y) + PLAYER_SIZE_Y / 2 == 1348)
	{
		_vel = INI_VEL_NORMAL;
		setState({ OBJ_STATE::JUMP, _state_dir.second });
	}

	if (lpKeyMng.getBuf()[KEY_INPUT_SPACE] && _coolTime == 0)
	{
		_anmEfkHd = lpEffectMng.playEffect(lpEffectMng.getEffect("magic_fire"), DELAY_FIRE);
		_coolTime = DELAY_FIRE;
		StateRotate();
		_control = &Player::ControlAttack;
	}
}

void Player::ControlAttack(void)
{
	if (lpKeyMng.getBuf()[KEY_INPUT_LEFT])
	{
		_pos.x -= WALK_SPEED;

		if (_state_dir.first == OBJ_STATE::A_JUMP)
		{
			if (_state_dir.second != DIR::LEFT)
			{
				_rotateFlag = true;
			}
			_state_dir.second = DIR::LEFT;
		}
		else if (!lpKeyMng.getOldBuf()[KEY_INPUT_LEFT] || _state_dir.first != OBJ_STATE::A_WALK || _state_dir.second != DIR::LEFT)
		{
			if (_state_dir.second != DIR::LEFT)
			{
				_rotateFlag = true;
			}
			setState({ OBJ_STATE::A_WALK, DIR::LEFT });
		}
		else
		{
			// ‚È‚µ
		}
	}
	else if (lpKeyMng.getBuf()[KEY_INPUT_RIGHT])
	{
		_pos.x += WALK_SPEED;

		if (_state_dir.first == OBJ_STATE::A_JUMP)
		{
			if (_state_dir.second != DIR::RIGHT)
			{
				_rotateFlag = true;
			}
			_state_dir.second = DIR::RIGHT;
		}
		else if (!lpKeyMng.getOldBuf()[KEY_INPUT_RIGHT] || _state_dir.first != OBJ_STATE::A_WALK || _state_dir.second != DIR::RIGHT)
		{
			if (_state_dir.second != DIR::RIGHT)
			{
				_rotateFlag = true;
			}
			setState({ OBJ_STATE::A_WALK, DIR::RIGHT });
		}
		else
		{
			// ‚È‚µ
		}
	}
	else
	{
		if ((lpKeyMng.getOldBuf()[KEY_INPUT_LEFT] || lpKeyMng.getOldBuf()[KEY_INPUT_RIGHT]) && _state_dir.first != OBJ_STATE::A_JUMP)
		{
			setState({ OBJ_STATE::A_NORMAL, _state_dir.second });
		}
	}

	if (CheckHitKey(KEY_INPUT_UP) && static_cast<int>(_tmpPos.y) + PLAYER_SIZE_Y / 2 == 1348)
	{
		_vel = INI_VEL_NORMAL;
		setState({ OBJ_STATE::A_JUMP, _state_dir.second });
	}
}

void Player::MagicUpdate(void)
{
	if (_coolTime != 0)
	{
		_coolTime--;
		if (_coolTime == 0)
		{
			_anmEfkHd = -1;
			_control = &Player::ControlNormal;
			StateRotate();
		}
	}
	if (_anmEfkHd != -1)
	{
		SetPosPlayingEffekseer2DEffect(_anmEfkHd, static_cast<float>(_pos.x + PLAYER_SIZE_X / 2 * (static_cast<int>(_state_dir.second) - 1)), static_cast<float>(_pos.y), 0.0f);
		if (_rotateFlag)
		{
			SetRotationPlayingEffekseer2DEffect(_anmEfkHd, 0.0f, (1 - static_cast<int>(_state_dir.second) / 2) * acos(-1.0f), 0.0f);
			_rotateFlag = false;
		}
	}
}

void Player::StateRotate(void)
{
	switch (_state_dir.first)
	{
	case OBJ_STATE::NORMAL:
		setState({ OBJ_STATE::A_NORMAL, _state_dir.second });
		break;
	case OBJ_STATE::WALK:
		setState({ OBJ_STATE::A_WALK, _state_dir.second });
		break;
	case OBJ_STATE::DASH:
		setState({ OBJ_STATE::A_DASH, _state_dir.second });
		break;
	case OBJ_STATE::JUMP:
		setState({ OBJ_STATE::A_JUMP, _state_dir.second });
		break;
	case OBJ_STATE::A_NORMAL:
		setState({ OBJ_STATE::NORMAL, _state_dir.second });
		break;
	case OBJ_STATE::A_WALK:
		setState({ OBJ_STATE::WALK, _state_dir.second });
		break;
	case OBJ_STATE::A_DASH:
		setState({ OBJ_STATE::DASH, _state_dir.second });
		break;
	case OBJ_STATE::A_JUMP:
		setState({ OBJ_STATE::JUMP, _state_dir.second });
		break;
	default:
		break;
	}
}

void Player::VelUpdate(void)
{
	if (static_cast<int>(_tmpPos.y) + PLAYER_SIZE_Y / 2 < 1348)
	{
		_vel = _vel - G_ACC_NORMAL;
	}

	if (_vel != 0 && static_cast<int>(_tmpPos.y) + PLAYER_SIZE_Y / 2 - _vel >= 1348)
	{
		_tmpPos.y = 1348.0 - PLAYER_SIZE_Y / 2;
		_vel = 0.0;
		if (lpKeyMng.getBuf()[KEY_INPUT_LEFT] || lpKeyMng.getBuf()[KEY_INPUT_RIGHT])
		{
			if (_state_dir.first == OBJ_STATE::A_JUMP)
			{
				setState({ OBJ_STATE::A_WALK, _state_dir.second });
			}
			else
			{
				setState({ OBJ_STATE::WALK, _state_dir.second });
			}
		}
		else
		{
			if (_state_dir.first == OBJ_STATE::A_JUMP)
			{
				setState({ OBJ_STATE::A_NORMAL,_state_dir.second });
			}
			else
			{
				setState({ OBJ_STATE::NORMAL, _state_dir.second });
			}
		}
	}

	//if (_vel < 0)
	//{
	//	setState({ OBJ_STATE::FALL, _state_dir.second });
	//}

	_tmpPos.y -= _vel;
	_type = OBJ_TYPE::PLAYER;

	_pos.y = static_cast<int>(_tmpPos.y);
}
