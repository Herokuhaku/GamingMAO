#pragma once
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include <cmath>
#include "Object.h"
#include "../KeyMng.h"

#define WALK_SPEED		4
#define G_ACC_NORMAL	0.3
#define INI_VEL_NORMAL	8.0

#define PLAYER_SIZE_X	85
#define PLAYER_SIZE_Y	90

#define DELAY_FIRE		350

class Player :
	public Object
{
public:
	Player();
	Player(Vector2Template<int> pos);
	~Player();

	void Update(void);
private:
	void Init(void);

	void ControlNormal(void);
	void ControlAttack(void);
	void (Player::*_control)(void); // è„2Ç¬ÇÃä÷êîÉ|ÉCÉìÉ^

	void MagicUpdate(void);
	int _coolTime;
	int _anmEfkHd;

	void StateRotate(void);

	bool _rotateFlag;

	void VelUpdate(void);
	double _vel;

	Vector2Template<double> _tmpPos;
};

