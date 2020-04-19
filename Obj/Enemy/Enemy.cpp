#include "Enemy.h"
#include "../../Scene/SceneMng.h"

//void Enemy::Update(std::shared_ptr<Object> plObj);
//{
//}

void Enemy::Update(void)
{
	auto tmp = lpSceneMng.GetPlObj();
	_work = (this->*autoM[_aState])((*tmp)->getPos());
	if (_work < e_fn_ptr_num)
	{
		_aState += _work;
	}
	else
	{
		// エラー
		_aState = 0;
	}
	Draw();
}

int Enemy::Wait(Vector2 pPos)
{
	_waitCnt++;
	if (_waitCnt >= _waitTime)
	{
		setState({ OBJ_STATE::WALK, _state_dir.second });
		return 1;
	}
	return 0;
}

int Enemy::Move(Vector2 pPos)
{
	if (_state_dir.second == DIR::RIGHT)
	{
		_pos.x += lpSceneMng.GetFlame() % 2;
	}
	return Search(pPos);
}

int Enemy::Search(Vector2 pPos)
{
	if ((pPos.x - _pos.x) <= _rangeS && (pPos.x - _pos.x) >= -20)
	{
		setState({ OBJ_STATE::ATTACK, _state_dir.second });
		return 2;
	}
	return 0;
}

int Enemy::Attack(Vector2 pPos)
{
	_waitTime = 120;	// クールタイム
	_waitCnt = 0;
	return -3;
}

Enemy::Enemy()
{
	_aState = 0;
	Init();
}

void Enemy::Init(void)
{
	_waitTime = std::rand() % 180 + 90;
	_waitCnt = 0;
	_waitF = true;
	_rangeS = 100;
}

Enemy::~Enemy()
{
}

