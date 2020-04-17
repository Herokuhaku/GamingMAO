#pragma once
#include <DxLib.h>
#include <Object/Object.h>

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
};

