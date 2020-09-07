#include "HealTree.h"
#include "../../../Graphic/ImageMng.h"
#include "../../../Manage/MapMng.h"
#include "../../../Audio/AudioContainer.h"

namespace
{
	AudioContainer _audio;
	constexpr int SURFACE_LIMIT = 3000;

	constexpr int GROW_TIME = 120;
	constexpr int LIFE_TIME = 700;
	constexpr int HEAL_DURATION = 150;

	constexpr int SIZE_Y = 225;
}

HealTree::HealTree(Vector2 pos, TIME time, int stage, OBJ_TYPE target)
{
	_pos = pos;
	_pos.y = FindSF(_pos.y) - SIZE_Y / 2;
	_time = time;
	_stage = stage;
	_target = target;
	_exRate = 1.5;

	_update = &HealTree::GrowUpdate;
	setState({ OBJ_STATE::A_NORMAL, DIR::RIGHT });
	_timer = GROW_TIME;

	Init();
}

HealTree::~HealTree()
{
}

void HealTree::Update(void)
{
	(this->*_update)();
}

void HealTree::GrowUpdate(void)
{
	_timer--;
	if (_timer <= 0)
	{
		_update = &HealTree::ActiveUpdate;
		_timer = LIFE_TIME;
	}
}

void HealTree::ActiveUpdate(void)
{
	_timer--;

	if (_timer % HEAL_DURATION == 50)
	{
		AddAttack("heal");
		lpImageMng.playEffect("heal_effect", &_pos.x, &_pos.y, 0.5, 0.0, LAYER::CHAR, 1, DX_BLENDMODE_NOBLEND, 0, _stage, EffectDrawType::DRAW_TO_RELATIVE);
		PlaySoundMem(_audio.GetSound("heal"), DX_PLAYTYPE_BACK, true);
	}

	if (_timer <= 0)
	{
		_timer = GROW_TIME;
		_update = &HealTree::WitherUpdate;
		setState({ OBJ_STATE::DAMAGE, _state_dir.second });
	}
}

void HealTree::WitherUpdate(void)
{
	_timer--;
	if (_timer <= 0)
	{
		setState({ OBJ_STATE::DEAD, _state_dir.second });
	}
}

int HealTree::FindSF(int pos)
{
	int tmp = pos;

	if (lpMapMng.getHitMap({ _pos.x, tmp }, lpMapMng.GetnowStage()))
	{
		while (lpMapMng.getHitMap({ _pos.x, tmp }, lpMapMng.GetnowStage()))
		{
			if (tmp < 0)
			{
				return -1;
			}
			tmp -= CHIP_SIZE;
		}
	}
	else
	{
		while (!lpMapMng.getHitMap({ _pos.x, tmp }, lpMapMng.GetnowStage()))
		{
			if (tmp > SURFACE_LIMIT)
			{
				return -1;
			}
			tmp += CHIP_SIZE;
		}
	}

	tmp = tmp - tmp % 16;

	return tmp;
}

void HealTree::Init(void)
{
	AnmVec data;
	data.reserve(4);

	for (int i = 0; i < 4; i++)
	{
		data.emplace_back(lpImageMng.getImage("tree")[i], 30 * i);
	}
	data.emplace_back(-1, 0);

	setAnm({ OBJ_STATE::A_NORMAL, _state_dir.second }, data);

	data.reserve(1);
	data.emplace_back(lpImageMng.getImage("tree")[4], 0);

	setAnm({ OBJ_STATE::NORMAL, _state_dir.second }, data);

	data.reserve(4);

	for (int i = 0; i < 4; i++)
	{
		data.emplace_back(lpImageMng.getImage("tree")[3 - i], 30 * i);
	}
	data.emplace_back(-1, -1);

	setAnm({ OBJ_STATE::DAMAGE, _state_dir.second }, data);



	std::vector<atkData> attack;

	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { -137, -112 }, { 137, 112 }, -20, 0, _target));

	setAttack("heal", attack);

	EffectData effect;
	effect.reserve(9);

	lpImageMng.getImage("image/Attack/heal_effect.png", "heal_effect", 240, 240, 8, 1);
	for (int i = 0; i < 8; i++)
	{
		effect.emplace_back(lpImageMng.getImage("heal_effect")[i], 2 * i);
	}
	effect.emplace_back(0, -1);
	lpImageMng.setEffect("heal_effect", effect);

	_audio.LoadSound("sound/magic/heal.wav", "heal", 10);
	_audio.ChangeVolume("heal", 100);
}

