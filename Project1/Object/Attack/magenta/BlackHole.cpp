#include "BlackHole.h"
#include "../../../Graphic/ImageMng.h"
#include "../../../Audio/AudioContainer.h"
#include "../../../func/CheckHitStage.h"

namespace
{
	constexpr int FINISH_DURATION = 10;

	constexpr float MOVE_TARGET_DISTANCE = 4.0f;

	constexpr int RADIUS = 20;
	constexpr int DAMAGE = 1;
}

BlackHole::BlackHole(Vector2 pos, DIR dir, Vector2 vec, int lifetime, TIME time, int stage, OBJ_TYPE target)
{
	_pos = pos;
	_state_dir = { OBJ_STATE::NORMAL, dir };
	_vec.x = (static_cast<int>(dir) - 1)* vec.x;
	_time = time;
	_stage = stage;
	_target = target;
	_lifetime = lifetime;
	_timer = FINISH_DURATION;
	_exRate = 1.5;

	_rad = atan2(_vec.y, _vec.x);
	_update = &BlackHole::NormalUpdate;

	Init();
}

BlackHole::~BlackHole()
{
	stopAttack();
}

void BlackHole::NormalUpdate(void)
{
	_pos += _vec;
	_lifetime--;
	if (CheckHitStage()(static_cast<CHECK_DIR>(static_cast<int>(_state_dir.second) / 2), _pos, getHitOffset(), _stage) != NOTHIT || _lifetime < 0)
	{
		_update = &BlackHole::FinishUpdate;
		_alive = false;
		stopAttack();
	}
}

void BlackHole::FinishUpdate(void)
{
	_timer--;
	if (_timer < 0)
	{
		setState({ OBJ_STATE::DEAD, _state_dir.second });
	}
}

void BlackHole::Update(void)
{
	(this->*_update)();
}

void BlackHole::Draw(void)
{
	if (!anmUpdate())
	{
		return;
	}

	lpImageMng.AddDraw({ _anmMap[_state_dir][_anmFlame].first, _pos.x, _pos.y - _drawOffset_y, _exRate, _rad, LAYER::CHAR, _zOrder, DX_BLENDMODE_ALPHA, static_cast<int>(255.0f * static_cast<float>(_timer) / static_cast<float>(FINISH_DURATION)) });
}

void BlackHole::IfHitAttack(std::shared_ptr<Object> target)
{
	Vector2F move = Vector2F(static_cast<float>(_pos.x - target->getPosWithOffset().x), static_cast<float>(_pos.y - target->getPosWithOffset().y));
	float dist = move.Magnitude();
	if (dist == 0.0f)
	{
		move = { 0.0f, 0.0f };
	}
	else
	{
		move = move / dist * MOVE_TARGET_DISTANCE;
	}
	target->MovePos(Vector2(static_cast<int>(move.x), static_cast<int>(move.y)));

	if (dist <= RADIUS)
	{
		target->Object::damagingHP(DAMAGE);
		target->Object::setInv(1);
	}
}

void BlackHole::Init(void)
{
	lpImageMng.getImage("image/Attack/blackhole.png", "blackhole", 70, 70, 5, 2);

	AnmVec data;
	data.reserve(10);

	for (int i = 0; i < 10; i++)
	{
		data.emplace_back(lpImageMng.getImage("blackhole")[i], i + 1);
	}

	setAnm({ OBJ_STATE::NORMAL, _state_dir.second }, data);

	std::vector<atkData> attack;
	attack.reserve(2);

	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { -150, -150 }, { 150, 150 }, -1, 0, _target));
	attack.emplace_back(atkData(false, OBJ_TYPE::ATTACK, { 0, 0 }, { 0, 0 }, 0, -1, _target));

	setAttack("blackhole", attack);

	_type = OBJ_TYPE::ATTACK;
	setHitOffset({ 20,20,20,20 });

	AddAttack("blackhole");
}
