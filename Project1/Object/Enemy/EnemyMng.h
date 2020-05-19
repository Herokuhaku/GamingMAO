#pragma once
#include <memory>
#include <map>
#include <vector>
#include "Enemy.h"

#define lpEnemyMng EnemyMng::GetInstance()

class EnemyMng
{	
	public :

			static EnemyMng &GetInstance(void)
			{
					Create();
					return *sInstance;
			};

			static void Create(void)
			{
					if(sInstance == nullptr)
					{
							sInstance = new EnemyMng();
					}
			};

			static void Destroy()
			{
					if(sInstance != nullptr)
					{
							delete sInstance;
					}
					sInstance = nullptr;
			};

			void Update(void);
			void Draw(void);
			std::vector<std::shared_ptr<Enemy>> &GetenemyList(void);

			void StageTrans(int nowStage);
			void StageTPop(int nowStage);			// ステージが変わった際のEnemyの湧き
			void StageTDelete(void);		// トランス ステージが変わった際のEnemyの削除
			
			void Init(void);
	private:
			static EnemyMng *sInstance;

			std::vector<std::shared_ptr<Enemy>> _enemyList;

			std::map<int,std::vector<std::pair<ENEMY_TYPE,Vector2>>> _enemyPlace;
			bool _epF;							// _enemyPlace を作るフラグ

			EnemyMng();
			~EnemyMng();
};
