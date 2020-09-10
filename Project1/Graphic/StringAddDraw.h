#pragma once
#include <string>
#include <unordered_map>
#include <DxLib.h>

#define lpStrAdd StringAddDraw::GetInstance()

#define DRAW_TO_LEFT	0
#define DRAW_TO_CENTER	1
#define DRAW_TO_RIGHT	2

class StringAddDraw
{
public:
	static StringAddDraw& GetInstance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new StringAddDraw();
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

	// string : 描画する文字列
	// font_key:フォント識別キー
	// pos_x : X座標	pos_y : 左上y座標
	// color : 描画色
	// draw_type : x座標をどこに合わせるか(左　中央　右)
	// 返り値 : 文字列の横サイズ
	int AddStringDraw(const char* string, const std::string& font_key, int pos_x, int pos_y, int color, int draw_type, int blendMode = DX_BLENDMODE_NOBLEND, int param = 0);

	void Draw(void);
	void ClearScreen(void);
	
	// font_keyに対応するキーを返す
	int GetFont(const std::string& font_key);				

private:
	static StringAddDraw* sInstance;

	int _strScreen;

	std::unordered_map<std::string, int> _fontHandle;		// フォントのハンドル

	StringAddDraw();
	StringAddDraw(const StringAddDraw&) = delete;
	StringAddDraw operator+(const StringAddDraw&) = delete;
	~StringAddDraw();
};

