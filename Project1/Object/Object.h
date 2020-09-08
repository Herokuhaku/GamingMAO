#pragma once
#include <map>
#include <vector>
#include <array>
#include <memory>
#include "../common/Vector2.h"
#include "DIR.h"
#include "../Manage/TimeMng.h"

enum class OBJ_TYPE : int
{
	PLAYER,
	ENEMY,
	ITEM,
	CAMERA,
	ATTACK,
	MAX
};

enum class OBJ_STATE : int
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

enum class CHECK_DIR : int
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// 状態異常
enum class STATE_EFFECT_TYPE
{
	PARALYSIS,
	FREEZE,
	CONFUSION
};

enum class COLLISION_TYPE
{
	SQUARE,
	CIRCLE,
};

class StateEffect;

using AnmVec = std::vector<std::pair<int, unsigned int>>;

struct atkData
{
	bool _isHit;
	OBJ_TYPE _myType;

	Vector2 _topLeft;
	Vector2 _bottomRight;

	Vector2 _offset;
	float _radius;

	int _damage;
	int _invincibleTime;
	OBJ_TYPE _target;
	COLLISION_TYPE _colType;

	atkData(bool isHit, OBJ_TYPE mytype, const Vector2& topleft, const Vector2& bottomright, int damage, int inv, OBJ_TYPE target) :
		_isHit(isHit), _myType(mytype), _topLeft(topleft), _bottomRight(bottomright), _damage(damage), _invincibleTime(inv), _target(target) 
	{
		_colType = COLLISION_TYPE::SQUARE;
	};

	atkData(bool isHit, OBJ_TYPE mytype, const Vector2& offset, float rad, int damage, int inv, OBJ_TYPE target) :
		_isHit(isHit), _myType(mytype), _offset(offset), _radius(rad), _damage(damage), _invincibleTime(inv), _target(target)
	{
		_colType = COLLISION_TYPE::CIRCLE;
	};

	int GetLeft(void)const;
	int GetRight(void)const;

	bool IsHit(const Vector2& mypos, DIR mydir, const Vector2& targetpos, const std::array<int, 4>& hitbox)const;
};

class Object
{
public:
	Object();
	virtual ~Object();
	
	virtual void Update(void);

	void setPos(Vector2Template<int> pos);
	void setPlTmpPos(Vector2Template<int> pos) { _tmpPos = { static_cast<double>(pos.x),static_cast<double>(pos.y) }; };
	Vector2Template<int> getPos(void);
	Vector2Template<int> getPosWithOffset(void);

	void MovePos(const Vector2Template<int>& pos);

	void setState(std::pair<OBJ_STATE, DIR> state);
	std::pair<OBJ_STATE, DIR> getState(void);
	
	// 状態異常関係
	void SetStateEffect(StateEffect* sEff);
	void UpdateStateEffect(void);
	bool IsEffected(STATE_EFFECT_TYPE type);
	bool CanMoveWithEffect(void);

	void setHP(int hp);
	int getHP(void);
	virtual void damagingHP(int damage);

	void setInv(int time);
	bool checkInv(void);
	void InvUpdate(void);

	OBJ_TYPE getObjType(void) { return _type; };

	void setHitOffset(std::array<int, 4> ary);
	std::array<int, 4> getHitOffset(void);

	void setAnm(const std::pair<OBJ_STATE, DIR> state, AnmVec& data);
	bool isAnmEnd(void);
	bool isAlive(void);
	bool Alive(void) { return _alive; };

	virtual void Draw(void);
	bool anmUpdate(void);
	
	void setAttack(const std::string key, std::vector<atkData>& data);
	void AddAttack(const std::string key);
	void attackUpdate(void);
	std::vector<atkData>& getAttackQue(void);
	int getAnmEfk(void);
	void stopAttack(void);

	void setTimeLine(TIME time);
	TIME getTimeLine(void);

	void setStage(int stage) { _stage = stage; };
	int getStage(void) { return _stage; };

	virtual void IfHitAttack(std::shared_ptr<Object> target);

	void nextPos(void) { _pos = _nextPos; _tmpPos = { static_cast<double>(_nextPos.x),static_cast<double>(_nextPos.y) }; };
private:
	int _inv;						// 無敵時間　0なら無敵ではない
	std::array<int, 4> _hitBox;	// 座標からの当たり判定の範囲 0:左 1:右 2:上 3:下
protected:
	int _hp;						// 体力
	Vector2 _pos;					// 座標(x:中心　y:下辺)
	double _rad;					// 角度
	int _drawOffset_y;				// 描画時のオフセット(画像の中央座標 - 下辺座標)

	TIME _time;						// 時間軸
	int _stage;						// ステージ

	bool _alive;					// 生きてるか

	bool _isColored = false;

	std::vector<std::unique_ptr<StateEffect>> _sEff; // 状態異常
	void DrawStateEffect(void);

	int _zOrder;							// Zオーダー
	double _exRate;							// 拡大率
	OBJ_TYPE _type;							// オブジェクトの種類
	std::pair<OBJ_STATE, DIR> _state_dir;	// オブジェクトの状態
	double _stateEffectExRate = 1.0;

	std::map<std::pair<OBJ_STATE, DIR>, AnmVec> _anmMap;	// アニメーションを保存するとこ
	unsigned int _anmTime;			// アニメーションの経過時間
	unsigned int _anmFlame;			// アニメーションの現在のコマ数

	int _anmEfkHd;					// effekseerのアニメーションハンドル

	Vector2Template<double> _tmpPos;

	std::map<std::string, std::vector<atkData>> _attackMap;	// 攻撃の情報
	std::vector<std::pair<std::string, unsigned int>> _attackData;	// 攻撃中の攻撃

	// 返すデータ
	std::vector<atkData> rtnvec;
protected:
	// ステージ移動
	Vector2 _nextPos;

};

class StateEffect
{
	friend Object;

	STATE_EFFECT_TYPE _type;
	int _duration;
	int _timer;
public:
	/// <summary>
	/// 状態異常
	/// </summary>
	/// <param name="type">状態異常の種類</param>
	/// <param name="duration">持続時間</param>
	StateEffect(STATE_EFFECT_TYPE type, int duration) :_type(type), _duration(duration), _timer(duration) {};
	~StateEffect() = default;
};
