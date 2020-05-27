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

	bool _jumpF;		// �W�����v�t���O
	
	void aState(int work);
	int _aState;		// autoMatonState
	int _work;		// ��Ɨp

	//---------------------------------------------------
	bool _waitF;		// wait�̃t���O
	int _waitCnt;		// wait�̃J�E���g
	int _waitTime;		// wait�̎���
	//---------------------------------------------------
	int _rangeS;		// range of search	����200
	int _rangeA;		// rage of attack	����80
	DIR _plDir;		// 

	bool _encntF;		// encoun
	
	int _speed;		// speed

	int _plStage;	
};
