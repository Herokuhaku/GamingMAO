#pragma once
#include "../Object.h"

#define lpAtkMng AttackMng::GetInstance()


class AttackMng :
	public Object
{
public:
	static AttackMng& GetInstance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new AttackMng();
		}

		return *sInstance;
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}

		sInstance = nullptr;
	}

	void Update(void)override;

	void Draw(void)override;

	std::vector<std::shared_ptr<Object>> GetAttackObjList(void);

	// 赤魔法

	// 火の玉
	// pos:座標			dir:方向
	// vec:移動ベクトル( vec.x > 0 でdir方向に、vec.x < 0 で反対側に)
	// time:時間軸		stage:ステージ
	// target:目標
	void MakeFireBall(Vector2 pos, DIR dir, Vector2 vec, TIME time, int stage, OBJ_TYPE target);
	// 爆弾投げ
	// pos:座標			dir:方向
	// speed:速度( speed > 0 でdir方向に、speed < 0 で反対側に)
	// vel:初速のY成分(負で上方向、正で下方向)
	// time:時間軸		stage:ステージ
	// target:目標
	void MakeBomb(Vector2 pos, DIR dir, int speed, double vel, TIME time, int stage, OBJ_TYPE target);
	
	// 青魔法

	// 泡攻撃
	// pos:座標			time:時間軸
	// stage:ステージ	target:目標
	void MakeBubble(Vector2 pos, TIME time, int stage, OBJ_TYPE target);
	// 泡破裂
	// pos:座標			time:時間軸
	// stage:ステージ	target:目標
	void MakeBubbleBlast(Vector2 pos, TIME time, int stage, OBJ_TYPE target);

	// 緑魔法

	// フルーツ転がし
	// pos:座標			dir:方向
	// speed:速度( speed > 0 でdir方向に、speed < 0 で反対側に)
	// time:時間軸		stage:ステージ
	// target:目標
	void MakeFruit(Vector2 pos, DIR dir, int speed, TIME time, int stage, OBJ_TYPE target);

	// 紫魔法

	// 毒の霧
	// pos:座標			count:生存時間
	// time:時間軸		stage:ステージ
	// target:目標
	void MakePoisonFog(Vector2 pos, int count, TIME time, int stage, OBJ_TYPE target);

	// 回復する木
	// pos:座標			time:時間軸
	// stage:ステージ	target:目標
	void MakeHealTree(Vector2 pos, TIME time, int stage, OBJ_TYPE target);

	// ブラックホール
	// pos:座標			dir:方向
	// vec:移動ベクトル( vec.x > 0 でdir方向に、vec.x < 0 で反対側に)
	// lifetime:生存時間
	// time:時間軸		stage:ステージ
	// target:目標
	void MakeBlackHole(Vector2 pos, DIR dir, Vector2 vec, int lifetime, TIME time, int stage, OBJ_TYPE target);

	// 水色魔法

	// 氷の球
	// owner:所有者
	// pos:座標			dir:方向
	// vec:移動ベクトル( vec.x > 0 でdir方向に、vec.x < 0 で反対側に)
	// time:時間軸		stage:ステージ
	// target:目標
	void MakeIceShot(std::shared_ptr<Object> owner, Vector2 offset, DIR dir, Vector2 vec, TIME time, int stage, OBJ_TYPE target);

	// 氷の壁
	// pos:座標			time:時間軸
	// stage:ステージ	target:目標
	void MakeIceWall(Vector2 pos, TIME time, int stage, OBJ_TYPE target);

	// スライム
	// pos:座標		dir::向き
	// target:標的の種類
	void MakeSlime(const Vector2& pos, DIR dir, int stage, OBJ_TYPE target);

	// 黄色魔法

	// 雷雲
	// pos:座標				dir:方向
	// speed:速度( speed > 0 でdir方向に、speed < 0 で反対側に)
	// count:落とす雷の数	dur:雷の間隔(フレーム数)
	// time:時間軸			stage:ステージ
	// target:目標
	void MakeThunderCloud(Vector2 pos, DIR dir, int speed, int count, int dur, TIME time, int stage, OBJ_TYPE target);

	// 雷
	// pos1:始点座標		pos2:終点座標
	// useRef:refPosを参照するか(refPosの移動に合わせて動くようになる)
	// refPos:参照に使う座標
	// damage:ダメージ		time:時間軸
	// stage:ステージ		target:目標	
	void MakeThunder(Vector2 pos1, Vector2 pos2, bool useRef, Vector2* refPos, int damage, TIME time, int stage, OBJ_TYPE target);

	// 閃光
	// pos:座標			time:時間軸
	// stage:ステージ	target:目標
	void MakeFlash(Vector2* pos, TIME time, int stage, OBJ_TYPE target);

	// スパーク
	// pos:座標			time:時間軸
	// stage:ステージ	target:目標
	void MakeSpark(Vector2* pos, TIME time, int stage, OBJ_TYPE target);

	// 白魔法

	// 光の柱
	// pos:座標			time:時間軸
	// stage:ステージ	target:目標
	int MakeHolyJudge(Vector2 pos, TIME time, int stage, OBJ_TYPE target);

	// 敵
	
	// 追尾弾
	// ePos:敵の座標		pPos:攻撃時点でのプレイヤーの座標
	// time:時間軸		stage:ステージ
	// target:目標
	void MakeTrackingBall(Vector2 ePos, Vector2 pPos, TIME time, int stage, OBJ_TYPE target);

	// demon槍攻撃
	// pos:敵の座標
	// dir:向いている方向
	// time:時間軸		stage:ステージ
	// target:目標
	void MakeSpearAttack(Vector2 pos, DIR dir, TIME time, int stage, OBJ_TYPE target);
	void MakeThunderAttack(Vector2 pos, DIR dir, TIME time, int stage, OBJ_TYPE target);
	void MakeCaneAttack(Vector2 pos, DIR dir, TIME time, int stage, OBJ_TYPE target);

	void DeleteAll(void);

private:
	static AttackMng* sInstance;

	std::vector<std::shared_ptr<Object>> _attackObj;
	std::vector<std::shared_ptr<Object>> _tmpObj;		// イテレート中の要素追加先	

	bool _canAddObj;

	AttackMng();
	AttackMng(const AttackMng&) = delete;
	AttackMng operator=(const AttackMng&) = delete;
	~AttackMng();
};

