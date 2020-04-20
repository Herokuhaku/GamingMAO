#pragma once
#include <DxLib.h>
#include <Obj/Object.h>
#include <KeyMng.h>

#define WALK_SPEED		4
#define G_ACC_NORMAL	0.3
#define INI_VEL_NORMAL	8.0

#define PLAYER_SIZE_Y	90

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
	void ControlJump(void);
	void (Player::*_control)(void); // è„ÇQÇ¬ÇÃä÷êîÉ|ÉCÉìÉ^


	void VelUpdate(void);
	double _vel;

	Vector2Template<double> _tmpPos;
};

