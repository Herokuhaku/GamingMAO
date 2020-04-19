#pragma once
#include "../Object.h"
#include <memory>

class Enemy :
	public Object
{
public:
	virtual	void Update(void);
	virtual int Wait(Vector2 pPos);
	virtual int Move(Vector2 pPos);
	virtual int Search(Vector2 pPos);
	virtual int Attack(Vector2 pPos);

	Enemy();
	~Enemy();
private:
	void Init(void);
protected:

using e_fn_ptr = int(Enemy::*)(Vector2 pPos);	// 

static const int e_fn_ptr_num = 4;

	const e_fn_ptr const autoM[e_fn_ptr_num]
		= { &Enemy::Wait, &Enemy::Move,
			&Enemy::Search, &Enemy::Attack };	// autoMaton

	int _aState;		// autoMatonState
	int _work;			// ��Ɨp

	//---------------------------------------------------
	bool _waitF;		// wait�̃t���O
	int _waitCnt;		// wait�̃J�E���g
	int _waitTime;		// wait�̎���
	//---------------------------------------------------
	int _rangeS;		// range of search

};
