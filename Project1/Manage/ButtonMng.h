#pragma once
#include <map>
#include <DxLib.h>
#include "../common/Vector2.h"

#define lpButtonMng ButtonMng::GetInstance()

#define XINPUT_THUMBL_X 0		// L�X�e�B�b�N�̉�
#define XINPUT_THUMBL_Y 1		// L�X�e�B�b�N�̏c
#define XINPUT_THUMBR_X 2		// R�X�e�B�b�N�̉�
#define XINPUT_THUMBR_Y 3		// R�X�e�B�b�N�̏c

// �X�e�B�b�N�擾�p
#define THUMB_LEFT  0
#define THUMB_RIGHT 1

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

	// �X�e�B�b�N�̏������̂܂܎擾����
	// thumbType �ǂ���̃X�e�B�b�N���擾���邩 THUMB_LEFT��RIGHT�Ŏw��
	// x,y�Ɋi�[���ĕԂ�
	void GetThumb(int thumbType, short& x, short& y);	

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