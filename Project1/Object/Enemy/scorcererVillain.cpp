#include "scorcererViilain.h"
#include "../../Scene/SceneMng.h"
#include "../../Graphic/ImageMng.h"
#include "../../Manage/MapMng.h"
#include "../EnemyAttack/TrackingBall.h"
#include "../Attack/AttackMng.h"

void sorcerer::Update(void)
{
	Enemy::Update();
	RunAtkList();
}

void sorcerer::damagingHP(int damage)
{
	if (damage >= 45)
	{
		Enemy::damagingHP(damage);
	}
	else
	{
		Object::damagingHP(damage);
	}
}

int sorcerer::Attack(Vector2& pPos)
{
	if (_state_dir.first != OBJ_STATE::ATTACK)
	{
		if (std::abs((pPos.x - _pos.x)) <= 150)
		{	// 近接
			if (rand() % 2 == 0)
			{
				setState({ OBJ_STATE::ATTACK2, _plDir });
				atkList.emplace_back(AtkList::THUNDER, 4);
				_waitTime = 70;	// クールタイム
				_waitCnt = 0;
			}
			else
			{
				setState({ OBJ_STATE::ATTACK3, _plDir });
				atkList.emplace_back(AtkList::CANE_ATTACK, 4);
				_waitTime = 30;	// クールタイム
				_waitCnt = 0;
			}
		}
		else
		{	// 遠距離
			setState({ OBJ_STATE::ATTACK, _plDir });
			atkList.emplace_back(AtkList::TRACKING_BALL, 6);
			_waitTime = 180;	// クールタイム
			_waitCnt = 0;
		}
		return static_cast<int>(MOVE_SELECT::WAIT);
	}
	return static_cast<int>(MOVE_SELECT::WAIT);
}

sorcerer::sorcerer(Vector2 pos, int stage)
	{
	_pos = pos;
	_stage = stage;
	_state_dir = { OBJ_STATE::NORMAL,DIR::RIGHT };
	setHP(100);
	setHitOffset({ 55, 55, 100, 0 });
	_tmpHP = _maxHP / _saveDivNum;
	
	while (!lpMapMng.getHitMap(_pos, _stage))
	{
		_pos.y += 1;
	}
	Init();
}

sorcerer::sorcerer(Vector2 pos, int stage, int pPos, bool flag)
{
	_pos = pos;
	_stage = stage;
	_etype = ENEMY_TYPE::s_dragon;
	_pPos = pPos;
	_state_dir = { OBJ_STATE::NORMAL,DIR::RIGHT };
	_hp = 4000;
	_maxHP = _hp;
	setHitOffset({ 55, 55, 100, 0 });
	_tmpHP = _maxHP / _saveDivNum;
	_exRate = 3.0;
	_stateEffectExRate = 3.0;

	_rangeSF = 1000;
	_rangeSB = 600;
	_rangeA = 850;

	if (flag)
	{
		while (!lpMapMng.getHitMap(_pos, _stage))
		{
			_pos.y += 1;
		}
	}
	Init();
}

sorcerer::~sorcerer()
{
}

void sorcerer::Init(void)
{
	AnmVec data;
	int animCnt = 20;
	// 右-------------------------------------------
	for (int i = 0; i < 2; i++)
	{
		data.emplace_back(lpImageMng.getImage("sorcViR")[17 + i], animCnt + i * animCnt);
	}
	setAnm({ OBJ_STATE::NORMAL,DIR::RIGHT }, data);
	animCnt = 5;

//	for (int i = 0; i < 13; i++)
	{
		int i = 0;
		data.emplace_back(lpImageMng.getImage("sorcViR")[i], animCnt + i * animCnt);
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViR")[i], animCnt + i * animCnt);
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViR")[i], animCnt + i * animCnt);
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViR")[i], animCnt + i * animCnt);
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViR")[i], animCnt + i * animCnt);
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViR")[i], animCnt + i * animCnt);
		animCnt = 15;
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViR")[i], animCnt + i * animCnt);
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViR")[i], animCnt + i * animCnt);
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViR")[i], animCnt + i * animCnt);
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViR")[i], animCnt + i * animCnt);
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViR")[i], animCnt + i * animCnt);
		animCnt = 20;
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViR")[i], animCnt + i * animCnt);
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViR")[i], animCnt + i * animCnt);
	}
	setAnm({ OBJ_STATE::WALK,DIR::RIGHT }, data);
	animCnt = 5;

	for (int i = 0; i < 6; i++)
	{
		data.emplace_back(lpImageMng.getImage("sorcViR")[68 + i], animCnt + i * animCnt);
	}
	data.emplace_back(lpImageMng.getImage("sorcViR")[68 + 6], animCnt + 20 * animCnt);
	data.emplace_back(-1, 0);
	setAnm({ OBJ_STATE::ATTACK,DIR::RIGHT }, data);

	data.emplace_back(lpImageMng.getImage("sorcViR")[68], animCnt + 0 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViR")[69], animCnt + 1 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViR")[70], animCnt + 2 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViR")[71], animCnt + 3 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViR")[72], animCnt + 4 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViR")[73], animCnt + 5 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViR")[74], animCnt + 6 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViR")[75], animCnt + 7 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViR")[76], animCnt + 8 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViR")[77], animCnt + 9 * animCnt);
	data.emplace_back(-1, 0);
	setAnm({ OBJ_STATE::ATTACK2,DIR::RIGHT }, data);

	data.emplace_back(lpImageMng.getImage("sorcViR")[85], animCnt + 0 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViR")[86], animCnt + 1 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViR")[87], animCnt + 2 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViR")[88], animCnt + 3 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViR")[89], animCnt + 4 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViR")[90], animCnt + 5 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViR")[91], animCnt + 6 * animCnt);
	data.emplace_back(-1, 0);
	setAnm({ OBJ_STATE::ATTACK3,DIR::RIGHT }, data);

	for (int i = 0; i < 7; i++)
	{
		data.emplace_back(lpImageMng.getImage("sorcViR")[34 + i], animCnt + i * animCnt);
	}
	data.emplace_back(-1,0);
	setAnm({ OBJ_STATE::DAMAGE,DIR::RIGHT }, data);

	for (int i = 0; i < 17; i++)
	{
		data.emplace_back(lpImageMng.getImage("sorcViR")[51 + i], animCnt + i * animCnt);
	}
	data.emplace_back(-1,2828);
	setAnm({ OBJ_STATE::DEAD,DIR::RIGHT }, data);

	// 左-------------------------------------------
	animCnt = 20;
	for (int i = 0; i < 2; i++)
	{
		data.emplace_back(lpImageMng.getImage("sorcViL")[33 - i], animCnt + i * animCnt);
	}
	setAnm({ OBJ_STATE::NORMAL,DIR::LEFT }, data);
	animCnt = 5;

//	for (int i = 0; i < 13; i++)
	{
		int i = 0;
		data.emplace_back(lpImageMng.getImage("sorcViL")[16 - i], animCnt + i * animCnt);
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViL")[16 - i], animCnt + i * animCnt);
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViL")[16 - i], animCnt + i * animCnt);
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViL")[16 - i], animCnt + i * animCnt);
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViL")[16 - i], animCnt + i * animCnt);
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViL")[16 - i], animCnt + i * animCnt);
		i++;
		animCnt = 15;
		data.emplace_back(lpImageMng.getImage("sorcViL")[16 - i], animCnt + i * animCnt);
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViL")[16 - i], animCnt + i * animCnt);
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViL")[16 - i], animCnt + i * animCnt);
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViL")[16 - i], animCnt + i * animCnt);
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViL")[16 - i], animCnt + i * animCnt);
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViL")[16 - i], animCnt + i * animCnt);
		animCnt = 20;
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViL")[16 - i], animCnt + i * animCnt);
		i++;
		data.emplace_back(lpImageMng.getImage("sorcViL")[16 - i], animCnt + i * animCnt);
	}
	setAnm({ OBJ_STATE::WALK,DIR::LEFT }, data);
	animCnt = 5;

	for (int i = 0; i < 6; i++)
	{
		data.emplace_back(lpImageMng.getImage("sorcViL")[84 - i], animCnt + i * animCnt);
	}
	data.emplace_back(lpImageMng.getImage("sorcViL")[84 - 6], animCnt + 20 * animCnt);
	data.emplace_back(-1, 0);
	setAnm({ OBJ_STATE::ATTACK,DIR::LEFT }, data);

	data.emplace_back(lpImageMng.getImage("sorcViL")[84], animCnt + 0 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViL")[83], animCnt + 1 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViL")[82], animCnt + 2 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViL")[81], animCnt + 3 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViL")[80], animCnt + 4 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViL")[79], animCnt + 5 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViL")[78], animCnt + 6 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViL")[77], animCnt + 7 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViL")[76], animCnt + 8 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViL")[75], animCnt + 9 * animCnt);
	data.emplace_back(-1, 0);
	setAnm({ OBJ_STATE::ATTACK2,DIR::LEFT }, data);

	data.emplace_back(lpImageMng.getImage("sorcViL")[101], animCnt + 0 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViL")[100], animCnt + 1 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViL")[99], animCnt + 2 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViL")[98], animCnt + 3 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViL")[97], animCnt + 4 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViL")[96], animCnt + 5 * animCnt);
	data.emplace_back(lpImageMng.getImage("sorcViL")[95], animCnt + 6 * animCnt);
	data.emplace_back(-1, 0);
	setAnm({ OBJ_STATE::ATTACK3,DIR::LEFT }, data);

	for (int i = 0; i < 7; i++)
	{
		data.emplace_back(lpImageMng.getImage("sorcViL")[50 - i], animCnt + i * animCnt);
	}
	data.emplace_back(-1,0);
	setAnm({ OBJ_STATE::DAMAGE,DIR::LEFT }, data);

	for (int i = 0; i < 17; i++)
	{
		data.emplace_back(lpImageMng.getImage("sorcViL")[67 - i], animCnt + i * animCnt);
	}
	data.emplace_back(-1, 2828);
	setAnm({ OBJ_STATE::DEAD,DIR::LEFT }, data);

	_etype = ENEMY_TYPE::sorcerer;
	_drawOffset_y = 80 * (int)_exRate / 2;

	_size = { 10, 200 };
}
