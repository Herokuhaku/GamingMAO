#include "Enemy.h"
#include "EnemyMng.h"
#include "../../Scene/SceneMng.h"
#include "../../Manage/MapMng.h"
#include "../../Manage/ItemTrader.h"

void Enemy::Update(void)
{
	Gravity();
	if (_state_dir.first == OBJ_STATE::DEAD)
	{
		return;
	}
	auto tmp = lpSceneMng.GetPlObj(TIME::FTR);
	auto plPos = (*tmp)->getPos();
	// ???
	if (_aState < 0 || _aState >= 5)
	{
		_aState = 0;
	}
	// ???
	_work = (this->*autoM[_aState])(plPos);
	_work =	Search(plPos);

	aState(_work);
}

int Enemy::Wait(Vector2 pPos)
{
	_waitCnt++;
	if (_waitCnt >= _waitTime)
	{
		setState({ OBJ_STATE::WALK, _plDir });
		return static_cast<int>(MOVE_SELECT::MOVE);
	}
	return _aState;
}

int Enemy::Move(Vector2 pPos)
{
	if( !_jumpF)
	{
		if (!_encntF)
		{
			int x;
			int y;

			if (_state_dir.second == DIR::RIGHT)
			{
				_pos.x += _speed;
				x = (_pos.x + 64);
				y = (_pos.y - 16); 
				if(lpMapMng.getHitMap({x,y},_stage))		// 壁
				{
					setState({ OBJ_STATE::WALK,DIR::LEFT });
				}

				x = (_pos.x + 64);
				y = (_pos.y + 1); 
				if(!lpMapMng.getHitMap({x,y},_stage))		// 床がない
				{
					setState({ OBJ_STATE::WALK,DIR::LEFT });
				}
			}
			else
			{
				_pos.x -= _speed;
				x = (_pos.x - 64);
				y = (_pos.y - 16);
				if(lpMapMng.getHitMap({x,y},_stage))
				{
					setState({ OBJ_STATE::WALK,DIR::RIGHT });
				}

				x = (_pos.x - 64);
				y = (_pos.y + 1);
				if(!lpMapMng.getHitMap({x,y},_stage))
				{
					setState({ OBJ_STATE::WALK,DIR::RIGHT });
				}
			}
			RandWait();
			return _aState;
		}
		else
		{
			return 	AtkMove(pPos);
		}
	}
}

void Enemy::RandWait(void)
{
	if (std::rand() % 500 == 0)
	{
		setState({ OBJ_STATE::NORMAL, _state_dir.second });
		_waitTime = 140;	// クールタイム
		_waitF = false;
		_waitCnt = 0;
		_aState = static_cast<int>(MOVE_SELECT::WAIT);
	}
}

int Enemy::Search(Vector2 pPos)
{
	_plDir = pPos.x > _pos.x ? DIR::RIGHT : DIR::LEFT;
	if (_waitCnt >= _waitTime)
	{
		if (_stage == lpEnemyMng.GetPlStage())
		{
			if (pPos.y < _pos.y + 10 && pPos.y > _pos.y - 10)
			{
				if ((pPos.x - _pos.x)  * (static_cast<int>(_state_dir.second) - 1) <= _rangeS &&
					(pPos.x - _pos.x)  * (static_cast<int>(_state_dir.second) - 1) >= -80)
				{
					if ((pPos.x - _pos.x) * (static_cast<int>(_state_dir.second) - 1) <= _rangeA)
					{
						aState(static_cast<int>(MOVE_SELECT::ATTACK));
						lpImageMng.AddDraw({ lpImageMng.getImage("excPoint")[0], _pos.x, _pos.y - _drawOffset_y, 1.0, 0.0, LAYER::EX, 10, DX_BLENDMODE_NOBLEND, 0 });
						return _aState;
					}
					lpImageMng.AddDraw({ lpImageMng.getImage("queMark")[0], _pos.x, _pos.y - _drawOffset_y, 1.0, 0.0, LAYER::EX, 10, DX_BLENDMODE_NOBLEND, 0 });
					_encntF = true;
					return static_cast<int>(MOVE_SELECT::MOVE);
				}
			}
		}
		_encntF = false;
	}
	return _work;
}

int Enemy::Attack(Vector2 pPos)
{
	if (_state_dir.first != OBJ_STATE::ATTACK)
	{
		setState({ OBJ_STATE::ATTACK, _plDir });
		_waitTime = 140;	// クールタイム
		_waitCnt = 0;
		return static_cast<int>(MOVE_SELECT::WAIT);
	}
	return static_cast<int>(MOVE_SELECT::WAIT);
}

int Enemy::AtkMove(Vector2 pPos)
{
	if (_state_dir.second == DIR::RIGHT)
	{
		_pos.x += _speed + 1;
	}
	else
	{
		_pos.x -= _speed + 1;
	}
	return _aState;
}

void Enemy::damagingHP(int damage)
{
	setState({ OBJ_STATE::DAMAGE, _state_dir.second });
	_waitCnt = 0;
	_waitTime = 60;	// クールタイム
	aState(static_cast<int>(MOVE_SELECT::WAIT));

	int ddir = _plDir == DIR::LEFT ? 13 : -13;
	
	// 画面外や壁に埋まらないように処理
	if (lpMapMng.getHitMap(_pos, _stage))
	{
	}
	else
	{
		_pos.x += ddir;
	}

	Object::damagingHP(damage);
}

Enemy::Enemy()
{
	_aState = 0;
	_drawOffset_y = 26;		// sizeの半分の18とMAPCHIPは中心描画だからそのの半分の8
	Init();
}

void Enemy::Init(void)
{
	_jumpF = false;
	_waitTime = std::rand() % 180;
	_waitCnt = 0;
	_waitF = true;
	_rangeS = 200;
	_rangeA = 80;
	_encntF = false;
	_plDir = DIR::RIGHT;
	_speed = 1;
	_type = OBJ_TYPE::ENEMY;
	_etype = ENEMY_TYPE::MAX;
	_stage = 1;
	_pPos = 1;
	_time = TIME::FTR;
	_divNum = 70;
	_maxHP = _hp;
}

void Enemy::Draw(void)
{
	Object::Draw();
	DrawHP();
}

void Enemy::DrawHP(void)
{
	int tmpNum;
	for (int i = 0; i < 10; i++)
	{
		if (getHP() >= i * 10 + 1)
		{
			tmpNum = 0;
		}
		else
		{
			tmpNum = 2;
		}
		lpImageMng.AddDraw({ lpImageMng.getImage("hp_bar")[tmpNum], _pos.x - 27 + 6 * i, _pos.y - 30 - _drawOffset_y, 1.0, 0.0, LAYER::EX, 0, DX_BLENDMODE_NOBLEND, 0 });
	}
}

void Enemy::Gravity(void)
{
		if(!lpMapMng.getHitMap(_pos,_stage))
		{
				_pos.y++;
				_jumpF = true;
				return;
		}
		_jumpF = false;
}

void Enemy::aState(int work)
{
	if ( work < e_fn_ptr_num)
	{
		_aState = work;
	}
	else
	{
		// エラー
		_aState = 0;
	}
}

Enemy::~Enemy()
{
	if (_hp <= 0)
	{
		lpEnemyMng.addDeadCnt(_etype, _stage, _pPos);
		lpTradeMng.SetItemList(_pos, ITEM_TYPE::BOOK, COLOR_TYPE::GREEN, _stage);
	}
}

