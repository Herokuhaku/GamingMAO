#include "StringAddDraw.h"

StringAddDraw* StringAddDraw::sInstance = nullptr;

StringAddDraw::StringAddDraw()
{
	_strScreen = MakeScreen(lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, true);
	_fontHandle = CreateFontToHandle("Terminal", 40, 1, DX_FONTTYPE_NORMAL);

	ClearScreen();
}

StringAddDraw::~StringAddDraw()
{

}

int StringAddDraw::AddDraw(const TCHAR * string, int pos_x, int pos_y, int color, int draw_type)
{
	int length = strlen(string);
	int width = GetDrawStringWidthToHandle(string, length, _fontHandle);
	
	int tmpScreen = GetDrawScreen();
	SetDrawScreen(_strScreen);

	switch (draw_type)
	{
	case DRAW_TO_LEFT:
		DrawStringToHandle(pos_x, pos_y, string, color, _fontHandle);
		break;
	case DRAW_TO_CENTER:
		DrawStringToHandle(pos_x - width / 2, pos_y, string, color, _fontHandle);
		break;
	case DRAW_TO_RIGHT:
		DrawStringToHandle(pos_x - width, pos_y, string, color, _fontHandle);
		break;
	default:
		break;
	}

	SetDrawScreen(tmpScreen);
	return width;
}

void StringAddDraw::Draw()
{
	lpImageMng.AddBackDraw({ _strScreen, lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y / 2, 1.0, 0.0, LAYER::EX, 100000, DX_BLENDMODE_NOBLEND, 0 });
}

void StringAddDraw::ClearScreen(void)
{
	int tmpScreen = GetDrawScreen();
	SetDrawScreen(_strScreen);
	ClsDrawScreen();
	SetDrawScreen(tmpScreen);
}

int StringAddDraw::GetFont(void)
{
	return _fontHandle;
}
