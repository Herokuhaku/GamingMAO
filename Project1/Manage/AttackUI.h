#pragma once
#include <cstddef>

#define lpAttackUI AttackUI::GetInstance()
#define STICK_TO_POS(val) (val / (0x7fff / (RING_RADIUS - STICK_OBJ_SIZE / 2)))
#define RAD(val) (val / 180 * acos(-1.0f))

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

	bool CheckAttackActivate(void);	// �E�X�e�B�b�N�����ȏ�X���Ă��邩
	int GetColor(void);				// ���݂̐F��Ԃ�
private:
	static AttackUI* sInstance;

	// ��`
	constexpr static int UI_SIZE = 300;
	constexpr static int RING_SIZE = 204;
	constexpr static int RING_RADIUS = 100;
	constexpr static int STICK_OBJ_SIZE = 60;

	constexpr static int DRAW_OFFSET_X = 1150;
	constexpr static int DRAW_OFFSET_Y = 600;

	constexpr static int ACTIVE_RADIUS = 40000000;
	constexpr static double STICK_RADIUS = 0x8000;

	constexpr static int RED_BYTE	= 0b001;
	constexpr static int GREEN_BYTE = 0b010;
	constexpr static int BLUE_BYTE	= 0b100;

	// UI�p�̃X�N���[���n���h��
	int _uiScreen;	

	// �X�e�B�b�N�̏��
	short _stickX;
	short _stickY;

	// ���݂̍U���F�̏��
	int _AttackColor;

	void ColorUpdate(void);	// �F�̍X�V
	void StickTrans(void);	// �X�e�B�b�N���W���~�ɕ␳

	AttackUI();
	~AttackUI();
};

