#pragma once
#include "BaceScene.h"
#include "../Object/Object.h"
#include "../Object/Enemy/Enemy.h"
#include "../Graphic/EffekseerMng.h"
#include "../func/CheckHitAttack.h"


class GameScene:public BaceScene
{
public:
	GameScene();
	~GameScene();

	std::unique_ptr<BaceScene> Update(std::unique_ptr<BaceScene> own) override;	
private:
	friend struct CheckHitAttack;

	bool Init(void);

	void getAttackQue(void);

	std::vector<std::shared_ptr<Object>> _objList;
	std::vector<std::shared_ptr<Object>> _enemyList;

	// 1:当たるか　2:自分の種類 3:判定の左上の座標　4:判定の右下の座標　
	// 5:ダメージ量　6:無敵時間　7:当てる対象(MAXで自分以外すべてに)
	std::vector<std::pair<atkData, std::shared_ptr<Object>>> _attackList;
};

