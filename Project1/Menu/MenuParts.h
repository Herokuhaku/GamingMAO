#pragma once
#include <string>
#include <functional>
#include "../common/Vector2.h"


struct MenuParts
{
	std::string _text;
	Vector2Template<int> _pos;
	std::function<void(void)> _func;

	MenuParts(const char* text, const Vector2Template<int>& pos, std::function<void(void)> func = []() {}) :_text(text), _pos(pos), _func(func) {};

	/// <summary>
	/// 文字の描画
	/// </summary>
	/// <param name="color">色</param>
	void Draw(int color = 0xffffff);

	/// <summary>
	/// 画像を使って描画
	/// </summary>
	/// <param="handle">ハンドル</param>
	/// <param name="exRate">拡大率</param>
	/// <param name="angle">角度</param>
	void DrawWithHandle(int handle, double exRate, double angle);
};

