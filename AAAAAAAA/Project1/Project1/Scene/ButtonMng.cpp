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

std::pair<int, int> ButtonMng::Buttonf(int no,int type)		// コントローラー番号,ボタン番号を指定してpairで返す firstがold,secondがnow
{
	return ButtonState[no][type];
}

void ButtonMng::UpFlag(void)
{
	for (int i = 0; i < 16; i++)
	{	
		for (int no = 0;no < 2;no++)
		{
			ButtonState[no][i].second = ButtonState[no][i].first;
			ButtonState[no][i].first = input[no].Buttons[i];
		}
	}
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
}
