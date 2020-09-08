#include "FireBall.h"
#include "../../../Graphic/ImageMng.h"
#include "../../../Audio/AudioContainer.h"

namespace
{
	AudioContainer _audio;

	constexpr int EXPLOSION_DURATION = 16;
}

FireBall::FireBall(Vector2 pos, DIR dir, Vector2 vec, TIME time, int stage, OBJ_TYPE target)
{
	_pos = pos;
	_state_dir = { OBJ_STATE::NORMAL, dir };
	_vec.x = (static_cast<int>(dir) - 1) * vec.x;
	_time = time;
	_stage = stage;
	_target = target;
	_isColored = true;

	_rad = atan2(_vec.y, _vec.x);
	_update = &FireBall::FireballUpdate;

	Init();
}

FireBall::~FireBall()
{
	stopAttack();
}

void FireBall::FireballUpdate(void)
{
	_pos += _vec;
	if (CheckHitStage()(static_cast<CHECK_DIR>(static_cast<int>(_state_dir.second) / 2), _pos, getHitOffset(), _stage) != NOTHIT)
	{
		setState({ OBJ_STATE::A_NORMAL, _state_dir.second });
		_update = &FireBall::ExplosionUpdate;
		_exRate = 2.0;
		_alive = false;
		_timer = EXPLOSION_DURATION;
		PlaySoundMem(_audio.GetSound("explosion"), DX_PLAYTYPE_BACK, true);
	}
}

void FireBall::ExplosionUpdate(void)
{
	_timer--;
	if (_timer < 0)
	{
		setState({ OBJ_STATE::DEAD, _state_dir.second });
	}
}

void FireBall::Update(void)
{
	(this->*_update)();
}

void FireBall::IfHitAttack(std::shared_ptr<Object> target)
{
	if (_update == &FireBall::ExplosionUpdate)
	{
		return;
	}
	_update = &FireBall::ExplosionUpdate;
	setState({ OBJ_STATE::A_NORMAL, _state_dir.second });
	_exRate = 2.0;
	_alive = false;
	_timer = EXPLOSION_DURATION;
	PlaySoundMem(_audio.GetSound("explosion"), DX_PLAYTYPE_BACK, true);
}

void FireBall::Init(void)
{
	AnmVec data;
	data.reserve(30);

	for (int i = 0; i < 30; i++)
	{
		data.emplace_back(lpImageMng.getImage("fireball")[i], i + 1);
	}

	setAnm({ OBJ_STATE::NORMAL, _state_dir.second }, data);

	for (int i = 0; i < 8; i++)
	{
		data.emplace_back(lpImageMng.getImage("explosion")[i], (i + 1)* 2);
	}
	data.emplace_back(-1, -1);

	setAnm({ OBJ_STATE::A_NORMAL, _state_dir.second }, data);

	std::vector<atkData> attack;
	attack.reserve(31);
	for (int i = 0; i < 30; i++)
	{
		attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { 0, -6 }, { 20, 14 }, 20, 10, _target));
	}
	attack.emplace_back(atkData(false, OBJ_TYPE::ATTACK, { 0, 0 }, { 0, 0 }, 0, -1, _target));

	setAttack("fireball", attack);

	_audio.LoadSound("sound/magic/fireball.wav", "fireball", 10);
	_audio.ChangeVolume("fireball", 180);
	PlaySoundMem(_audio.GetSound("fireball"), DX_PLAYTYPE_BACK, true);

	_audio.LoadSound("sound/magic/explosion.wav", "explosion", 10);
	_audio.ChangeVolume("explosion", 180);

	_type = OBJ_TYPE::ATTACK;
	setHitOffset({ 20,0,6,14 });

	AddAttack("fireball");
}
