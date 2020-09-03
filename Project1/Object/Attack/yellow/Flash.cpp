#include "Flash.h"
#include "../../../Scene/SceneMng.h"
#include "../../../Graphic/ImageMng.h"

namespace
{
	constexpr int LIFE_TIME = 30;
	constexpr int EXPAND_INTERVAL = 5;
	constexpr int SHRINK_INTERVAL = LIFE_TIME - EXPAND_INTERVAL;

	constexpr float VERTEX_LENGTH_MAX = 300.0f;

	constexpr int ATTACK_RANGE_MAX = 210;

	constexpr float ANGLE_DIFF = DX_PI_F / 18.0f;

	std::array<unsigned short, 108> _verIndex;
	int screen;
	int drawscreen;
	bool _initialized = false;
}

Flash::Flash(Vector2* pos, TIME time, int stage, OBJ_TYPE target)
{
	_ownerPos = pos;
	_pos = *pos;
	_time = time;
	_stage = stage;
	_target = target;
	_timer = 0;
	_update = &Flash::ExpandUpdate;
	setState({ OBJ_STATE::NORMAL, DIR::RIGHT });

	_exRate = 1.0;
	_rad = 0.0;
	_zOrder = 300;

	Vector2D cpos = lpSceneMng.GetcPos();
	VERTEX2D ver;
	ver.pos = { VERTEX_LENGTH_MAX, VERTEX_LENGTH_MAX, 0.0f };
	ver.rhw = 1.0f;
	ver.u = (ver.pos.x - cpos.x) / lpSceneMng.ScreenSize.x;
	ver.v = (ver.pos.y - cpos.y) / lpSceneMng.ScreenSize.y;
	ver.dif = { 0x00, 0xff, 0xff, 0x55 };
	_lightVer.fill(ver);

	_lightVer[0].dif = { 0xff, 0xff,0xff,0xff };
	Init();
	OnceInit();
}

Flash::~Flash()
{
}

void Flash::Update(void)
{
	_timer++;
	_pos = *_ownerPos;
	(this->*_update)();
}

void Flash::Draw(void)
{
	Vector2D cpos = lpSceneMng.GetcPos();
	int ts, tb, tp;
	lpImageMng.GetCurrentScreen(&ts, &tb, &tp);
	SetDrawScreen(drawscreen);
	ClsDrawScreen();

	DrawPrimitiveIndexed2D(_lightVer.data(), _lightVer.size(), _verIndex.data(), _verIndex.size(), DX_PRIMTYPE_TRIANGLELIST, DX_NONE_GRAPH, true);

	lpImageMng.AddDraw({ drawscreen, _ownerPos->x, _ownerPos->y, _exRate, _rad, LAYER::CHAR, _zOrder, DX_BLENDMODE_NOBLEND, 0 });

	SetDrawScreen(ts);
}

void Flash::IfHitAttack(std::shared_ptr<Object> target)
{
	if (target != nullptr)
	{
		target->SetStateEffect(new StateEffect(STATE_EFFECT_TYPE::CONFUSION, 180));
	}
}

void Flash::Init(void)
{
	std::vector<atkData> attack;
	attack.reserve(LIFE_TIME);
	float size;
	for (int i = 0; i < EXPAND_INTERVAL; i++)
	{
		size = VERTEX_LENGTH_MAX / static_cast<float>(EXPAND_INTERVAL) * static_cast<float>(i + 1);
		attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { 0, 0 }, size, -1, 0, _target));
	}
	for (int i = 0; i < SHRINK_INTERVAL; i++)
	{
		size = VERTEX_LENGTH_MAX / static_cast<float>(SHRINK_INTERVAL) * static_cast<float>(SHRINK_INTERVAL - i);
		attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { 0, 0 }, size, -1, 0, _target));
	}
	setAttack("light", attack);

	AddAttack("light");
}

void Flash::OnceInit(void)
{
	if (_initialized)
	{
		return;
	}
	_initialized = true;

	for (unsigned short i = 0; i < 35; i++)
	{
		_verIndex[i * 3 + 0] = 0;
		_verIndex[i * 3 + 1] = i + 1;
		_verIndex[i * 3 + 2] = i + 2;
	}
	_verIndex[105] = 0;
	_verIndex[106] = 36;
	_verIndex[107] = 1;

	drawscreen = MakeScreen(static_cast<int>(VERTEX_LENGTH_MAX) * 2, static_cast<int>(VERTEX_LENGTH_MAX) * 2, true);
}

void Flash::ExpandUpdate(void)
{
	Vector2D cpos = lpSceneMng.GetcPos() - Vector2D(lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y);

	float angle = -DX_PI_F;
	float range = VERTEX_LENGTH_MAX / static_cast<float>(EXPAND_INTERVAL) * _timer;
	for (int i = 0; i < 36; i++)
	{
		_lightVer[i + 1].pos.x = VERTEX_LENGTH_MAX + cosf(angle) * range;
		_lightVer[i + 1].pos.y = VERTEX_LENGTH_MAX + sinf(angle) * range;
		_lightVer[i + 1].u = (_ownerPos->x + _lightVer[i + 1].pos.x - cpos.x - VERTEX_LENGTH_MAX) / lpSceneMng.ScreenSize.x;
		_lightVer[i + 1].v = (_ownerPos->y + _lightVer[i + 1].pos.y - cpos.y - VERTEX_LENGTH_MAX) / lpSceneMng.ScreenSize.y;

		angle += ANGLE_DIFF;
	}

	if (_timer >= EXPAND_INTERVAL)
	{
		_update = &Flash::ShrinkUpdate;
		_timer = 0;
	}
}

void Flash::ShrinkUpdate(void)
{
	Vector2D cpos = lpSceneMng.GetcPos() - Vector2D(lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y);

	float angle = -DX_PI_F;
	float range = VERTEX_LENGTH_MAX / static_cast<float>(SHRINK_INTERVAL) * (SHRINK_INTERVAL - _timer);
	for (int i = 0; i < 36; i++)
	{
		_lightVer[i + 1].pos.x = VERTEX_LENGTH_MAX + cosf(angle) * range;
		_lightVer[i + 1].pos.y = VERTEX_LENGTH_MAX + sinf(angle) * range;
		_lightVer[i + 1].u = (_ownerPos->x + _lightVer[i + 1].pos.x - cpos.x - VERTEX_LENGTH_MAX) / lpSceneMng.ScreenSize.x;
		_lightVer[i + 1].v = (_ownerPos->y + _lightVer[i + 1].pos.y - cpos.y - VERTEX_LENGTH_MAX) / lpSceneMng.ScreenSize.y;

		angle += ANGLE_DIFF;
	}

	if (_timer >= SHRINK_INTERVAL)
	{
		setState({ OBJ_STATE::DEAD, _state_dir.second });
	}
}
