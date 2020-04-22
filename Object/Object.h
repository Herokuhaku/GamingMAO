#pragma once
#include <map>
#include <vector>
#include <memory>
#include "../Graphic/ImageMng.h"
#include "Object.h"


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

using AnmVec = std::vector<std::pair<int, int>>;

class Object
{
public:
	Object();
	virtual ~Object();

	virtual void Update(void) = 0;

	OBJ_TYPE getType(void) { return _type; };

	void setPos(Vector2Template<int> pos);
	Vector2Template<int> getPos(void);
	Vector2Template<int>* getPos2(void);

	void setState(std::pair<OBJ_STATE, DIR> state);
	std::pair<OBJ_STATE, DIR> getState(void);

	void setAnm(const std::pair<OBJ_STATE, DIR> state, AnmVec& data);
	bool isAnmEnd(void);
	bool isAlive(void);

	virtual void Draw(void);
	void anmUpdate(void);
protected:
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

