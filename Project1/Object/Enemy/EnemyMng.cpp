#include "EnemyMng.h"
#include "s_dragon.h"
#include "../../Scene/SceneMng.h"

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

void EnemyMng::StageTrans(int nowStage)
{
	StageTDelete();
	StageTPop(nowStage);
}

void EnemyMng::StageTPop(int nowStage)
{
	if (nowStage > _enemyPlace.size())
	{
		// エラー
		exit(1);
	//	return;
	}
	for (int i = 0; i < _enemyPlace[nowStage].size(); i++)
	{
		_enemyList.emplace_back(new s_dragon(_enemyPlace[nowStage][i].second, nowStage));
	}
}

void EnemyMng::StageTDelete(void)
{
	// pl1,pl2のどちらのステージにもない場合削除

	_enemyList.erase(std::remove_if(_enemyList.begin(), _enemyList.end(), [](std::shared_ptr<Enemy>& data) {
		return ((*data).getStage() != (*lpSceneMng.GetPlObj(TIME::FTR))->getStage() &&
			(*data).getStage() != (*lpSceneMng.GetPlObj(TIME::NOW))->getStage());
	}),_enemyList.end());
}

void EnemyMng::Init(void)
{
	if (_epF)
	{
		// とりあえず手書き
		_enemyPlace[1] = { { ENEMY_TYPE::s_dragon, {  800,   50 } },{ ENEMY_TYPE::s_dragon, { 1200,  200 } } };
		_enemyPlace[2] = { { ENEMY_TYPE::s_dragon, {  800,   50 } },{ ENEMY_TYPE::s_dragon, { 1200,  200 } } };
		_enemyPlace[3] = { { ENEMY_TYPE::s_dragon, {  768, 1056 } },{ ENEMY_TYPE::s_dragon, { 1200,  200 } } };
		_enemyPlace[4] = { { ENEMY_TYPE::s_dragon, {   48, 1040 } },{ ENEMY_TYPE::s_dragon, {  272,  128 } } };



		_epF = false;
	}

	_enemyList.clear();
	_enemyList.emplace_back(new s_dragon({ 800,50 },1, false));
}

EnemyMng::EnemyMng()
{
	_epF = true;
}

EnemyMng::~EnemyMng()
{
}

