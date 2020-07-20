#pragma once
#include <string>
#include <functional>
#include "../common/Vector2.h"


struct MenuParts
{
	std::string _text;
	Vector2Template<int> _pos;
	std::function<void(void)> _func;

	MenuParts(const char* text, const Vector2Template<int>& pos, std::function<void(void)> func) :_text(text), _pos(pos), _func(func) {};

	void Draw(int color = 0xffffff);
};

