#include "EnemyMng.h"
#include "s_dragon.h"
#include "demon.h"
#include "wizard.h"
#include "scorcererViilain.h"
#include "../../Scene/SceneMng.h"
#include "../../Manage/MapMng.h"

EnemyMng *EnemyMng::sInstance = nullptr;

void EnemyMng::Update(void)
{
	for(auto data : _enemyList)
	{
		(*data).Update();
	}
	_enemyList.erase(std::remove_if(_enemyList.begin(), _enemyList.end(), 
		[&](std::shared_ptr<Enemy>& data)
	       	{
			return !(*data).isAlive(); 
		}
		),_enemyList.end());

	enemyPop((*lpSceneMng.GetPlObj(TIME::FTR))->getStage());
	enemyPop((*lpSceneMng.GetPlObj(TIME::NOW))->getStage());
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
	SetPlStage(static_cast<int>(lpTimeMng.getTime()), nextStage);
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

	TIME ttime = lpTimeMng.getTime() == TIME::FTR ? TIME::NOW : TIME::FTR;

	if ((*lpSceneMng.GetPlObj(ttime))->getStage() == nextStage)
	{
			// プレイヤーがいるMAPだから新しく敵を配置する必要がない	 
			return;
	}

	for (unsigned int i = 0; i < _enemyPlace[nextStage].size(); i++)
	{
		EnemyPop(_enemyPlace[nextStage][i].first, nextStage, i);
	}
}

void EnemyMng::StageTDelete(void)
{
	// pl1,pl2のどちらのステージにもない場合削除

	_enemyList.erase(std::remove_if(_enemyList.begin(), _enemyList.end(), [&](std::shared_ptr<Enemy>& data) {
		bool flag = false;
		if ((*data).getStage() != (*lpSceneMng.GetPlObj(TIME::FTR))->getStage() &&
			(*data).getStage() != (*lpSceneMng.GetPlObj(TIME::NOW))->getStage())
		{
			_deadStageCnt[(*data).getStage()]--;
			flag = true;
		}
			return flag;
	}),_enemyList.end());
}

void EnemyMng::Init(void)
{
	if (_epF)
	{
		// とりあえず手書き
		_enemyPlace[1] = { { ENEMY_TYPE::demon	 , {  448,  464 } },{ ENEMY_TYPE::s_dragon, {  896,  624 } } };
		_enemyPlace[2] = { { ENEMY_TYPE::s_dragon, {  800, 1280 } },{ ENEMY_TYPE::wizard  , { 1264, 1280 } } };
		_enemyPlace[3] = { { ENEMY_TYPE::sorcerer, {  768, 1056 } },{ ENEMY_TYPE::s_dragon, { 1200,  200 } } };
		_enemyPlace[4] = { { ENEMY_TYPE::s_dragon, {   48, 1040 } },{ ENEMY_TYPE::s_dragon, {  272,  128 } } };

		_epF = false;
	}

	for (int i = 0; i < STAGE_MAX; i++)
	{
		_deadStageCnt[i] = 0;
	}

	_enemyList.clear();
	_enemyList.emplace_back(new wizard({ 848,646 },1,0, false));

	_plStage[0] = 1;
	_plStage[1] = 1;
}

void EnemyMng::addDeadCnt(ENEMY_TYPE type, int stage, int pPos)
{
		_deadCnt.emplace_back(std::move(std::make_pair(type,std::make_pair(stage,pPos))));
		_deadStageCnt[stage]++;
}

void EnemyMng::enemyPop(int stage)
{
	_deadStageCnt[stage] += (std::rand() % 3000 == 0);		// 時間経過で湧くように

	if (_deadStageCnt[stage] > 1)
	{
		for (auto data = _deadCnt.begin(); data != _deadCnt.end();)
		{
			if (data->second.first == stage)
			{
				EnemyPop(_enemyPlace[data->second.first][data->second.second].first, data->second.first, data->second.second);
				data = _deadCnt.erase(data);
				continue;
				// dataが次のイテレータになったからインクリメントしない
			}
			++data;
		}
		_deadStageCnt[stage] = 0;
	}
}

void EnemyMng::EnemyPop(ENEMY_TYPE type, int nextStage, int i)
{
	switch (type)
	{
	case ENEMY_TYPE::s_dragon:
		_enemyList.emplace_back(new s_dragon(_enemyPlace[nextStage][i].second, nextStage, i, false));
		break;
	case ENEMY_TYPE::demon:
		_enemyList.emplace_back(new demon(_enemyPlace[nextStage][i].second, nextStage, i, false));
		break;
	case ENEMY_TYPE::wizard:
		_enemyList.emplace_back(new wizard(_enemyPlace[nextStage][i].second, nextStage, i, false));
		break;
	case ENEMY_TYPE::sorcerer:
		_enemyList.emplace_back(new sorcerer(_enemyPlace[nextStage][i].second, nextStage, i, false));
	default:
		break;
	}
}


EnemyMng::EnemyMng()
{
	_epF = true;
}

EnemyMng::~EnemyMng()
{
}

