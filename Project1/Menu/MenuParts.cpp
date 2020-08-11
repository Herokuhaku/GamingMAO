#include "MenuParts.h"
#include "../Graphic/StringAddDraw.h"
#include <cassert>
#include <DxLib.h>

void MenuParts::Draw(int color)
{
	lpStrAdd.AddStringDraw(_text.c_str(), "TITLE", _pos.x, _pos.y, color, DRAW_TO_LEFT);
}

void MenuParts::DrawWithHandle(int handle, double exRate, double angle)
{
	assert(handle != -1);
	DrawRotaGraph(_pos.x, _pos.y, exRate, angle, handle, true);
}
