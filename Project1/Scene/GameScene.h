#pragma once
#include "BaseScene.h"
#include "../Object/Object.h"
#include "../Object/Enemy/Enemy.h"
#include "../Graphic/EffekseerMng.h"
#include "../func/CheckHitAttack.h"
#include "GameOverScene.h"
#include <memory>

class GimmickMng;
class MenuExecuter;
class BarrierMng;

class GameScene:public BaseScene
{
public:
	GameScene();
	~GameScene();

	std::unique_ptr<BaseScene> Update(std::unique_ptr<BaseScene> own) override;	

	/// <summary>
	/// ���j���[�̊Ǘ��N���X�̎擾
	/// </summary>
	std::shared_ptr<MenuExecuter>& GetMenuExecuter(void);

	std::shared_ptr<BarrierMng>& GetBarrierMng(void);

	/// <summary>
	/// �|�C���^�ɑΉ�����shared_ptr�I�u�W�F�N�g��T��
	/// </summary>
	std::shared_ptr<Object> FindObject(Object* obj);
private:
	friend struct CheckHitAttack;

	bool Init(void);

	void getAttackQue(void);
	void ItemDraw(void);

	std::unique_ptr<BaseScene> NormalUpdate(std::unique_ptr<BaseScene> own);
	std::unique_ptr<BaseScene> StopedUpdate(std::unique_ptr<BaseScene> own);
	std::unique_ptr<BaseScene>(GameScene::*_update)(std::unique_ptr<BaseScene> own);

	std::vector<std::shared_ptr<Object>> _objList;
	std::shared_ptr<camera> _cobj;
	std::unique_ptr<GimmickMng> _gimmickMng;
	std::shared_ptr<MenuExecuter> _menu;
	std::shared_ptr<BarrierMng> _barrierMng;

	// 1:�����邩�@2:�����̎�� 3:����̍���̍��W�@4:����̉E���̍��W�@
	// 5:�_���[�W�ʁ@6:���G���ԁ@7:���Ă�Ώ�(MAX�Ŏ����ȊO���ׂĂ�)
	std::vector<std::pair<atkData, std::shared_ptr<Object>>> _attackList;
};

