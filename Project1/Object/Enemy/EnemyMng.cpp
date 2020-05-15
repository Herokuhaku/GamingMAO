#include "EnemyMng.h"
#include "s_dragon.h"

EnemyMng *EnemyMng::sInstance = nullptr;

void EnemyMng::Update(void)
{
	for(auto data : _enemyList)
	{
	//	_enemyList.erase(data);				// 範囲for文でのイテレータの取り方がわからない
		(*data).Update();
	}
	_enemyList.erase(std::remove_if(_enemyList.begin(), _enemyList.end(), [](std::shared_ptr<Enemy>& data) {return !(*data).isAlive(); }),_enemyList.end());
}

void EnemyMng::Draw(void)
{
	for(auto data : _enemyList)
	{
		if ((*data).getStage() == lpMapMng.GetnowStage())
		{
			(*data).Draw();
		}
	}
}

std::vector<std::shared_ptr<Enemy>> &EnemyMng::GetenemyList(void)
{
	return _enemyList;
}

void EnemyMng::Init(void)
{
	_enemyList.emplace_back(new s_dragon());	
}

EnemyMng::EnemyMng()
{
}

EnemyMng::~EnemyMng()
{
}

