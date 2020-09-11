#include "BlackHole.h"
#include "../../../Graphic/ImageMng.h"
#include "../../../Audio/AudioContainer.h"
#include "../../../func/CheckHitStage.h"

namespace
{
	AudioContainer _audio;
	constexpr int FINISH_DURATION = 10;

	constexpr float MOVE_TARGET_DISTANCE = 7.0f;

	constexpr float GRAVITY_RADIUS = 118.0f;
	constexpr int RADIUS = 20;
	constexpr int DAMAGE = 1;

	constexpr int B_SCREEN_SIZE = 256;
	constexpr unsigned int CIRCLE_COLOR = 0xdd00dd;
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
	_isColored = true;

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
	
	int tmps, tmpb, tmpp;
	ImageMng::GetCurrentScreen(&tmps, &tmpb, &tmpp);
	SetDrawScreen(_screen);
	ClsDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 140);
	DrawCircle(B_SCREEN_SIZE / 2, B_SCREEN_SIZE / 2, B_SCREEN_SIZE / 2 , CIRCLE_COLOR, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawRotaGraph(B_SCREEN_SIZE / 2, B_SCREEN_SIZE / 2, _exRate, _rad, _anmMap[_state_dir][_anmFlame].first, true);

	SetDrawScreen(tmps);
	SetDrawBlendMode(tmpb, tmpp);
	lpImageMng.AddDraw({ _screen, _pos.x, _pos.y - _drawOffset_y, 1.0, 0.0, LAYER::CHAR, _zOrder, DX_BLENDMODE_ALPHA, static_cast<int>(255.0f * static_cast<float>(_timer) / static_cast<float>(FINISH_DURATION)), true });
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

	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { 0, 0 }, GRAVITY_RADIUS, -1, 0, _target));
	attack.emplace_back(atkData(false, OBJ_TYPE::ATTACK, { 0, 0 }, GRAVITY_RADIUS, 0, -1, _target));

	setAttack("blackhole", attack);

	_type = OBJ_TYPE::ATTACK;
	setHitOffset({ 20,20,20,20 });

	AddAttack("blackhole");

	_screen = MakeScreen(B_SCREEN_SIZE, B_SCREEN_SIZE, true);

	_audio.LoadSound("sound/magic/blackhole.wav", "blackhole", 10);
	_audio.ChangeVolume("blackhole", 145);
	PlaySoundMem(_audio.GetSound("blackhole"), DX_PLAYTYPE_BACK, true);
}
