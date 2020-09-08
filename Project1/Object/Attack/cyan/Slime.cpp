#include "Slime.h"
#include "../../../Graphic/ImageMng.h"
#include "../../../func/CheckHitStage.h"
#include "../../../Audio/AudioContainer.h"
#include "../../../Scene/SceneMng.h"
#include "../../Player.h"

namespace
{
	AudioContainer _audio;
	constexpr int LIFE_TIME = 1200;

	constexpr int MOVE_SPEED = 6;

	constexpr int ATTACK_DURATION = 5;

	int slimeCount = 0;

	constexpr double G_ACC = 0.4;
	constexpr double ACC_MAX = 8.0;
}

Slime::Slime(const Vector2& pos, DIR dir, int stage, OBJ_TYPE target)
{
	_pos = pos;
	setState({ OBJ_STATE::NORMAL, dir });
	_target = target;
	_type = OBJ_TYPE::ATTACK;
	_time = TIME::FTR;
	_exRate = 2.0;
	_vel = 0.0;
	_tmpPos.y = static_cast<double>(_pos.y);
	_lifetime = LIFE_TIME;
	_stage = stage;
	slimeCount++;
	_isColored = true;

	setHitOffset({ 32, 32, 24, 24 });

	_update = &Slime::MoveUpdate;

	lpImageMng.getImage("image/Attack/slime-Sheet.png", "slime", 32, 25, 16, 3);

	AnmVec data;
	data.reserve(8);

	for (int i = 0; i < 8; i++)
	{
		data.emplace_back(lpImageMng.getImage("slime")[i], i * 3 + 1);
	}

	setAnm({ OBJ_STATE::NORMAL, DIR::LEFT }, data);

	for (int i = 0; i < 8; i++)
	{
		data.emplace_back(lpImageMng.getImage("slime")[15 - i], i * 3 + 1);
	}

	setAnm({ OBJ_STATE::NORMAL, DIR::RIGHT }, data);

	data.reserve(9);
	for (int i = 0; i < 8; i++)
	{
		data.emplace_back(lpImageMng.getImage("slime")[i + 16], i * 3 + 1);
	}
	data.emplace_back(-1, 0);
	setAnm({ OBJ_STATE::ATTACK, DIR::LEFT }, data);

	for (int i = 0; i < 8; i++)
	{
		data.emplace_back(lpImageMng.getImage("slime")[31 - i], i * 3 + 1);
	}
	data.emplace_back(-1, 0);
	setAnm({ OBJ_STATE::ATTACK, DIR::RIGHT }, data);

	data.reserve(6);
	for (int i = 0; i < 5; i++)
	{
		data.emplace_back(lpImageMng.getImage("slime")[i + 32], i * 3 + 1);
	}
	data.emplace_back(-1, -1);
	setAnm({ OBJ_STATE::DAMAGE, DIR::LEFT }, data);

	for (int i = 0; i < 5; i++)
	{
		data.emplace_back(lpImageMng.getImage("slime")[47 - i], i * 3 + 1);
	}
	data.emplace_back(-1, -1);
	setAnm({ OBJ_STATE::DAMAGE, DIR::RIGHT }, data);


	std::vector<atkData> attack;
	attack.reserve(2);
	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { -18, -18 }, { 18, 18 }, -1, 0, _target));
	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { 0, 0 }, { 0, 0 }, 0, -1, _target));
	setAttack("slime_find", attack);

	attack.reserve(6);
	for (int i = 0; i < 6; i++)
	{
		attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { -24, -24 }, { 32, 24 }, 2, ATTACK_DURATION, _target));
	}
	setAttack("slime_attack", attack);

	AddAttack("slime_find");

	_audio.LoadSound("sound/magic/slime_summon.wav", "summon", 10);
	_audio.ChangeVolume("summon", 180);
	PlaySoundMem(_audio.GetSound("summon"), DX_PLAYTYPE_BACK, true);

	_audio.LoadSound("sound/magic/enemy_dead.wav", "dead", 10);
	_audio.ChangeVolume("dead", 180);

	_audio.LoadSound("sound/magic/attack.wav", "attack", 10);
	_audio.ChangeVolume("attack", 180);
}

Slime::~Slime()
{
	slimeCount--;
}

void Slime::Update(void)
{
	_lifetime--;
	if (_timer > 0)
	{
		_timer--;
	}
	if (slimeCount == 1 && _isNewObject)
	{
		_isNewObject = false;
	}

	if (slimeCount >= 2 && _isNewObject == false && _update != &Slime::DeadUpdate)
	{
		_update = &Slime::DeadUpdate;
		setState({ OBJ_STATE::DAMAGE, _state_dir.second });
		PlaySoundMem(_audio.GetSound("dead"), DX_PLAYTYPE_BACK, true);
		stopAttack();
	}

	if (lpSceneMng.GetPlObj2(TIME::FTR)->getStage() != _stage && lpSceneMng.GetPlObj2(TIME::FTR)->getState().first != OBJ_STATE::DEAD)
	{
		setState({ OBJ_STATE::DEAD, _state_dir.second });
		PlaySoundMem(_audio.GetSound("dead"), DX_PLAYTYPE_BACK, true);
		stopAttack();
	}

	VelUpdate();
	(this->*_update)();
}

void Slime::IfHitAttack(std::shared_ptr<Object> target)
{
	if (_state_dir.first != OBJ_STATE::ATTACK && _timer == 0)
	{
		stopAttack();
		setState({ OBJ_STATE::ATTACK, _state_dir.second });
		_update = &Slime::AttackUpdate;
	}
}

void Slime::MoveUpdate(void)
{
	if (_lifetime <= 0)
	{
		_update = &Slime::DeadUpdate;
		setState({ OBJ_STATE::DAMAGE, _state_dir.second });
		PlaySoundMem(_audio.GetSound("dead"), DX_PLAYTYPE_BACK, true);
		stopAttack();
		return;
	}

	_pos.x += MOVE_SPEED * (static_cast<int>(_state_dir.second) - 1);

	if (_state_dir.second == DIR::LEFT)
	{
		int tl = CheckHitStage()(CHECK_DIR::LEFT, _pos, getHitOffset(), _stage);

		if (tl != NOTHIT)
		{
			_pos.x = tl + getHitOffset()[static_cast<int>(CHECK_DIR::LEFT)];
			setState({ OBJ_STATE::NORMAL , DIR::RIGHT});
		}
	}
	else
	{
		int tr = CheckHitStage()(CHECK_DIR::RIGHT, _pos, getHitOffset(), _stage);

		if (tr != NOTHIT)
		{
			_pos.x = tr - getHitOffset()[static_cast<int>(CHECK_DIR::RIGHT)];
			setState({ OBJ_STATE::NORMAL , DIR::LEFT });
		}
	}
}

void Slime::AttackUpdate(void)
{
	if (_anmTime == 2 * 3 + 1)
	{
		AddAttack("slime_attack");
		PlaySoundMem(_audio.GetSound("attack"), DX_PLAYTYPE_BACK, true);
	}
	if (_anmTime == 4 * 3 + 1)
	{
		stopAttack();
	}

	if (_state_dir.first == OBJ_STATE::NORMAL)
	{
		_update = &Slime::MoveUpdate;
		AddAttack("slime_find");
		_timer = ATTACK_DURATION;
	}
}

void Slime::DeadUpdate(void)
{
	if (!_alive)
	{
		setState({ OBJ_STATE::DEAD, _state_dir.second });
	}
}

void Slime::VelUpdate(void)
{
	int tmpDown = CheckHitStage()(CHECK_DIR::DOWN, { _pos.x, static_cast<int>(_tmpPos.y) }, getHitOffset(), _stage);
	if (tmpDown != NOTHIT)
	{
		_tmpPos.y = static_cast<double>(tmpDown) - (static_cast<double>(getHitOffset()[static_cast<int>(CHECK_DIR::DOWN)]));
		_vel = 0.0;
	}
	else
	{
		if (_vel + G_ACC > ACC_MAX)
		{
			_vel = ACC_MAX;
		}
		else
		{
			_vel += G_ACC;
		}

		tmpDown = CheckHitStage()(CHECK_DIR::DOWN, { _pos.x, static_cast<int>(_tmpPos.y + _vel) }, getHitOffset(), _stage);

		if (tmpDown != NOTHIT)
		{
			_tmpPos.y = static_cast<double>(tmpDown) - (static_cast<double>(getHitOffset()[static_cast<int>(CHECK_DIR::DOWN)]));
			_vel = 0.0;
		}
		else
		{
			_tmpPos.y += _vel;
		}
	}

	_pos.y = static_cast<int>(_tmpPos.y);
}
