#pragma once
#include <common/Vector2.h>
#include <map>
#include <vector>
#include <Graphic/ImageMng.h>

enum class OBJ_TYPE
{
	PLAYER,
	ENEMY,
	ITEM,
	CAMERA,
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
	FALL,
	ATTACK,
	DEAD
};

enum class DIR
{
	LEFT,
	NORMAL,
	RIGHT
};

enum class TIME
{
	NOW,	// 現在
	FTR,	// 未来
};

using AnmVec = std::vector<std::pair<int, unsigned int>>;

class Object
{
public:
	Object();
	virtual ~Object();

	virtual void Update(void) = 0;

	void setPos(Vector2Template<int> pos);
	Vector2Template<int> getPos(void);

	void setState(std::pair<OBJ_STATE, DIR> state);
	std::pair<OBJ_STATE, DIR> getState(void);

	void setAnm(const std::pair<OBJ_STATE, DIR> state, AnmVec& data);
	bool isAnmEnd(void);
	bool isAlive(void);

	void Draw(void);
	void anmUpdate(void);
private:
	std::map<std::pair<OBJ_STATE, DIR>, AnmVec> _anmMap;	// アニメーションを保存するとこ
	unsigned int _anmTime;				// アニメーションの経過時間
	unsigned int _anmFlame;		// アニメーションの現在のコマ数

protected:
	Vector2Template<int> _pos;	// 座標
	double _rad;				// 角度

	TIME _time;					// 時間軸
	int _stage;					// ステージ

	bool _alive;				// 生きてるか

	int _zOrder;							// Zオーダー
	OBJ_TYPE _type;							// オブジェクトの種類
	std::pair<OBJ_STATE, DIR> _state_dir;	// オブジェクトの状態
};

