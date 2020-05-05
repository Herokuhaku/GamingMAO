#pragma once
#include <map>
#include <DxLib.h>

#define lpButtonMng ButtonMng::GetInstance()

class ButtonMng
{
public:
	static ButtonMng &GetInstance()
	{
		if (sInstance == nullptr)	// いなかったらCreateを呼び出して作る
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
	std::pair<int, int> Buttonf(int no, int type);			// ボタンの情報を返す
	const void Buttonf(int no, int type,int First ,int Second);			// ボタンの情報を上書きする
private:
	static ButtonMng* sInstance;

	ButtonMng();
	~ButtonMng();
	void ButtonInit(void);

	void UpFlag(void);										// 押下情報更新

	XINPUT_STATE input[2];
	int Button[2][16];										// コントローラ番号	1P = 0 ,2P = 1,ボタン番号 0~15
	std::map<int, std::pair<int, int>> ButtonState[2];		// <何番目のボタン,old,now>


};

