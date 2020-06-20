#pragma once
#include <array>
#include "COLOR.h"

#define lpAttackUI AttackUI::GetInstance()
#define STICK_TO_POS(val) (val / (0x7fff / (RING_RADIUS - STICK_OBJ_SIZE / 2)))
#define RAD(val) (val / 180.0 * acos(-1.0f))

// �F���Ƃ̏��
enum class ATK_STATE
{
	NON,
	WAIT,
	RUN
};

class AttackUI
{
public:
	static AttackUI& GetInstance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new AttackUI();
		}
		return *sInstance;
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}

	void Update(void);	// �X�V
	void Draw(void);	// �`��

	COLOR GetAttackColor(void);	// ���݂̍U���F�̎擾

	bool CheckAttackActivate(void);			// �E�X�e�B�b�N�����ȏ�X���Ă��邩
	bool RunAttack(const int& coolTime, const int& MP);		// �U���𔭓�������


private:
	static AttackUI* sInstance;

	// ��`
	static constexpr int Z_ORDER = 500;
	static constexpr int UI_SIZE = 300;
	static constexpr int RING_SIZE = 230;
	static constexpr int RING_RADIUS = 102;
	static constexpr int STICK_OBJ_SIZE = 60;
	static constexpr int EFFECT_ANM_COUNT = 10;
	static constexpr int EFFECT_ANM_INTERVAL = 3;
	static constexpr double EFFECT_EX_RATE_STICK = 1.0;
	static constexpr double EFFECT_EX_RATE_RUN = 5.0;

	static constexpr int DRAW_OFFSET_X = 1150;
	static constexpr int DRAW_OFFSET_Y = 600;

	static constexpr int ACTIVE_RADIUS = 400000000;
	static constexpr double STICK_RADIUS = 0x8000;

	static constexpr float MP_MAX = 100.0;
	static constexpr float MP_REGENERATION_SPEED = 0.1;
	static constexpr int PRIMARY_COLOR_COUNT = 3;

	static constexpr int MP_GAUGE_OFFSET[PRIMARY_COLOR_COUNT] = { 251, 251, 147 };
	static constexpr int MP_GAUGE_HEIGHT[PRIMARY_COLOR_COUNT] = { 149, 149, 98 };

	// UI�p�̃X�N���[���n���h��
	int _uiScreen;

	// �}�X�N�摜�n���h���̊i�[�p
	int _maskHandle[PRIMARY_COLOR_COUNT];

	// �X�e�B�b�N�̏��
	short _stickX;
	short _stickY;
	// �X�e�B�b�N�̐�΍��W
	int _absStickX;
	int _absStickY;

	// �U���F�̏��
	COLOR _OldAttackColor;
	COLOR _AttackColor;

	// �U���̃N�[���^�C��
	int _coolTime;

	void MpUpdate(void);
	void ColorUpdate(void);	// �F�̍X�V
	void StickTrans(void);	// �X�e�B�b�N���W���~�ɕ␳

	std::array<std::pair<ATK_STATE, float>, PRIMARY_COLOR_COUNT> _magicState;	// ���@�̏��

	void StateUpdate(void);	// ���@�̏�Ԃ̍X�V

	AttackUI();
	~AttackUI();
};

