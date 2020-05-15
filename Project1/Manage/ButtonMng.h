#pragma once
#include <map>
#include <DxLib.h>
#include "../common/Vector2.h"

#define lpButtonMng ButtonMng::GetInstance()

#define XINPUT_THUMBL_X 0		// Lスティックの横
#define XINPUT_THUMBL_Y 1		// Lスティックの縦
#define XINPUT_THUMBR_X 2		// Rスティックの横
#define XINPUT_THUMBR_Y 3		// Rスティックの縦

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
	std::pair<int, int> Thumbf(int no, int type);			// スティックの情報を返す

	const void Buttonf(int no, int type,int First ,int Second);			// ボタンの情報を上書きする
	const void Thumbf(int no, int type, int First, int Second);

	void ThumbLFlag(void);
private:
	static ButtonMng* sInstance;

	ButtonMng();
	~ButtonMng();
	void ButtonInit(void);

	void UpFlag(void);										// 押下情報更新

	XINPUT_STATE input[2];
	int Button[2][16];										// コントローラ番号	1P = 0 ,2P = 1,ボタン番号 0~15
	std::map<int, std::pair<int, int>> ButtonState[2];		// <何番目のボタン,now,old>

	Vector2 Thumb[2][4];									// コントローラー番号 ,0,Lスティック、1,Rスティック
	std::map<int, std::pair<int, int>> ThumbState[2];		// now,old
};

//short					ThumbLX;						// 左スティックの横軸値( -32768 ～ 32767 )
//short					ThumbLY;						// 左スティックの縦軸値( -32768 ～ 32767 )
//short					ThumbRX;						// 右スティックの横軸値( -32768 ～ 32767 )
//short					ThumbRY;						// 右スティックの縦軸値( -32768 ～ 32767 )
