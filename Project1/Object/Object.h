#pragma once
#include <map>
#include <vector>
#include "../Graphic/ImageMng.h"
#include "../common/Vector2.h"
#include "DIR.h"
#include "../Manage/TimeMng.h"

enum class OBJ_TYPE
{
	PLAYER,
	ENEMY,
	ITEM,
	CAMERA,
	MAX
};

enum class OBJ_STATE
{
	NORMAL,
	WALK,
	DASH,
	JUMP,
	A_NORMAL,
	A_WALK,
	A_DASH,
	A_JUMP,
	DAMAGE,
	FALL,
	ATTACK,
	DEAD
};

enum class CHECK_DIR
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

using AnmVec = std::vector<std::pair<int, unsigned int>>;
using atkData = std::tuple<bool, OBJ_TYPE, Vector2, Vector2, int, int, OBJ_TYPE>;

class Object
{
public:
	Object();
	virtual ~Object();

	virtual void Update(void);

	void setPos(Vector2Template<int> pos);
	Vector2Template<int> getPos(void);

	void setState(std::pair<OBJ_STATE, DIR> state);
	std::pair<OBJ_STATE, DIR> getState(void);

	void setHP(int hp);
	int getHP(void);
	void damagingHP(int damage);

	void setInv(int time);
	bool checkInv(void);
	void InvUpdate(void);

	OBJ_TYPE getType(void) { return _type; };

	void setHitOffset(std::array<int, 4> ary);
	std::array<int, 4> getHitOffset(void);

	void setAnm(const std::pair<OBJ_STATE, DIR> state, AnmVec& data);
	bool isAnmEnd(void);
	bool isAlive(void);

	virtual void Draw(void);
	bool anmUpdate(void);

	void setAttack(const std::string key, std::vector<atkData>& data);
	void AddAttack(const std::string key);
	void attackUpdate(void);
	std::vector<atkData> getAttackQue(void);
	void stopAttack(void);

	void setTimeLine(TIME time);
	TIME getTimeLine(void);

	int getStage(void) { return _stage; };

	void nextPos(void) { _pos = _nextPos; _tmpPos = { static_cast<double>(_nextPos.x),static_cast<double>(_nextPos.y) }; };
private:
	int _hp;						// 体力
	int _inv;						// 無敵時間　0なら無敵ではない
	std::array<int, 4> _hitOffset;	// 座標からの当たり判定の範囲 0:左 1:右 2:上 3:下

	static std::map<std::string, std::vector<atkData>> _attackMap;	// 攻撃の情報
	std::vector<std::pair<std::string, unsigned int>> _attackData;	// 攻撃中の攻撃

protected:
	Vector2 _pos;					// 座標(x:中心　y:下辺)
	double _rad;					// 角度
	int _drawOffset_y;				// 描画時のオフセット(画像の中央座標 - 下辺座標)

	TIME _time;						// 時間軸
	int _stage;						// ステージ

	bool _alive;					// 生きてるか

	int _zOrder;							// Zオーダー
	OBJ_TYPE _type;							// オブジェクトの種類
	std::pair<OBJ_STATE, DIR> _state_dir;	// オブジェクトの状態

	std::map<std::pair<OBJ_STATE, DIR>, AnmVec> _anmMap;	// アニメーションを保存するとこ
	unsigned int _anmTime;			// アニメーションの経過時間
	unsigned int _anmFlame;			// アニメーションの現在のコマ数

	int _anmEfkHd;					// effekseerのアニメーションハンドル

	Vector2Template<double> _tmpPos;
protected:
	// ステージ移動
	Vector2 _nextPos;

};
