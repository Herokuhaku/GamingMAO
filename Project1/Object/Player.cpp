#include "Player.h"
#include "../Manage/Menu.h"
#include "../Manage/ItemTrader.h"
#include "../Manage/ButtonMng.h"
#include "../Scene/SceneMng.h"
#include "../Manage/KeyMng.h"
#include "../func/CheckHitStage.h"
#include "Attack/AttackMng.h"
#include "../Graphic/EffekseerMng.h"
#include "../Graphic/ImageMng.h"

Player::Player()
{
}

Player::Player(Vector2Template<int> pos, int stage, TIME time)
{
	_pos = pos;
	_tmpPos = {static_cast<double>(pos.x),static_cast<double>(pos.y)};
	_state_dir = { OBJ_STATE::NORMAL, DIR::RIGHT };
	_coolTime = 0;
	_rotateFlag = false;
	_control = &Player::ControlNormal;
	_type = OBJ_TYPE::PLAYER;

	setHitOffset({ 14,10,70,0 });
	_drawOffset_y = 45;

	_time = time;
	_stage = stage;
	MenuFlag = false;

	_anmEfkHd = -1;

	setHP(HP_MAX);
	_nextPos = { 0,0 };

	_magicSet = { ATK_TYPE::TYPE_1 };

	Init();
}

Player::~Player()
{
}

void Player::Update(void)
{
	VelUpdate();
	MagicUpdate();

	// 操作しているプレイヤーじゃない
	if (lpTimeMng.getTime() != _time);
	{
		StopWalk();
		return;
	}
	
	if (!MenuUpdate() && _time == lpTimeMng.getTime())
	{
		if (_state_dir.first != OBJ_STATE::DEAD && _state_dir.first != OBJ_STATE::DAMAGE)
		{
			(this->*_control)();
		}

		if (((lpKeyMng.getOldBuf()[KEY_INPUT_LSHIFT] && !lpKeyMng.getBuf()[KEY_INPUT_LSHIFT])) || 
			lpButtonMng.Buttonf(0,XINPUT_BUTTON_LEFT_SHOULDER).first == 0 && lpButtonMng.Buttonf(0,XINPUT_BUTTON_LEFT_SHOULDER).second == 1)
		{
			lpTimeMng.ChangeTime();
		}
	}
	else
	{
		StopWalk();
	}

	if (CheckHitKey(KEY_INPUT_T) || lpButtonMng.Buttonf(0, XINPUT_BUTTON_X).first == 1)
	{
		lpTradeMng.AddBag();
	}

	Portal();
}

void Player::Draw(void)
{
	Object::Draw();

	int tmpNum;
	for (int i = 0; i < 10; i++)
	{
		if (getHP() >= i * 10 + 1)
		{
			if (_state_dir.first == OBJ_STATE::DAMAGE)
			{
				tmpNum = 1;
			}
			else
			{
				tmpNum = 0;
			}
		}
		else
		{
			tmpNum = 2;
		}
		lpImageMng.AddDraw({ lpImageMng.getImage("hp_bar")[tmpNum], _pos.x - 27 + 6 * i, _pos.y - 60 - _drawOffset_y, 1.0, 0.0, LAYER::CHAR, 160, DX_BLENDMODE_NOBLEND, 0 });
	}
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

	data.reserve(2);
	data.emplace_back(lpImageMng.getImage("player_damaged")[0], 30);
	data.emplace_back(-1, 0);
	setAnm({ OBJ_STATE::DAMAGE, DIR::LEFT }, data);

	data.emplace_back(lpImageMng.getImage("player_damaged")[1], 30);
	data.emplace_back(-1, 0);
	setAnm({ OBJ_STATE::DAMAGE, DIR::RIGHT }, data);

	data.reserve(1);
	data.emplace_back(lpImageMng.getImage("player_damaged")[2], 3);
	setAnm({ OBJ_STATE::DEAD, DIR::LEFT } , data);

	data.emplace_back(lpImageMng.getImage("player_damaged")[3], 3);
	setAnm({ OBJ_STATE::DEAD, DIR::RIGHT }, data);


	std::vector<atkData> attack;
	attack.reserve(350);
	for (int i = 0; i < 100; i++)
	{
		attack.emplace_back(atkData(false, OBJ_TYPE::PLAYER, { 42,-55 }, { 16,-35 }, 10, 10, OBJ_TYPE::MAX));
	}
	for (int i = 100; i < 200; i++)
	{
		attack.emplace_back(atkData(true, OBJ_TYPE::PLAYER, { 42,-55 }, { 162,-35 }, 10, 10, OBJ_TYPE::MAX));
	}
	for (int i = 200; i < 220; i++)
	{
		attack.emplace_back(atkData(false, OBJ_TYPE::PLAYER, { 42,-55 }, { 162,-35 }, 10, 10, OBJ_TYPE::MAX));
	}
	setAttack("magic_fire", attack);

	_vel = 0.0;
	_tmpPos.y = static_cast<double>(_pos.y);

	// 攻撃の関数をまとめる
	_attack[static_cast<int>(COLOR::RED)]	[static_cast<int>(ATK_TYPE::TYPE_1)] = std::bind(&Player::Red1    , this);
	_attack[static_cast<int>(COLOR::RED)]	[static_cast<int>(ATK_TYPE::TYPE_2)] = std::bind(&Player::Red2    , this);
	_attack[static_cast<int>(COLOR::RED)]	[static_cast<int>(ATK_TYPE::TYPE_3)] = std::bind(&Player::Red3    , this);
	_attack[static_cast<int>(COLOR::GREEN)]	[static_cast<int>(ATK_TYPE::TYPE_1)] = std::bind(&Player::Green1  , this);
	_attack[static_cast<int>(COLOR::GREEN)]	[static_cast<int>(ATK_TYPE::TYPE_2)] = std::bind(&Player::Green2  , this);
	_attack[static_cast<int>(COLOR::GREEN)]	[static_cast<int>(ATK_TYPE::TYPE_3)] = std::bind(&Player::Green3  , this);
	_attack[static_cast<int>(COLOR::YELLOW)][static_cast<int>(ATK_TYPE::TYPE_1)] = std::bind(&Player::Yellow1, this);
	_attack[static_cast<int>(COLOR::YELLOW)][static_cast<int>(ATK_TYPE::TYPE_2)] = std::bind(&Player::Yellow1, this);
	_attack[static_cast<int>(COLOR::YELLOW)][static_cast<int>(ATK_TYPE::TYPE_3)] = std::bind(&Player::Yellow3, this);
	_attack[static_cast<int>(COLOR::BLUE)]	[static_cast<int>(ATK_TYPE::TYPE_1)] = std::bind(&Player::Blue1   , this);
	_attack[static_cast<int>(COLOR::BLUE)]	[static_cast<int>(ATK_TYPE::TYPE_2)] = std::bind(&Player::Blue2   , this);
	_attack[static_cast<int>(COLOR::BLUE)]	[static_cast<int>(ATK_TYPE::TYPE_3)] = std::bind(&Player::Blue3   , this);
	_attack[static_cast<int>(COLOR::MAGENTA)]	[static_cast<int>(ATK_TYPE::TYPE_1)] = std::bind(&Player::Magenta1, this);
	_attack[static_cast<int>(COLOR::MAGENTA)]	[static_cast<int>(ATK_TYPE::TYPE_2)] = std::bind(&Player::Magenta2, this);
	_attack[static_cast<int>(COLOR::MAGENTA)]	[static_cast<int>(ATK_TYPE::TYPE_3)] = std::bind(&Player::Magenta3, this);
	_attack[static_cast<int>(COLOR::CYAN)]	[static_cast<int>(ATK_TYPE::TYPE_1)] = std::bind(&Player::Cyan1   , this);
	_attack[static_cast<int>(COLOR::CYAN)]	[static_cast<int>(ATK_TYPE::TYPE_2)] = std::bind(&Player::Cyan2   , this);
	_attack[static_cast<int>(COLOR::CYAN)]	[static_cast<int>(ATK_TYPE::TYPE_3)] = std::bind(&Player::Cyan3   , this);
	_attack[static_cast<int>(COLOR::WHITE)]	[static_cast<int>(ATK_TYPE::TYPE_1)] = std::bind(&Player::White1  , this);
	_attack[static_cast<int>(COLOR::WHITE)]	[static_cast<int>(ATK_TYPE::TYPE_2)] = std::bind(&Player::White2  , this);
	_attack[static_cast<int>(COLOR::WHITE)]	[static_cast<int>(ATK_TYPE::TYPE_3)] = std::bind(&Player::White3  , this);
}

void Player::ControlNormal(void)
{
	if (lpKeyMng.getBuf()[KEY_INPUT_LEFT] || lpButtonMng.Thumbf(0,XINPUT_THUMBL_X).first == 2)
	{
		if (_state_dir.first == OBJ_STATE::JUMP)
		{
			_state_dir.second = DIR::LEFT;
		}
		else if (!lpKeyMng.getOldBuf()[KEY_INPUT_LEFT] && lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second == 0 || _state_dir.first != OBJ_STATE::WALK || _state_dir.second != DIR::LEFT)
		{
			setState({ OBJ_STATE::WALK, DIR::LEFT });
		}
		else
		{
			// なし
		}

		int tmpLeft = CheckHitStage()(CHECK_DIR::LEFT, { _pos.x - WALK_SPEED, _pos.y }, getHitOffset(),_stage);
		if (tmpLeft == NOTHIT)
		{
			_pos.x -= WALK_SPEED;
		}
		else
		{
			_pos.x = tmpLeft + getHitOffset()[static_cast<int>(CHECK_DIR::LEFT)];
		}
	}
	else if (lpKeyMng.getBuf()[KEY_INPUT_RIGHT] || lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).first == 1)
	{
		if (_state_dir.first == OBJ_STATE::JUMP)
		{
			_state_dir.second = DIR::RIGHT;
		}
		else if (!lpKeyMng.getOldBuf()[KEY_INPUT_RIGHT] && lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second == 0 || _state_dir.first != OBJ_STATE::WALK || _state_dir.second != DIR::RIGHT)
		{
			setState({ OBJ_STATE::WALK, DIR::RIGHT });
		}
		else
		{
			// なし
		}

		int tmpRight = CheckHitStage()(CHECK_DIR::RIGHT, { _pos.x + WALK_SPEED, _pos.y }, getHitOffset(),_stage);
		if (tmpRight == NOTHIT)
		{
			_pos.x += WALK_SPEED;
		}
		else
		{
			_pos.x = tmpRight - getHitOffset()[static_cast<int>(CHECK_DIR::RIGHT)];
		}
	}
	else
	{
		if ((lpKeyMng.getOldBuf()[KEY_INPUT_LEFT] || lpKeyMng.getOldBuf()[KEY_INPUT_RIGHT] ||
			lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second != 0) && _state_dir.first != OBJ_STATE::JUMP)
		{
			setState({ OBJ_STATE::NORMAL, _state_dir.second });
		}
	}

	if ((CheckHitKey(KEY_INPUT_UP) || lpButtonMng.Buttonf(0, XINPUT_BUTTON_A).first == 1) && CheckHitStage()(CHECK_DIR::DOWN, { _pos.x, static_cast<int>(_tmpPos.y) + 1 }, getHitOffset(),_stage) != NOTHIT)
	{
		_vel = INI_VEL_NORMAL;
		setState({ OBJ_STATE::JUMP, _state_dir.second });
	}

	if (lpAttackUI.CheckAttackActivate())
	{
		_control = &Player::ControlAttack;
		StateRotate();
	}
}

void Player::ControlAttack(void)
{
	if (lpKeyMng.getBuf()[KEY_INPUT_LEFT] || lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).first == 2)
	{
		if (_state_dir.first == OBJ_STATE::A_JUMP)
		{
			if (_state_dir.second != DIR::LEFT)
			{
				_rotateFlag = true;
			}
			_state_dir.second = DIR::LEFT;
		}
		else if (!lpKeyMng.getOldBuf()[KEY_INPUT_LEFT] && lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second == 0 || _state_dir.first != OBJ_STATE::A_WALK || _state_dir.second != DIR::LEFT)
		{
			if (_state_dir.second != DIR::LEFT)
			{
				_rotateFlag = true;
			}
			setState({ OBJ_STATE::A_WALK, DIR::LEFT });
		}
		else
		{
			// なし
		}

		int tmpLeft = CheckHitStage()(CHECK_DIR::LEFT, { _pos.x - WALK_SPEED, _pos.y }, getHitOffset(),_stage);
		if (tmpLeft == NOTHIT)
		{
			_pos.x -= WALK_SPEED;
		}
		else
		{
			_pos.x = tmpLeft + getHitOffset()[static_cast<int>(CHECK_DIR::LEFT)];
		}
	}
	else if (lpKeyMng.getBuf()[KEY_INPUT_RIGHT] || lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).first == 1)
	{
		if (_state_dir.first == OBJ_STATE::A_JUMP)
		{
			if (_state_dir.second != DIR::RIGHT)
			{
				_rotateFlag = true;
			}
			_state_dir.second = DIR::RIGHT;
		}
		else if (!lpKeyMng.getOldBuf()[KEY_INPUT_RIGHT] && lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second == 0 || _state_dir.first != OBJ_STATE::A_WALK || _state_dir.second != DIR::RIGHT)
		{
			if (_state_dir.second != DIR::RIGHT)
			{
				_rotateFlag = true;
			}
			setState({ OBJ_STATE::A_WALK, DIR::RIGHT });
		}
		else
		{
			// なし
		}

		int tmpRight = CheckHitStage()(CHECK_DIR::RIGHT, { _pos.x + WALK_SPEED, _pos.y }, getHitOffset(),_stage);
		if (tmpRight == NOTHIT)
		{
			_pos.x += WALK_SPEED;
		}
		else
		{
			_pos.x = tmpRight - getHitOffset()[static_cast<int>(CHECK_DIR::RIGHT)];
		}
	}
	else
	{
		if ((lpKeyMng.getOldBuf()[KEY_INPUT_LEFT] || lpKeyMng.getOldBuf()[KEY_INPUT_RIGHT] ||
			lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second != 0) && _state_dir.first != OBJ_STATE::JUMP)
		{
			setState({ OBJ_STATE::A_NORMAL, _state_dir.second });
		}
	}

 	if ((CheckHitKey(KEY_INPUT_UP) || lpButtonMng.Buttonf(0,XINPUT_BUTTON_A).first == 1)&& CheckHitStage()(CHECK_DIR::DOWN, { _pos.x, static_cast<int>(_tmpPos.y) + 1 }, getHitOffset(),_stage) != NOTHIT)
	{
		_vel = INI_VEL_NORMAL;
		setState({ OBJ_STATE::A_JUMP, _state_dir.second });
	}

	if (_coolTime == 0)
	{
		if (!lpAttackUI.CheckAttackActivate())
		{
			COLOR&& color = lpAttackUI.RunAttack(10);
			if (static_cast<int>(color) >= static_cast<int>(COLOR::RED) && static_cast<int>(color) < static_cast<int>(COLOR::MAX))
			{
				_attack[static_cast<int>(color)][static_cast<int>(_magicSet[static_cast<int>(color)])]();
			}
			_coolTime = 10;
		}
	}
}

void Player::StopWalk(void)
{
	if (_state_dir.first == OBJ_STATE::DASH || _state_dir.first == OBJ_STATE::WALK)
	{
		setState({ OBJ_STATE::NORMAL, _state_dir.second });
	}
	if (_state_dir.first == OBJ_STATE::A_DASH || _state_dir.first == OBJ_STATE::A_WALK)
	{
		setState({ OBJ_STATE::A_NORMAL, _state_dir.second });
	}
}

void Player::MagicUpdate(void)
{	
	if (_coolTime != 0)
	{
		_coolTime--;
		if (_coolTime == 0)
		{
			//_anmEfkHd = -1;
			_control = &Player::ControlNormal;
			StateRotate();
		}
	}

	

	if (_anmEfkHd != -1)
	{
		//SetPosPlayingEffekseer2DEffect(_anmEfkHd, static_cast<float>(_pos.x + PLAYER_SIZE_X / 2 * (static_cast<int>(_state_dir.second) - 1)), static_cast<float>(_pos.y), 0.0f);
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
	if (CheckHitStage()(CHECK_DIR::DOWN, { _pos.x, static_cast<int>(_tmpPos.y) + 1 }, getHitOffset(),_stage) == NOTHIT)
	{
		if (_vel - G_ACC_NORMAL > -VEL_MAX)
		{
			_vel = _vel - G_ACC_NORMAL;
		}
		else
		{
			_vel = -VEL_MAX;
		}
	}

	int tmpDown = CheckHitStage()(CHECK_DIR::DOWN, { _pos.x, static_cast<int>(_tmpPos.y - _vel) }, getHitOffset(),_stage);

	if (_vel != 0.0 && tmpDown != NOTHIT)
	{
		_tmpPos.y = tmpDown - 1;
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

	_tmpPos.y -= _vel;
	_type = OBJ_TYPE::PLAYER;

	_pos.y = static_cast<int>(_tmpPos.y);

}

bool Player::MenuUpdate(void)
{
	if ((lpButtonMng.Buttonf(0, XINPUT_BUTTON_BACK).first == 1 &&
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_BACK).second == 0) && _time == lpTimeMng.getTime())
	{
		MenuFlag = true;
	}

	if (MenuFlag && _time == lpTimeMng.getTime())
	{
		MenuFlag = lpMenuMng.Update();
		return MenuFlag;
	}
	return false;
}

void Player::Attack(void)
{

}

void Player::Portal(void)
{
	if ((lpKeyMng.getOldBuf()[KEY_INPUT_DOWN] && !lpKeyMng.getBuf()[KEY_INPUT_DOWN]) ||
		(lpButtonMng.Buttonf(0, XINPUT_BUTTON_Y).first == 1 && lpButtonMng.Buttonf(0, XINPUT_BUTTON_Y).second == 0))
	{
		// 
		bool flag =
			std::pow(lpMapMng.GetPortal()->Spos.x - _pos.x, 2.0) +
			std::pow(lpMapMng.GetPortal()->Spos.y + 50 - _pos.y, 2.0)
			<= 900 ? true : false;
		// 900は正しい値じゃない
		// 

		int y = _pos.y - 50;
		// if(座標を見て一番右のポータル)
		if (lpMapMng.getGameMapM({ _pos.x,y }, _stage) == 41)
		{
			_nextPos = { lpMapMng.GetFrontPosX(_stage),lpMapMng.GetFrontPosY(_stage) };
			lpImageMng.SetplmoveF(true, MAP_DATA::FRONT);
			lpImageMng.setGkind(ScrEff::FADEOUT);
		}
		// if(座標を見て一番左のポータル)
		else if (lpMapMng.getGameMapM({ _pos.x,y }, _stage) == 9)
		{
			_nextPos = { lpMapMng.GetBackPosX(_stage),lpMapMng.GetBackPosY(_stage) };
			lpImageMng.SetplmoveF(true, MAP_DATA::BACK);
			lpImageMng.setGkind(ScrEff::FADEOUT);
		}
		// if(座標 真ん中のポータル)
		else if (flag)
		{
			_nextPos = { lpMapMng.GetBrancPosX(_stage),lpMapMng.GetBrancPosY(_stage) };
			lpMapMng.setstageF(false);
			lpImageMng.SetplmoveF(true, MAP_DATA::BRANCH);
			lpImageMng.setGkind(ScrEff::FADEOUT);

		}
		// ポータルスタート
		else if (std::pow(lpMapMng.GetPortal2()->Spos.x - _pos.x, 2.0) +
			std::pow(lpMapMng.GetPortal2()->Spos.y + 50 - _pos.y, 2.0)
			<= 900)
		{
			(*lpSceneMng.GetPlObj(lpTimeMng.getTime()))->setPos(lpMapMng.GetPortal2()->Epos);
			(*lpSceneMng.GetPlObj(lpTimeMng.getTime()))->setPlTmpPos(lpMapMng.GetPortal2()->Epos);
		}
		// ポータルエンド
		else if (std::pow(lpMapMng.GetPortal2()->Epos.x - _pos.x, 2.0) +
			std::pow(lpMapMng.GetPortal2()->Epos.y + 50 - _pos.y, 2.0)
			<= 900)
		{
			(*lpSceneMng.GetPlObj(lpTimeMng.getTime()))->setPos(lpMapMng.GetPortal2()->Spos);
			(*lpSceneMng.GetPlObj(lpTimeMng.getTime()))->setPlTmpPos(lpMapMng.GetPortal2()->Spos);
		}
		else
		{
		}
	}
}

void Player::Red1(void)
{
	lpAtkMng.MakeFireBall({ _pos.x + (static_cast<int>(_state_dir.second) - 1) * PLAYER_SIZE_X / 2, _pos.y - _drawOffset_y }, _state_dir.second,
		{ 6, 0 }, _time, _stage, OBJ_TYPE::ENEMY);
}

void Player::Red2(void)
{
}

void Player::Red3(void)
{
}

void Player::Green1(void)
{
	lpAtkMng.MakeFruit({ _pos.x + (static_cast<int>(_state_dir.second) - 1) * PLAYER_SIZE_X / 2, _pos.y - _drawOffset_y }, _state_dir.second, 4, _time, _stage, OBJ_TYPE::ENEMY);
}

void Player::Green2(void)
{
}

void Player::Green3(void)
{
}

void Player::Yellow1(void)
{
	lpAtkMng.MakeThunderCloud({ _pos.x + (static_cast<int>(_state_dir.second) - 1) * 30, _pos.y - 300 }, _state_dir.second, 3, 3, 60, _time, _stage, OBJ_TYPE::ENEMY);
}

void Player::Yellow2(void)
{
}

void Player::Yellow3(void)
{
}

void Player::Blue1(void)
{
	lpAtkMng.MakeBubble(_pos, _time, _stage, OBJ_TYPE::ENEMY);
}

void Player::Blue2(void)
{
}

void Player::Blue3(void)
{
}

void Player::Magenta1(void)
{
	lpAtkMng.MakePoisonFog({ _pos.x +(static_cast<int>(_state_dir.second) - 1) * 160, _pos.y - 60 }, 180, _time, _stage, OBJ_TYPE::ENEMY);
}

void Player::Magenta2(void)
{
}

void Player::Magenta3(void)
{
}

void Player::Cyan1(void)
{
	lpAtkMng.MakeIceWall({ _pos.x, _pos.y - 40 }, _time, _stage, OBJ_TYPE::ENEMY);
}

void Player::Cyan2(void)
{
}

void Player::Cyan3(void)
{
}

void Player::White1(void)
{
	lpAtkMng.MakeHolyJudge({ _pos.x + (static_cast<int>(_state_dir.second) - 1) * 250, _pos.y }, _time, _stage, OBJ_TYPE::ENEMY);
}

void Player::White2(void)
{
}

void Player::White3(void)
{
}
