#pragma once
#include "Enemy.h"
//#includ

enum class AtkList
{
	TRACKING_BALL,
	THUNDER,
	CANE_ATTACK,		// èÒ
	MAX
};

class Boss : public Enemy
{
public:

	void DrawHP(void) override;

	Boss();
	~Boss();

	void RunAtkList(void);

private:
	void (Boss::*func)(void);

protected:
	int _startCnt;
	int _saveDivNum;
	int _tmpHP;

	std::vector<std::pair<AtkList, int>> atkList;		// <,å¬êî>

	
	void funcDrawHPStart(void);
	void funcDrawHP(void);
};

