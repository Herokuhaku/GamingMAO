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

int sorcerer::Attack(Vector2 pPos)
{
	if (_state_dir.first != OBJ_STATE::ATTACK)
	{
		setState({ OBJ_STATE::ATTACK, _plDir });
		atkList.emplace_back(AtkList::TRACKING_BALL, 4);
		_waitTime = 180;	// クールタイム
		_waitCnt = 0;
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
