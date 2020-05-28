#pragma once
#include "Enemy.h"

class Boss : public Enemy
{
public:
	//void Update(void);

	void DrawHP(void) override;

	Boss();
	~Boss();

private:
	void (Boss::*func)(void);

	int _startCnt;
	int _saveDivNum;
	
	void funcDrawHPStart(void);
	void funcDrawHP(void);
};

