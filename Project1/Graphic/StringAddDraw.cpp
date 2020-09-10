#include "StringAddDraw.h"
#include <cassert>
#include "../Graphic/ImageMng.h"
#include "../Scene/SceneMng.h"

StringAddDraw* StringAddDraw::sInstance = nullptr;

StringAddDraw::StringAddDraw()
{
	_strScreen = MakeScreen(lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, true);

	_fontHandle.try_emplace("TITLE", CreateFontToHandle("Terminal", 25, 1, DX_FONTTYPE_NORMAL));
	_fontHandle.try_emplace("SQUARE_BIG", CreateFontToHandle("Terminal", 40, 1, DX_FONTTYPE_NORMAL));
	_fontHandle.try_emplace("SQUARE_SMALL", CreateFontToHandle("Terminal", 30, 1, DX_FONTTYPE_NORMAL));

	ClearScreen();
}

StringAddDraw::~StringAddDraw()
{

}

int StringAddDraw::AddStringDraw(const char* string, const std::string& font_key, int pos_x, int pos_y, int color, int draw_type, int BlendMode, int param)
{
	if (_fontHandle.find(font_key) == _fontHandle.end())
	{
		assert(false);
		return -1;
	}
	int length = static_cast<int>(strlen(string));
	int width = GetDrawStringWidthToHandle(string, length, _fontHandle[font_key]);
	
	int tmpScreen, tb, tp;
	lpImageMng.GetCurrentScreen(&tmpScreen, &tb, &tp);
	SetDrawScreen(_strScreen);
	SetDrawBlendMode(BlendMode, param);

	switch (draw_type)
	{
	case DRAW_TO_LEFT:
		DrawStringToHandle(pos_x, pos_y, string, color, _fontHandle[font_key]);
		break;
	case DRAW_TO_CENTER:
		DrawStringToHandle(pos_x - width / 2, pos_y, string, color, _fontHandle[font_key]);
		break;
	case DRAW_TO_RIGHT:
		DrawStringToHandle(pos_x - width, pos_y, string, color, _fontHandle[font_key]);
		break;
	default:
		break;
	}

	SetDrawScreen(tmpScreen);
	SetDrawBlendMode(tb, tp);
	return width;
}

void StringAddDraw::Draw()
{
	lpImageMng.AddBackDraw({ _strScreen, lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y / 2, 1.0, 0.0, LAYER::EX, 100000, DX_BLENDMODE_NOBLEND, 0, true });
}

void StringAddDraw::ClearScreen(void)
{
	int tmpScreen = GetDrawScreen();
	SetDrawScreen(_strScreen);
	ClsDrawScreen();
	SetDrawScreen(tmpScreen);
}

int StringAddDraw::GetFont(const std::string& font_key)
{
	assert(_fontHandle.find(font_key) != _fontHandle.end());
	return _fontHandle[font_key];
}
