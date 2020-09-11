#include "Boss.h"
#include "../../Graphic/ImageMng.h"
#include "../Attack/AttackMng.h"
#include "../../Scene/SceneMng.h"

void Boss::DrawHP(void)
{
	(this->*func)();
}

Boss::Boss()
{
	func = { &Boss::funcDrawHPStart };
	_startCnt = 0;
	_saveDivNum = _divNum;
	_tmpHP = _maxHP / _saveDivNum;
}

Boss::~Boss()
{
}

void Boss::RunAtkList(void)
{
	if (lpSceneMng.GetFlame() % 10 == 0)
	{
		if (atkList.size() > 0)
		{
			auto pPos = lpSceneMng.GetPlPos(TIME::FTR);
			switch (atkList[0].first)
			{
			case AtkList::TRACKING_BALL:
				if (atkList[0].second > 0)
				{
					lpAtkMng.MakeTrackingBall({ _pos.x - 30,_pos.y - 200 }, std::move(pPos), _time, _stage, OBJ_TYPE::PLAYER);
					atkList[0].second--;
					break;
				}
				atkList.erase(atkList.begin());
				break;

			case AtkList::THUNDER:
				lpAtkMng.MakeThunderAttack(_pos, _plDir, _time, _stage, OBJ_TYPE::PLAYER);
				atkList.erase(atkList.begin());
				break;

			case AtkList::CANE_ATTACK:
				lpAtkMng.MakeCaneAttack(_pos, _plDir, _time, _stage, OBJ_TYPE::PLAYER);
				atkList.erase(atkList.begin());
				break;

			default:
				break;
			}
		}
	}
}

void Boss::funcDrawHPStart(void)
{
	_divNum = static_cast<int>(_startCnt * (70.0 / 200.0));
	funcDrawHP();
	_startCnt++;
	if (_startCnt >= 200)
	{
		func = { &Boss::funcDrawHP };
		_divNum = _saveDivNum;
	}
}

void Boss::funcDrawHP(void)
{
	int tmpNum;
	for (int i = 0; i < _divNum; i++)
	{
		if (_hp >= i * _tmpHP + 1)
		{
			tmpNum = 0;
		}
		else
		{
			tmpNum = 2;
		}
		lpImageMng.AddBackDraw({ lpImageMng.getImage("hp_bar")[tmpNum],  (6 * 3) * i + 19 ,(12 * 3) / 2, 3.0, 0.0, LAYER::EX, 0, DX_BLENDMODE_NOBLEND, 0, true });
	}
}
