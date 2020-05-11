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

	Enemy();
	~Enemy();
private:
	void Init(void);
	void Gravity(void);
protected:

using e_fn_ptr = int(Enemy::*)(Vector2 pPos);	// 

static const int e_fn_ptr_num = 5;

	const e_fn_ptr  autoM[e_fn_ptr_num]
		= { &Enemy::Wait, &Enemy::Move,
			&Enemy::AtkMove,&Enemy::Attack,
			&Enemy::Search,};	// autoMaton

	bool _jumpF;		// ジャンプフラグ
	
	void aState(int work);
	int _aState;		// autoMatonState
	int _work;		// 作業用

	//---------------------------------------------------
	bool _waitF;		// waitのフラグ
	int _waitCnt;		// waitのカウント
	int _waitTime;		// waitの時間
	//---------------------------------------------------
	int _rangeS;		// range of search
	int _rangeA;		// rage of attack
	DIR _plDir;		// 

	bool _encntF;		// encoun
	
	int _speed;		// speed
};
