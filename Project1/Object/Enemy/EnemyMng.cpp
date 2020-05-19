#include "EnemyMng.h"
#include "s_dragon.h"
#include "../../Scene/SceneMng.h"

EnemyMng *EnemyMng::sInstance = nullptr;

void EnemyMng::Update(void)
{
	for(auto data : _enemyList)
	{
	//	_enemyList.erase(data);				// �͈�for���ł̃C�e���[�^�̎������킩��Ȃ�
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
	_enemyList.emplace_back(new s_dragon({ 800,50 },nowStage));
}

void EnemyMng::StageTDelete(void)
{
	// pl1,pl2�̂ǂ���̃X�e�[�W�ɂ��Ȃ��ꍇ�폜

	_enemyList.erase(std::remove_if(_enemyList.begin(), _enemyList.end(), [](std::shared_ptr<Enemy>& data) {
		return ((*data).getStage() != (*lpSceneMng.GetPlObj(TIME::FTR))->getStage() &&
			(*data).getStage() != (*lpSceneMng.GetPlObj(TIME::NOW))->getStage());
	}),_enemyList.end());
}

void EnemyMng::Init(void)
{
	_enemyList.clear();
	_enemyList.emplace_back(new s_dragon({ 800,50 },1, false));
}

EnemyMng::EnemyMng()
{
}

EnemyMng::~EnemyMng()
{
}

