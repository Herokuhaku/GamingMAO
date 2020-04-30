#pragma once
#include <map>
#include <DxLib.h>

#define lpButtonMng ButtonMng::GetInstance()

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
	const void Buttonf(int no, int type,int First ,int Second);			// �{�^���̏����㏑������
private:
	static ButtonMng* sInstance;

	ButtonMng();
	~ButtonMng();
	void ButtonInit(void);

	void UpFlag(void);										// �������X�V

	XINPUT_STATE input[2];
	int Button[2][16];										// �R���g���[���ԍ�	1P = 0 ,2P = 1,�{�^���ԍ� 0~15
	std::map<int, std::pair<int, int>> ButtonState[2];		// <���Ԗڂ̃{�^��,old,now>


};

