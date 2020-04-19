#pragma once
#include <DxLib.h>
#include <Object/Object.h>
#include <KeyMng.h>

#define WALK_SPEED		2
#define G_ACC_NORMAL	0.1
#define INI_VEL_NORMAL	5.0

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

	void Control(void);
	void VelUpdate(void);
	double _vel;

	Vector2Template<double> _tmpPos;
};

