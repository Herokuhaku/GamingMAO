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
	/// •¶š‚Ì•`‰æ
	/// </summary>
	/// <param name="color">F</param>
	void Draw(int color = 0xffffff);

	/// <summary>
	/// ‰æ‘œ‚ğg‚Á‚Ä•`‰æ
	/// </summary>
	/// <param="handle">ƒnƒ“ƒhƒ‹</param>
	/// <param name="exRate">Šg‘å—¦</param>
	/// <param name="angle">Šp“x</param>
	void DrawWithHandle(int handle, double exRate, double angle);
};

