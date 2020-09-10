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
	
	bool ToFeverTime(void);
	void Active(bool);

	void Reset(void);
private:
	static AttackUI* sInstance;

	void Init(void);

	static constexpr int PRIMARY_COLOR_COUNT = 3;

	static constexpr int MP_GAUGE_OFFSET[PRIMARY_COLOR_COUNT] = { 251, 251, 147 };
	static constexpr int MP_GAUGE_HEIGHT[PRIMARY_COLOR_COUNT] = { 149, 149, 98 };

	// UI�p�̃X�N���[���n���h��
	int _uiScreen;

	// MP�p�X�N���[���n���h��
	int _mpScreen[PRIMARY_COLOR_COUNT];

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

	// MP�����ŏo���鎞��
	int _feverTime;

	void MpUpdate(void);
	void ColorUpdate(void);	// �F�̍X�V
	void StickTrans(void);	// �X�e�B�b�N���W���~�ɕ␳

	bool _active = true;

	std::array<std::pair<ATK_STATE, float>, PRIMARY_COLOR_COUNT> _magicState;	// ���@�̏��

	void StateUpdate(void);	// ���@�̏�Ԃ̍X�V

	AttackUI();
	AttackUI(const AttackUI&) = delete;
	AttackUI operator+(const AttackUI&) = delete;
	~AttackUI();
};

