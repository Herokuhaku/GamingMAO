#include "MenuParts.h"
#include "../Graphic/StringAddDraw.h"

void MenuParts::Draw(int color)
{
	lpStrAdd.AddStringDraw(_text.c_str(), "TITLE", _pos.x, _pos.y, color, DRAW_TO_LEFT);
}
