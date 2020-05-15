#pragma once
#include <map>
#include <DxLib.h>
#include "../common/Vector2.h"

#define lpButtonMng ButtonMng::GetInstance()

#define XINPUT_THUMBL_X 0		// L�X�e�B�b�N�̉�
#define XINPUT_THUMBL_Y 1		// L�X�e�B�b�N�̏c
#define XINPUT_THUMBR_X 2		// R�X�e�B�b�N�̉�
#define XINPUT_THUMBR_Y 3		// R�X�e�B�b�N�̏c

class ButtonMng
{
public:
	static ButtonMng &GetInstance()
	{
		if (sInstance == nullptr)	// ���Ȃ�������Create���Ăяo���č��
		{
			Create();
		}
		return *sInstance;
	}

	static void Create(void)
	{
		sInstance = new ButtonMng();
	}

	static void Destroy(void)
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}
	void Run(void);
	std::pair<int, int> Buttonf(int no, int type);			// �{�^���̏���Ԃ�
	std::pair<int, int> Thumbf(int no, int type);			// �X�e�B�b�N�̏���Ԃ�

	const void Buttonf(int no, int type,int First ,int Second);			// �{�^���̏����㏑������
	const void Thumbf(int no, int type, int First, int Second);

	void ThumbLFlag(void);
private:
	static ButtonMng* sInstance;

	ButtonMng();
	~ButtonMng();
	void ButtonInit(void);

	void UpFlag(void);										// �������X�V

	XINPUT_STATE input[2];
	int Button[2][16];										// �R���g���[���ԍ�	1P = 0 ,2P = 1,�{�^���ԍ� 0~15
	std::map<int, std::pair<int, int>> ButtonState[2];		// <���Ԗڂ̃{�^��,now,old>

	Vector2 Thumb[2][4];									// �R���g���[���[�ԍ� ,0,L�X�e�B�b�N�A1,R�X�e�B�b�N
	std::map<int, std::pair<int, int>> ThumbState[2];		// now,old
};

//short					ThumbLX;						// ���X�e�B�b�N�̉����l( -32768 �` 32767 )
//short					ThumbLY;						// ���X�e�B�b�N�̏c���l( -32768 �` 32767 )
//short					ThumbRX;						// �E�X�e�B�b�N�̉����l( -32768 �` 32767 )
//short					ThumbRY;						// �E�X�e�B�b�N�̏c���l( -32768 �` 32767 )
