#pragma once
#include <memory>
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

			void StageTDelete(void);		// トランス ステージが変わった際のEnemyの削除
			
			void Init(void);
	private:
			static EnemyMng *sInstance;

			std::vector<std::shared_ptr<Enemy>> _enemyList;

			EnemyMng();
			~EnemyMng();
};
