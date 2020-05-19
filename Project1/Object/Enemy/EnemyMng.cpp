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

void EnemyMng::StageTrans(int nowStage, int nextStage)
{
	StageTDelete();
	StageTPop(nowStage,nextStage);
}

void EnemyMng::StageTPop(int nowStage, int nextStage)
{
	if (nextStage > _enemyPlace.size())
	{
		// エラー
		exit(1);
	//	return;
	}

	for (int i = 0; i < ACTIVEMAP; i++)
	{
		if ((*lpSceneMng.GetPlObj(lpTimeMng.getTime()))->getStage() == nextStage)
		{
			// プレイヤーがいるMAPだから新しく敵を配置する必要がない	 
			return;
		}
	}

	for (int i = 0; i < _enemyPlace[nextStage].size(); i++)
	{
		
		_enemyList.emplace_back(new s_dragon(_enemyPlace[nextStage][i].second, nextStage, false));
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
		_enemyPlace[1] = { { ENEMY_TYPE::s_dragon, {  448,  464 } },{ ENEMY_TYPE::s_dragon, {  896,  624 } } };
		_enemyPlace[2] = { { ENEMY_TYPE::s_dragon, {  800, 1280 } },{ ENEMY_TYPE::s_dragon, { 1264, 1280 } } };
		_enemyPlace[3] = { { ENEMY_TYPE::s_dragon, {  768, 1056 } },{ ENEMY_TYPE::s_dragon, { 1200,  200 } } };
		_enemyPlace[4] = { { ENEMY_TYPE::s_dragon, {   48, 1040 } },{ ENEMY_TYPE::s_dragon, {  272,  128 } } };



		_epF = false;
	}

	_enemyList.clear();
	_enemyList.emplace_back(new s_dragon({ 448,446 },1, false));
}

EnemyMng::EnemyMng()
{
	_epF = true;
}

EnemyMng::~EnemyMng()
{
}

