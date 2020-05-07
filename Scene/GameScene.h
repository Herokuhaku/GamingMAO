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

	// 1:�����邩�@2:�����̎�� 3:����̍���̍��W�@4:����̉E���̍��W�@
	// 5:�_���[�W�ʁ@6:���G���ԁ@7:���Ă�Ώ�(MAX�Ŏ����ȊO���ׂĂ�)
	std::vector<std::pair<atkData, std::shared_ptr<Object>>> _attackList;
};

