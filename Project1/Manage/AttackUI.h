#pragma once
#include <array>
#include "COLOR.h"

#define lpAttackUI AttackUI::GetInstance()
#define STICK_TO_POS(val) (val / (0x7fff / (RING_RADIUS - STICK_OBJ_SIZE / 2)))
#define RAD(val) (val / 180.0 * acos(-1.0f))

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

	bool CheckAttackActivate(void);			// �E�X�e�B�b�N�����ȏ�X���Ă��邩
	COLOR RunAttack(int coolTime);		// �U���𔭓�������


private:
	static AttackUI* sInstance;

	// ��`
	static constexpr int UI_SIZE = 300;
	static constexpr int RING_SIZE = 204;
	static constexpr int RING_RADIUS = 100;
	static constexpr int STICK_OBJ_SIZE = 60;
	static constexpr int EFFECT_ANM_COUNT = 10;
	static constexpr int EFFECT_ANM_INTERVAL = 3;
	static constexpr double EFFECT_EX_RATE = 1.0;

	static constexpr int DRAW_OFFSET_X = 1150;
	static constexpr int DRAW_OFFSET_Y = 600;

	static constexpr int ACTIVE_RADIUS = 70000000;
	static constexpr double STICK_RADIUS = 0x8000;

	static constexpr int MP_MAX = 100;

	// UI�p�̃X�N���[���n���h��
	int _uiScreen;	

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

	void ColorUpdate(void);	// �F�̍X�V
	void StickTrans(void);	// �X�e�B�b�N���W���~�ɕ␳

	std::array<std::pair<ATK_STATE, unsigned int>, 3> _magicState;

	void StateUpdate(void);	// ���@�̏�Ԃ̍X�V

	AttackUI();
	~AttackUI();
};

