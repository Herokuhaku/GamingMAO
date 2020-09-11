#include "CaneAttack.h"
#include "../../Graphic/ImageMng.h"
#include "../../Audio/AudioContainer.h"

namespace
{
	AudioContainer _audio;
}

CaneAttack::CaneAttack(Vector2& ePos, DIR dir, TIME time, int stage, OBJ_TYPE target)
{
	_pos = { ePos.x, ePos.y - 100 };		// ‘„‚ÌoŒ»À•W
	addX = 6 * (dir == DIR::LEFT ? -1 : 1);
	_state_dir = { OBJ_STATE::NORMAL, dir };
	_time = time;
	_stage = stage;
	_target = target;
	_farstY = _pos.x;

	Init();
}

void CaneAttack::Update(void)
{
	_pos.x += addX;
	if (std::abs(_pos.x - _farstY) > 150)
	{
		setState({ OBJ_STATE::DEAD, _state_dir.second });
	}
}

void CaneAttack::IfHitAttack(std::shared_ptr<Object> target)
{
	setState({ OBJ_STATE::DEAD, _state_dir.second });
	if (target != nullptr)
	{
		target->MovePos({ (60 * ((target->getPos().x < _pos.x) ? -1 : 1)), -15 });
		PlaySoundMem(_audio.GetSound("hit"), DX_PLAYTYPE_BACK, true);
	}
}

bool CaneAttack::Init(void)
{	
	std::vector<atkData> attack;
	attack.reserve(1);

	//attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { _pos.x - 10, _pos.y - 10 }, { _pos.x + 10, _pos.y + 10 }, 30, 10, _target));
	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { 0, 0 }, 120, 20, 60, _target));
	attack.emplace_back(atkData(false, OBJ_TYPE::ATTACK, { 0, 0 }, { 0, 0 }, 0, -1, _target));

	AnmVec data;
	data.reserve(30);
	for (int i = 0; i < 30; i++)
	{
		data.emplace_back(lpImageMng.getImage("fireball")[i], i + 1);
	}

	setAnm({ OBJ_STATE::NORMAL, _state_dir.second }, data);

	setAttack("cane", attack);
	AddAttack("cane");

	_audio.LoadSound("sound/Attack/cane_attack.wav", "c_attack", 10);
	_audio.ChangeVolume("c_attack", 130);
	PlaySoundMem(_audio.GetSound("c_attack"), DX_PLAYTYPE_BACK, true);

	_audio.LoadSound("sound/Attack/hit.wav", "hit", 10);
	_audio.ChangeVolume("hit", 145);

	return false;
}
