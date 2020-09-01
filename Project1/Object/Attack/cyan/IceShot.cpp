#include "IceShot.h"
#include "../../../func/CheckHitStage.h"
#include "../../../Graphic/ImageMng.h"
#include "../../Player.h"
#include "../white/StopTime.h"
#include "../../../Scene/SceneMng.h"
#define _USE_MATH_DEFINES
#include <math.h>

namespace
{
	constexpr int ANM_SPEED = 3;

	constexpr int CHARGE_FLAME = 3;
	constexpr int CHARGE_DURATION = ANM_SPEED * CHARGE_FLAME;

	constexpr int SHOT_FLAME = 3;
	constexpr int SHOT_DURATION = ANM_SPEED * SHOT_FLAME;

	constexpr int EFFECT_DURATION = 12;

	constexpr int ICE_SCREEN_SIZE = 256;
}

IceShot::IceShot(std::weak_ptr<Object> owner, Vector2 offset, DIR dir, Vector2 vec, TIME time, int stage, OBJ_TYPE target):_owner(owner)
{
	_state_dir = { OBJ_STATE::NORMAL, dir };
	_offset = offset;
	_vec = vec;
	_time = time;
	_stage = stage;
	_target = target;
	_type = OBJ_TYPE::ATTACK;
	_timer = 0;

	_rad = atan2(_vec.y, _vec.x);
	_exRate = 1.0;

	_zOrder = 30;

	_update = &IceShot::ChargeUpdate;
	_draw = &IceShot::ChargeDraw;

	_screen = MakeScreen(ICE_SCREEN_SIZE, ICE_SCREEN_SIZE, true);

	Init();
}

IceShot::~IceShot()
{
}

void IceShot::Update(void)
{
	if (_owner.expired())
	{
		setState({ OBJ_STATE::DEAD, _state_dir.second });
		_alive = false;
	}

	if (_state_dir.second != DIR::NORMAL)
	{
		_rad = _owner.lock()->getState().second == DIR::LEFT ? M_PI : 0.0;
	}

	(this->*_update)();
}

void IceShot::Draw(void)
{
	(this->*_draw)();
}

void IceShot::IfHitAttack(std::shared_ptr<Object> target)
{
	_timer = EFFECT_DURATION;
	lpImageMng.playEffect("ice_shot", &_pos.x, &_pos.y, 1.0, _rad, LAYER::CHAR, _zOrder + 1, DX_BLENDMODE_NOBLEND, 0, _stage, EffectDrawType::DRAW_TO_RELATIVE);
	_update = &IceShot::DestroyUpdate;
	_draw = &IceShot::FlyingDraw;
	stopAttack();

	target->SetStateEffect(new StateEffect(STATE_EFFECT_TYPE::FREEZE, 200));
}

void IceShot::Init(void)
{
	lpImageMng.getImage("image/Attack/ice_shot.png", "ice_shot", 128, 128, 7, 1);
	lpImageMng.getImage("image/Attack/ice_shot_effect.png", "ice_shot_effect", 128, 128, 4, 1);
	
	EffectData effect;
	effect.reserve(5);

	for (int i = 0; i < 4; i++)
	{
		effect.emplace_back(lpImageMng.getImage("ice_shot_effect")[i], (i + 1) * 3);
	}
	effect.emplace_back(0, -1);
	lpImageMng.setEffect("ice_shot", effect);

	std::vector<atkData> attack;
	attack.reserve(2);
	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { -32, -16 }, { 32, 16 }, 30, 10, _target));
	attack.emplace_back(atkData(false, OBJ_TYPE::ATTACK, { 0, 0 }, { 0, 0 }, 0, -1, _target));

	setAttack("ice_shot", attack);

	setHitOffset({ 32, 32, 16, 16 });
}

void IceShot::ChargeUpdate(void)
{
	_timer++;
	if (_timer >= CHARGE_DURATION)
	{
		_update = &IceShot::ShotUpdate;
		_draw = &IceShot::ShotDraw;
		_timer = 0;
		if (!_owner.expired())
		{
			if (_state_dir.second != DIR::NORMAL)
			{
				Vector2 pos = { _owner.lock()->getPos().x + (_offset.x * (static_cast<int>(_owner.lock()->getState().second) - 1)), _owner.lock()->getPos().y + _offset.y };
				_vec.x = _vec.x * (static_cast<int>(_owner.lock()->getState().second) - 1);
				_pos = pos;
				_shotRad = _rad;
			}
			else
			{
				_pos = _owner.lock()->getPos();
				_shotRad = _rad;
			}
			AddAttack("ice_shot");
		}
	}
}

void IceShot::ShotUpdate(void)
{
	_timer++;
	
	if (_timer >= ANM_SPEED)
	{
		FlyingUpdate();
	}

	if (_timer > SHOT_DURATION)
	{
		_update = &IceShot::FlyingUpdate;
		_draw = &IceShot::FlyingDraw;
		_timer = 0;
	}
}

void IceShot::FlyingUpdate(void)
{
	_pos += _vec;
	if (CheckHitStage()(static_cast<CHECK_DIR>(static_cast<int>(_state_dir.second) / 2), _pos, getHitOffset(), _stage) != NOTHIT)
	{
		_timer = EFFECT_DURATION;
		lpImageMng.playEffect("ice_shot", &_pos.x, &_pos.y, 1.0, _rad, LAYER::CHAR, _zOrder + 1, DX_BLENDMODE_NOBLEND, 0, _stage, EffectDrawType::DRAW_TO_RELATIVE);
		_update = &IceShot::DestroyUpdate;
		_draw = &IceShot::FlyingDraw;
		stopAttack();
	}
}

void IceShot::DestroyUpdate(void)
{
	_timer--;
	if (_timer < 0)
	{
		setState({ OBJ_STATE::DEAD, _state_dir.second });
		_alive = false;
	}
}

void IceShot::ChargeDraw(void)
{
	Vector2 op = _owner.lock()->getPos();
	if (_state_dir.second != DIR::NORMAL)
	{
		std::pair<OBJ_STATE, DIR> sd = _owner.lock()->getState();
		lpImageMng.AddDraw({ lpImageMng.getImage("ice_shot")[_timer / ANM_SPEED], op.x + (_offset.x * (static_cast<int>(sd.second) - 1)), op.y + _offset.y, _exRate, _rad, LAYER::CHAR, _zOrder, DX_BLENDMODE_NOBLEND, 0 });
	}
	else
	{
		lpImageMng.AddDraw({ lpImageMng.getImage("ice_shot")[_timer / ANM_SPEED], op.x + _offset.x, op.y + _offset.y, _exRate, _rad, LAYER::CHAR, _zOrder, DX_BLENDMODE_NOBLEND, 0 });
	}
}

void IceShot::ShotDraw(void)
{
	SetDrawScreen(_screen);
	ClsDrawScreen();

	if (!_owner.expired())
	{
		Vector2 op = _owner.lock()->getPos();
		if (_state_dir.second != DIR::NORMAL)
		{
			std::pair<OBJ_STATE, DIR> sd = _owner.lock()->getState();
			DrawRotaGraph2(ICE_SCREEN_SIZE / 2, ICE_SCREEN_SIZE / 2, ICE_SCREEN_SIZE / 8, ICE_SCREEN_SIZE / 4, _exRate, _rad, lpImageMng.getImage("ice_shot")[_timer / ANM_SPEED + CHARGE_FLAME], true);
			lpImageMng.AddDraw({ _screen, op.x + (_offset.x * (static_cast<int>(sd.second) - 1)), op.y + _offset.y, 1.0, 0.0, LAYER::CHAR, _zOrder - 1, DX_BLENDMODE_NOBLEND, 0 });
		}
		else
		{
			DrawRotaGraph2(ICE_SCREEN_SIZE / 2, ICE_SCREEN_SIZE / 2, ICE_SCREEN_SIZE / 8, ICE_SCREEN_SIZE / 4, _exRate, _rad, lpImageMng.getImage("ice_shot")[_timer / ANM_SPEED + CHARGE_FLAME], true);
			lpImageMng.AddDraw({ _screen, op.x + _offset.x, op.y + _offset.y, 1.0, 0.0, LAYER::CHAR, _zOrder - 1, DX_BLENDMODE_NOBLEND, 0 });
		}
	}
	lpImageMng.AddDraw({ lpImageMng.getImage("ice_shot")[CHARGE_FLAME + SHOT_FLAME], _pos.x, _pos.y, _exRate, _shotRad, LAYER::CHAR, _zOrder, DX_BLENDMODE_NOBLEND, 0 });
}

void IceShot::FlyingDraw(void)
{
	if (_update == &IceShot::DestroyUpdate)
	{
		return;
	}
	lpImageMng.AddDraw({ lpImageMng.getImage("ice_shot")[CHARGE_FLAME + SHOT_FLAME], _pos.x, _pos.y, _exRate, _shotRad, LAYER::CHAR, _zOrder, DX_BLENDMODE_NOBLEND, 0 });
}
