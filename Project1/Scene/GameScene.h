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
	/// メニューの管理クラスの取得
	/// </summary>
	std::shared_ptr<MenuExecuter>& GetMenuExecuter(void);

	std::shared_ptr<BarrierMng>& GetBarrierMng(void);

	/// <summary>
	/// ポインタに対応するshared_ptrオブジェクトを探す
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

	// 1:当たるか　2:自分の種類 3:判定の左上の座標　4:判定の右下の座標　
	// 5:ダメージ量　6:無敵時間　7:当てる対象(MAXで自分以外すべてに)
	std::vector<std::pair<atkData, std::shared_ptr<Object>>> _attackList;
};

