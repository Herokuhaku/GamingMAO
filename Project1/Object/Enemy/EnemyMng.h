#pragma once
#include <memory>
#include <map>
#include <vector>
#include "Enemy.h"

#define lpEnemyMng EnemyMng::GetInstance()
#define STAGE_MAX 5

class EnemyMng
{
public:

	static EnemyMng &GetInstance(void)
	{
		Create();
		return *sInstance;
	};

	static void Create(void)
	{
		if (sInstance == nullptr)
		{
			sInstance = new EnemyMng();
		}
	};

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	};

	void Update(void);
	void Draw(void);
	std::vector<std::shared_ptr<Enemy>> &GetenemyList(void);

	void StageTrans(int nowStage, int nextStage);
	void StageTPop(int nowStage, int nextStage);			// �X�e�[�W���ς�����ۂ�Enemy�̗N��
	void StageTDelete(void);		// �g�����X �X�e�[�W���ς�����ۂ�Enemy�̍폜

	void addDeadCnt(ENEMY_TYPE type, int stage, int pPos);

	void enemyPop(int stage);

	void Init(int stage);

	void SetPlStage(int no, int stage) { _plStage[no] = stage; };
	int GetPlStage(int no) { return _plStage[no]; };
	int GetPlStage(void) { return _plStage[1]; };

private:
	static EnemyMng *sInstance;

	std::vector<std::shared_ptr<Enemy>> _enemyList;
	std::vector<std::pair<ENEMY_TYPE, std::pair<int, int>>> _deadCnt;		// <type, <stage, pPos>>
	unsigned short _deadStageCnt[STAGE_MAX];					// �A�N�Z�X���₷���悤��_deadCnt�ƕ����Ĕz����g��

	void EnemyPop(ENEMY_TYPE type, int nextStage, int i);

	std::map<int, std::vector<std::pair<ENEMY_TYPE, Vector2>>> _enemyPlace;
	bool _epF;							// _enemyPlace �����t���O

	int _plStage[2];

	EnemyMng();
	~EnemyMng();
};
