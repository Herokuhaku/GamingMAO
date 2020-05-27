#include "scorcererViilain.h"
#include "../../Scene/SceneMng.h"

void sorcerer::Update(void)
{
	Enemy::Update();
}

//s_dragon::s_dragon(Vector2Template<int> pos, double rad, TIME time, int stage, OBJ_TYPE type, std::pair<OBJ_STATE, DIR> state_dir)
sorcerer::sorcerer(Vector2 pos, int stage)
	{
	_pos = pos;
	_stage = stage;
	_state_dir = { OBJ_STATE::NORMAL,DIR::RIGHT };
	setHP(100);
	setHitOffset({ 55, 55, 100, 0 });
	
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
	setHP(100);
	setHitOffset({ 55, 55, 100, 0 });
	_exRate = 3.0;

	_rangeS = 300;
	_rangeA = 250;

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
	// ‰E-------------------------------------------
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

	for (int i = 0; i < 10; i++)
	{
		data.emplace_back(lpImageMng.getImage("sorcViR")[68 + i], animCnt + i * animCnt);
	}
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

	// ¶-------------------------------------------
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

	for (int i = 0; i < 10; i++)
	{
		data.emplace_back(lpImageMng.getImage("sorcViL")[84 - i], animCnt + i * animCnt);
	}
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
}
