#pragma once
#include "../Object.h"
#include <memory>

enum class MOVE_SELECT
{
	WAIT,
	MOVE,
	ATKMOVE,
	ATTACK,
	MAX
};

enum class ENEMY_TYPE
{
	s_dragon,
	demon,
	wizard,
	sorcerer,
	MAX
};

class Enemy :
	public Object
{
public:
	virtual	void Update(void);
	virtual int Wait(Vector2 pPos);
	virtual int Move(Vector2 pPos);
	virtual int Search(Vector2 pPos);
	virtual int Attack(Vector2 pPos);
	virtual int AtkMove(Vector2 pPos);

	void damagingHP(int damage) override;

	void Draw(void);
	virtual void DrawHP(void);

private:
	void Init(void);
	void Gravity(void);
protected:
	Enemy();
	~Enemy();

using e_fn_ptr = int(Enemy::*)(Vector2 pPos);	// 

static const int e_fn_ptr_num = 5;

	const e_fn_ptr  autoM[e_fn_ptr_num]
		= { &Enemy::Wait, &Enemy::Move,
			&Enemy::AtkMove,&Enemy::Attack,
			&Enemy::Search,};	// autoMaton

	ENEMY_TYPE _etype;
	int _pPos;			// placePos popPos

	bool _jumpF;		// ジャンプフラグ
	
	void aState(int work);
	int _aState;		// autoMatonState
	int _work;		// 作業用

	//---------------------------------------------------
	bool _waitF;		// waitのフラグ
	int _waitCnt;		// waitのカウント
	int _waitTime;		// waitの時間
	//---------------------------------------------------
	int _rangeSF;		// range of search	初期200
	int _rangeSB;		// range of search	初期100
	int _rangeA;		// rage of attack	初期80
	DIR _plDir;		// 

	bool _encntF;		// encoun
	
	int _speed;		// speed

	int _plStage;	

	void RandWait(void);	//	

	int _maxHP;
	int _divNum;		// HPを描画するときの分割数

	Vector2 _size;
};
