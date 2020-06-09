#pragma once
#include <DxLib.h>
#include <cmath>
#include <functional>
#include "Object.h"
#include "../Manage/KeyMng.h"
#include "../func/CheckHitStage.h"
#include "Attack/AttackMng.h"



#define PLAYER_SIZE_X	85
#define PLAYER_SIZE_Y	90

#define DELAY_FIRE		220

#define HP_MAX			100

// �U���̎��
enum class ATK_COLOR : int
{
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MGN,
	CYAN,
	WHITE,
	MAX
};

enum class ATK_TYPE : int
{
	TYPE_1,
	TYPE_2,
	TYPE_3,
	MAX
};

enum class ATK_STATE
{
	NON,
	WAIT,
	RUN
};


class Player :
	public Object
{
public:
	Player();
	Player(Vector2Template<int> pos, int stage, TIME time);
	~Player();

	void Update(void)override;

	void Draw(void)override;
private:
	static constexpr int WALK_SPEED = 4;
	static constexpr double G_ACC_NORMAL = 0.4;
	static constexpr double INI_VEL_NORMAL = 9.0;
	static constexpr double VEL_MAX = 9.0;

	static constexpr int MP_MAX = 100;

	void Init(void);

	void ControlNormal(void);
	void ControlAttack(void);
	void (Player::*_control)(void); // ��2�̊֐��|�C���^

	void StopWalk(void);

	void MagicUpdate(void);
	int _coolTime;

	void MagicSelector(void);

	ATK_COLOR ColorBlend(void);
	void SetAttackState(void);

	void StateRotate(void);

	bool _rotateFlag;

	void VelUpdate(void);

	double _vel;
	//
	bool MenuUpdate(void);

	bool MenuFlag;

	// �U���֌W
	std::array<std::pair<ATK_STATE, unsigned int>, 3> _magicState;		// ���@�̏�ԂƎc��MP
	std::array<ATK_TYPE, static_cast<int>(ATK_COLOR::MAX)> _magicSet;	// �F���Ƃɂǂ̋Z�ɐݒ肵�Ă��邩
	std::array<std::array<std::function<void(void)>, static_cast<int>(ATK_TYPE::MAX)>, static_cast<int>(ATK_COLOR::MAX)> _attack;
	bool _attackFlag; // �U���ł��邩
	ATK_COLOR _cursor;	// �I�𒆂̍U��

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

