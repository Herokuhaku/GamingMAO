#pragma once
#include "BaseScene.h"
#include "../Object/Object.h"
#include "../Object/Enemy/Enemy.h"
#include "../Graphic/EffekseerMng.h"
#include "../func/CheckHitAttack.h"
#include "GameOverScene.h"


class GameScene:public BaseScene
{
public:
	GameScene();
	~GameScene();

	std::unique_ptr<BaseScene> Update(std::unique_ptr<BaseScene> own) override;	
private:
	friend struct CheckHitAttack;

	bool Init(void);

	void getAttackQue(void);
	void ItemDraw(void);

	std::vector<std::shared_ptr<Object>> _objList;
	std::shared_ptr<camera> _cobj;

	// 1:当たるか　2:自分の種類 3:判定の左上の座標　4:判定の右下の座標　
	// 5:ダメージ量　6:無敵時間　7:当てる対象(MAXで自分以外すべてに)
	std::vector<std::pair<atkData, std::shared_ptr<Object>>> _attackList;
};

