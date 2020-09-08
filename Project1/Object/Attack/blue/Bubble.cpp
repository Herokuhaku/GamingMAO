#include "Bubble.h"
#include "../../../Graphic/ImageMng.h"
#include "../../../Audio/AudioContainer.h"

namespace
{
	AudioContainer _audio;
	constexpr float ATTACK_RADIUS = 40.0f;
}

Bubble::Bubble(Vector2 pos, TIME time, int stage, OBJ_TYPE target)
{
	_pos = pos;
	_basePos_y = _pos.y;
	_time = time;
	_stage = stage;
	_target = target;
	_state_dir = { OBJ_STATE::NORMAL, DIR::LEFT };

	Init();
}

Bubble::~Bubble()
{
}

void Bubble::Update(void)
{
	_floatCount++;
	if (_floatCount > LIFE_TIME)
	{
		IfHitAttack(nullptr);
	}

	_pos.y = static_cast<int>(_basePos_y + sinf(_floatCount * acos(-1.0f) / 180.0f) * 20);
}

void Bubble::IfHitAttack(std::shared_ptr<Object> target)
{
	lpAtkMng.MakeBubbleBlast(_pos, _time, _stage, _target);
	setState({ OBJ_STATE::DEAD, _state_dir.second });
}

void Bubble::Init(void)
{
	AnmVec data;
	data.reserve(1);

	data.emplace_back(lpImageMng.getImage("bubble")[0], 1);

	setAnm({ OBJ_STATE::NORMAL, _state_dir.second }, data);

	std::vector<atkData> attack;
	attack.reserve(2);

	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { 0, 0 }, ATTACK_RADIUS, 0, 0, _target));
	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { 0, 0 }, ATTACK_RADIUS, 0, -1, _target));

	setAttack("bubble", attack);


	_floatCount = 0;

	_type = OBJ_TYPE::ATTACK;
	setHitOffset({ 50,50,50,50 });

	AddAttack("bubble");

	_audio.LoadSound("sound/magic/bubble.wav", "bubble", 10);
	_audio.ChangeVolume("bubble", 180);
	PlaySoundMem(_audio.GetSound("bubble"), DX_PLAYTYPE_BACK, true);
}
