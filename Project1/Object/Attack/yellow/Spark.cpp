#include "Spark.h"
#include "../../../Scene/SceneMng.h"
#include "../../../Graphic/ImageMng.h"

namespace
{
	constexpr int SPARK_INTERVAL = 60;
	constexpr int LIFE_TIME = 330;
}

Spark::Spark(Vector2* pos, TIME time, int stage, OBJ_TYPE target)
{
	_time = time;
	_stage = stage;
	_target = target;

	_ownerPos = pos;
	_timer = LIFE_TIME;

	setState({ OBJ_STATE::NORMAL, DIR::RIGHT });

	Init();
}

Spark::~Spark()
{
}

void Spark::Update(void)
{
	if(_timer % SPARK_INTERVAL == 30)
	{
		lpImageMng.playEffect("spark_effect", &_ownerPos->x, &_ownerPos->y, 1.5, 0.0, LAYER::CHAR, 50, DX_BLENDMODE_NOBLEND, 0, lpSceneMng.GetPlObj2(TIME::FTR)->getStage(), EffectDrawType::DRAW_TO_RELATIVE);
		AddAttack("spark");
	}
	_timer--;

	if (_timer < 0)
	{
		setState({ OBJ_STATE::DEAD, _state_dir.second });
	}
	_pos = *_ownerPos;
}

void Spark::Init(void)
{
	std::vector<atkData> attack;
	attack.reserve(32);
	for (int i = 0; i < 32; i++)
	{
		attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { -40, -40 }, { 40, 40 }, 8, 10, _target));
	}
	setAttack("spark", attack);

	EffectData effect;
	effect.reserve(9);

	for (int i = 0; i < 8; i++)
	{
		effect.emplace_back(lpImageMng.getImage("spark")[i], 4 * i);
	}
	effect.emplace_back(0, -1);
	lpImageMng.setEffect("spark_effect", effect);
}
