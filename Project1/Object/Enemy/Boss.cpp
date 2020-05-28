#include "Boss.h"

//void Boss::Update(void)
//{

//}

void Boss::DrawHP(void)
{
	(this->*func)();
}

Boss::Boss()
{
	func = { &Boss::funcDrawHPStart };
	_startCnt = 0;
	_saveDivNum = _divNum;
}

Boss::~Boss()
{
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
		if (_hp >= i * 10 + 1)
		{
			tmpNum = 0;
		}
		else
		{
			tmpNum = 2;
		}
		lpImageMng.AddBackDraw({ lpImageMng.getImage("hp_bar")[tmpNum],  (6 * 3) * i + 19 ,(12 * 3) / 2, 3.0, 0.0, LAYER::EX, 0, DX_BLENDMODE_NOBLEND, 0 });
	}
}
