#pragma once
#include <DxLib.h>
#include <cmath>
#include <functional>
#include "Object.h"
#include "../Manage/AttackUI.h"
#include <memory>

#define PLAYER_SIZE_X	85
#define PLAYER_SIZE_Y	90

#define DELAY_FIRE		220

#define HP_MAX			100

class GameScene;
struct StopTime;

enum class ATK_TYPE : int
{
	TYPE_1,
	TYPE_2,
	TYPE_3,
	MAX
};

class MagicMenu;

class Player :
	public Object
{
	friend MagicMenu;
public:
	Player() = delete;
	Player(Vector2Template<int> pos, int stage, TIME time, GameScene* gs);
	Player(const Player&) = delete;
	~Player();

	void Update(void)override;

	void Draw(void)override;

	bool IsTimeStoped(void);

	std::unique_ptr<StopTime>& GetStopTime(void);
private:
	static constexpr double G_ACC_NORMAL = 0.4;
	static constexpr double INI_VEL_NORMAL = 9.0;
	static constexpr double INI_VEL_SUPER = 20.0;
	static constexpr double VEL_MAX = 9.0;

	static constexpr int MP_MAX = 100;

	static constexpr int WING_OFFSET = 120;

	static 	constexpr int DASH_DURATION = 5;

	void Init(void);

	void ControlNormal(void);
	void ControlAttack(void);
	void ControlDash(void);
	void (Player::*_control)(void); // è„2Ç¬ÇÃä÷êîÉ|ÉCÉìÉ^

	void StopWalk(void);

	void MagicUpdate(void);
	int _coolTime;

	void StateRotate(void);

	bool _rotateFlag;

	bool _isSuperJump;

	void VelUpdate(void);

	double _vel;
	int _speed;

	bool MenuUpdate(void);
	bool Attack(void);
	void Portal(void);

	bool MenuFlag;

	Vector2 _centerPos;
	Vector2 _wingPos;

	GameScene* _gameScene;

	std::unique_ptr<StopTime> _stopTime;

	static constexpr int HISTORY_COUNT = 5;
	int _dashTimer;
	std::array<std::pair<Vector2F, DIR>, HISTORY_COUNT> _dashHistory;
	bool _writeHistory = false;
	void HistoryUpdate(void);
	void HistoryDraw(void);
	DIR _dashDir;
	std::pair<OBJ_STATE, DIR> _tmpsd;

	// çUåÇä÷åW
	std::array<ATK_TYPE, static_cast<int>(COLOR::MAX)> _magicSet;	// êFÇ≤Ç∆Ç…Ç«ÇÃãZÇ…ê›íËÇµÇƒÇ†ÇÈÇ©
	std::array<std::array<std::function<void(void)>, static_cast<int>(ATK_TYPE::MAX)>, static_cast<int>(COLOR::MAX)> _attack;

	void Red1(void);
	void Red2(void);
	void Red3(void);
	void Green1(void);
	void Green2(void);
	void Green3(void);
	void Yellow1(void);
	void Yellow2(void);
	void Yellow3(void);
	void Blue1(void);
	void Blue2(void);
	void Blue3(void);
	void Magenta1(void);
	void Magenta2(void);
	void Magenta3(void);
	void Cyan1(void);
	void Cyan2(void);
	void Cyan3(void);
	void White1(void);
	void White2(void);
	void White3(void);
};

