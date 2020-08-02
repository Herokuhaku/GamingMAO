#pragma once
#include "Enemy.h"

class Boss : public Enemy
{
public:

	void DrawHP(void) override;

	Boss();
	~Boss();

private:
	void (Boss::*func)(void);

protected:
	int _startCnt;
	int _saveDivNum;
	int _tmpHP;
	
	void funcDrawHPStart(void);
	void funcDrawHP(void);
};

