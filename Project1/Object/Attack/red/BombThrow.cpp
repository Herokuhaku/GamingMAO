#include "BombThrow.h"
#include "../../../func/CheckHitStage.h"
#include "../../../Graphic/ImageMng.h"
#include "../../../Audio/AudioContainer.h"

namespace
{
	AudioContainer _audio;

	constexpr int EXPLOSION_DURATION = 16;

	constexpr int ATTACK_RADIUS = 22;
}

BombThrow::BombThrow(Vector2 pos, DIR dir, int speed, double vel, TIME time, int stage, OBJ_TYPE target)
{
	_pos = pos;
	_speed = (static_cast<int>(dir) - 1) * speed;
	_vel = vel;
	_time = time;
	_stage = stage;
	_rad = 0.0;
	_target = target;
	_isColored = true;

	_type = OBJ_TYPE::ATTACK;
	_update = &BombThrow::BombUpdate;

	setHitOffset({ 22, 22, 22, 22 });

	_tmpPos.y = static_cast<double>(_pos.y);

	setState({ OBJ_STATE::NORMAL, dir });

	Init();
}

BombThrow::~BombThrow()
{
}

void BombThrow::Update(void)
{
	(this->*_update)();
}

void BombThrow::IfHitAttack(std::shared_ptr<Object> target)
{
	if (_update == &BombThrow::BombUpdate)
	{
		_update = &BombThrow::ExplosionUpdate;
		setState({ OBJ_STATE::A_NORMAL, _state_dir.second });
		_exRate = 2.0;
		_timer = EXPLOSION_DURATION;
		PlaySoundMem(_audio.GetSound("explosion"), DX_PLAYTYPE_BACK, true);
		stopAttack();
		AddAttack("explosion");
	}
}

void BombThrow::Init(void)
{
	AnmVec data;

	data.emplace_back(lpImageMng.getImage("bomb")[0], 5);
	data.emplace_back(lpImageMng.getImage("bomb")[1], 10);

	setAnm({ OBJ_STATE::NORMAL, _state_dir.second }, data);

	for (int i = 0; i < 8; i++)
	{
		data.emplace_back(lpImageMng.getImage("explosion")[i], (i + 1) * 2);
	}
	data.emplace_back(-1, -1);

	setAnm({ OBJ_STATE::A_NORMAL, _state_dir.second }, data);

	std::vector<atkData> attack;
	attack.reserve(2);
	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { 0, 0 }, static_cast<float>(ATTACK_RADIUS), -1, 0, _target));
	attack.emplace_back(atkData(false, OBJ_TYPE::ATTACK, { 0, 0 }, static_cast<float>(ATTACK_RADIUS), 0, -1, _target));

	setAttack("bomb", attack);

	attack.reserve(2);
	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { 0, 0 }, static_cast<float>(ATTACK_RADIUS), 30, 20, _target));
	attack.emplace_back(atkData(false, OBJ_TYPE::ATTACK, { 0, 0 }, static_cast<float>(ATTACK_RADIUS), 0, -1, _target));

	setAttack("explosion", attack);

	AddAttack("bomb");

	_audio.LoadSound("sound/magic/explosion.wav", "explosion", 10);
	_audio.ChangeVolume("explosion", 135);
}

void BombThrow::BombUpdate(void)
{
	_rad += (static_cast<double>(static_cast<int>(_state_dir.second)) - 1.0) * RAD_VEL;

	_pos.x += _speed;

	VelUpdate();

	if ((CheckHitStage()(CHECK_DIR::UP, { _pos.x, static_cast<int>(_tmpPos.y) }, getHitOffset(), _stage) != NOTHIT) || 
		(CheckHitStage()(CHECK_DIR::DOWN, { _pos.x, static_cast<int>(_tmpPos.y) }, getHitOffset(), _stage) != NOTHIT) || 
		(CheckHitStage()(CHECK_DIR::LEFT, { _pos.x, static_cast<int>(_tmpPos.y) }, getHitOffset(), _stage) != NOTHIT) || 
		CheckHitStage()(CHECK_DIR::RIGHT, { _pos.x, static_cast<int>(_tmpPos.y) }, getHitOffset(), _stage) != NOTHIT)
	{
		_update = &BombThrow::ExplosionUpdate;
		setState({ OBJ_STATE::A_NORMAL, _state_dir.second });
		_exRate = 2.0;
		_timer = EXPLOSION_DURATION;
		PlaySoundMem(_audio.GetSound("explosion"), DX_PLAYTYPE_BACK, true);
		stopAttack();
		AddAttack("explosion");
	}
}

void BombThrow::ExplosionUpdate(void)
{
	_timer--;
	if (_timer < 0)
	{
		setState({ OBJ_STATE::DEAD, _state_dir.second });
		_alive = false;
	}
}

void BombThrow::VelUpdate(void)
{
	_vel = min(_vel - G_ACC, ACC_MAX);

	_tmpPos.y -= _vel;

	_pos.y = static_cast<int>(_tmpPos.y);
}

