#include "ButtonMng.h"


ButtonMng* ButtonMng::sInstance = nullptr;

ButtonMng::ButtonMng()
{
	ButtonInit();
}

ButtonMng::~ButtonMng()
{
}

void ButtonMng::Run(void)
{
	GetJoypadXInputState(DX_INPUT_PAD1, &input[0]);
	GetJoypadXInputState(DX_INPUT_PAD2, &input[1]);
	
	UpFlag();
}

std::pair<int, int> ButtonMng::Buttonf(int no,int type)		// �R���g���[���[�ԍ�,�{�^���ԍ����w�肵��pair�ŕԂ� first��old,second��now
{
	return ButtonState[no][type];
}

std::pair<int, int> ButtonMng::Thumbf(int no, int type)
{
	return ThumbState[no][type];
}

const void ButtonMng::Buttonf(int no, int type, int First, int Second)
{
	ButtonState[no][type] = { First,Second };
}

const void ButtonMng::Thumbf(int no, int type, int First, int Second)
{
	ButtonState[no][type] = {First,Second};
}

void ButtonMng::ThumbLFlag(void)
{
	for (int no = 0;no < 2;no++)
	{
		// ���X�e�B�b�N��X��
		if (input[no].ThumbLX > 30000)
		{
			ThumbState[no][XINPUT_THUMBL_X].second = ThumbState[no][XINPUT_THUMBL_X].first;
			ThumbState[no][XINPUT_THUMBL_X].first = 1;
		}
		else if (input[no].ThumbLX < -30000)
		{
			ThumbState[no][XINPUT_THUMBL_X].second = ThumbState[no][XINPUT_THUMBL_X].first;
			ThumbState[no][XINPUT_THUMBL_X].first = 2;
		}
		else
		{
			ThumbState[no][XINPUT_THUMBL_X].second = ThumbState[no][XINPUT_THUMBL_X].first;
			ThumbState[no][XINPUT_THUMBL_X].first = 0;
		}
		// ���X�e�B�b�N��Y��
		if (input[no].ThumbLY > 30000)
		{
			ThumbState[no][XINPUT_THUMBL_Y].second = ThumbState[no][XINPUT_THUMBL_Y].first;
			ThumbState[no][XINPUT_THUMBL_Y].first = 2;
		}
		else if (input[no].ThumbLY < -30000)
		{
			ThumbState[no][XINPUT_THUMBL_Y].second = ThumbState[no][XINPUT_THUMBL_Y].first;
			ThumbState[no][XINPUT_THUMBL_Y].first = 1;
		}
		else
		{
			ThumbState[no][XINPUT_THUMBL_Y].second = ThumbState[no][XINPUT_THUMBL_Y].first;
			ThumbState[no][XINPUT_THUMBL_Y].first = 0;
		}
	}

}

void ButtonMng::UpFlag(void)
{
	//�{�^��
	for (int i = 0; i < 16; i++)
	{
		for (int no = 0;no < 2;no++)
		{
			ButtonState[no][i].second = ButtonState[no][i].first;
			ButtonState[no][i].first = input[no].Buttons[i];
		}
	}
	// �X�e�B�b�NX PL1
	ThumbLFlag();
	//for (int no;no < 2;no++)
	//{
	//	if (input[no].ThumbLX > 15000)
	//	{
	//		ThumbState[no][0].second = ThumbState[no][0].first;
	//		ThumbState[no][0].first = 1;
	//	}
	//	else if (input[no].ThumbLX < -15000)
	//	{
	//		ThumbState[no][0].second = ThumbState[no][0].first;
	//		ThumbState[no][0].first = 2;
	//	}
	//	else
	//	{
	//		ThumbState[no][0].second = ThumbState[no][0].first;
	//		ThumbState[no][0].first = 0;
	//	}
	//}
}
void ButtonMng::ButtonInit(void)
{
	for (int x = 0;x < 2;x++)
	{
		for (int i = 0;i < 16;i++)
		{
			ButtonState[x][i] = { 0, 0 };
		}
	}
	//�@�X�e�B�b�N�̃X�e�[�^�X��0
	for (int y = 0;y < 2;y++)
	{
		for (int x=0;x < 4;x++)
		{
			ThumbState[y][x] = { 0,0 };
		}
	}
}
