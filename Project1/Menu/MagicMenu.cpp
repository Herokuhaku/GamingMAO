#include "MagicMenu.h"
#include "../Scene/SceneMng.h"
#include "../Object/Player.h"
#include "MenuExecuter.h"
#include "../common/Vector2.h"
#include "../Graphic/ImageMng.h"
#include "../Object/Attack/AttackDetails.h"
#include "../Manage/ButtonMng.h"
#include "../Graphic/StringAddDraw.h"
#include "../Audio/AudioContainer.h"
#include <sstream>
#include <string>
#include <cassert>

namespace
{
	// アイコンの座標
	constexpr int LENGTH = 160;
	constexpr int ORIGIN = 225;
	const Vector2Template<int> partsPosTable[static_cast<int>(COLOR::MAX) - 1] = 
	{
		{ ORIGIN, ORIGIN - LENGTH },
		{ static_cast<int>(ORIGIN - LENGTH * cos(RAD(30))), static_cast<int>(ORIGIN - LENGTH * sin(RAD(30))) },
		{ static_cast<int>(ORIGIN + LENGTH * cos(RAD(30))), static_cast<int>(ORIGIN - LENGTH * sin(RAD(30))) },
		{ ORIGIN, ORIGIN },
		{ static_cast<int>(ORIGIN - LENGTH * cos(RAD(30))), static_cast<int>(ORIGIN + LENGTH * sin(RAD(30))) },
		{ static_cast<int>(ORIGIN + LENGTH * cos(RAD(30))), static_cast<int>(ORIGIN + LENGTH * sin(RAD(30))) },
		{ ORIGIN, ORIGIN + LENGTH },
	};

	const COLOR colorTable[7] =
	{
		COLOR::BLUE, COLOR::MAGENTA, COLOR::CYAN, COLOR::WHITE, COLOR::RED, COLOR::GREEN, COLOR::YELLOW
	};
	constexpr int CIRCLE_SIZE = 450;
	constexpr int FILTER_SCREEN_SIZE = 128;

	constexpr int BOX_OFFSET_X = 330;
	constexpr int BOX_OFFSET_Y = 150;
	constexpr int BOX_SIZE_X = 250;
	constexpr int BOX_SIZE_Y = 150;

	constexpr int S_BOX_OFFSET_X = 330;
	constexpr int S_BOX_OFFSET_Y = 350;
	constexpr int S_BOX_SIZE_X = 350;
	constexpr int S_BOX_SIZE_Y = 150;

	constexpr int S_ICON_OFFSET_X = 60;
	constexpr int S_ICON_INTERVAL_X = 100;

	constexpr int ICON_SIZE = 72;
}

MagicMenu::MagicMenu(std::shared_ptr<MenuExecuter> exe, std::shared_ptr<AudioContainer> audio) :MenuBase(exe, audio)
{
	_player = std::static_pointer_cast<Player>(lpSceneMng.GetPlObj2(TIME::FTR));

	for (int i = 0; i < static_cast<int>(COLOR::MAX) - 1; i++)
	{
		_parts.emplace_back(new MenuParts("", partsPosTable[i]));
	}

	ControlInit();
	
	_update = &MagicMenu::SelectColorUpdate;
	_draw = &MagicMenu::SelectColorDraw;
	_control = &MagicMenu::CursorControlAtS_Color;

	_screen = MakeScreen(lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, true);
	_filterScreen = MakeScreen(FILTER_SCREEN_SIZE, FILTER_SCREEN_SIZE, true);
	_filterScreen = MakeScreen(FILTER_SCREEN_SIZE, FILTER_SCREEN_SIZE, true);

	lpImageMng.getImage("image/UI/AttackMenu.png", "color_ring");
} 

MagicMenu::~MagicMenu()
{
	DeleteGraph(_screen);
	DeleteGraph(_filterScreen);
	DeleteGraph(_filterTmpScreen);
}

void MagicMenu::Update(void)
{
	(this->*_update)();
}

void MagicMenu::Draw(void)
{
	int tmpScreen = GetDrawScreen();
	int tmpBlend, tmpParam;
	GetDrawBlendMode(&tmpBlend, &tmpParam);
	SetDrawScreen(_screen);
	ClsDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawMenuBox(BOX_OFFSET_X, BOX_OFFSET_Y, BOX_SIZE_X, BOX_SIZE_Y, 0x333333, 0xffffff, 220);

	(this->*_draw)();
	lpImageMng.AddBackDraw({ _screen, lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y / 2, 1.0, 0.0, LAYER::EX, 1001, DX_BLENDMODE_NOBLEND, 0 });

	SetDrawScreen(tmpScreen);
	SetDrawBlendMode(tmpBlend, tmpParam);
}

void MagicMenu::CursorControlAtS_Color(void)
{
	_controller[_cursor]();

	if (lpButtonMng.ButtonTrg(0, XINPUT_BUTTON_B))
	{
		PlaySoundMem(_audio->GetSound("select"), DX_PLAYTYPE_BACK, true);
		_update = &MagicMenu::SelectTypeUpdate;
		_draw = &MagicMenu::SelectTypeDraw;
		_selectCursor = static_cast<int>(_player->_magicSet[static_cast<int>(colorTable[_cursor])]);
	}
}

void MagicMenu::CursorControlAtS_Type(void)
{
	if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).first == 2 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second != 2)
	{
		PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
		_selectCursor--;
		if(_selectCursor < 0) _selectCursor += static_cast<int>(ATK_TYPE::MAX);
	}
	else if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).first == 1 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second != 1)
	{
		PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
		_selectCursor++;
		_selectCursor = _selectCursor % static_cast<int>(ATK_TYPE::MAX);
	}

	if (lpButtonMng.ButtonTrg(0, XINPUT_BUTTON_B))
	{
		PlaySoundMem(_audio->GetSound("select"), DX_PLAYTYPE_BACK, true);
		_player->_magicSet[static_cast<int>(colorTable[_cursor])] = static_cast<ATK_TYPE>(_selectCursor);

		_update = &MagicMenu::SelectColorUpdate;
		_draw = &MagicMenu::SelectColorDraw;
		_selectCursor = static_cast<int>(_player->_magicSet[static_cast<int>(colorTable[_cursor])]);
	}
}

void MagicMenu::SelectColorUpdate(void)
{
	CursorControlAtS_Color();
}

void MagicMenu::SelectTypeUpdate(void)
{
	CursorControlAtS_Type();
}

void MagicMenu::SelectColorDraw(void)
{
	Vector2Template<int> offset = Vector2Template<int>((lpSceneMng.ScreenSize.x - CIRCLE_SIZE) / 2 + 150, (lpSceneMng.ScreenSize.y - CIRCLE_SIZE) / 2);

	DrawGraph(offset.x, offset.y, lpImageMng.getImage("color_ring")[0], true);

	int color;
	ATK_TYPE type;
	Detail* det;
	for (int i = 0; i < static_cast<int>(COLOR::MAX) - 1; i++)
	{
		color = static_cast<int>(colorTable[i]);
		type = _player->_magicSet[color];
		det = lpAtkDetails.GetDetail(color, static_cast<int>(type)).get();

		DrawRotaGraph(_parts[i]->_pos.x + offset.x, _parts[i]->_pos.y + offset.y, 1.5, 0.0, det->_handle, true);

		if (_cursor == i)
		{
			DrawCircle(_parts[i]->_pos.x + offset.x, _parts[i]->_pos.y + offset.y, ICON_SIZE / 2, 0x000000, false, 2);
			DrawMagicDesc(color, static_cast<int>(type));
		}
	}
}

void MagicMenu::SelectTypeDraw(void)
{
	Vector2Template<int> offset = Vector2Template<int>((lpSceneMng.ScreenSize.x - CIRCLE_SIZE) / 2 + 150, (lpSceneMng.ScreenSize.y - CIRCLE_SIZE) / 2);

	DrawGraph(offset.x, offset.y, lpImageMng.getImage("color_ring")[0], true);

	int color;
	ATK_TYPE type;
	Detail* det;
	for (int i = 0; i < static_cast<int>(COLOR::MAX) - 1; i++)
	{
		color = static_cast<int>(colorTable[i]);
		type = _player->_magicSet[color];
		det = lpAtkDetails.GetDetail(color, static_cast<int>(type)).get();

		if (_cursor == i)
		{
			SetDrawScreen(_filterScreen);
			ClsDrawScreen();
			SetDrawScreen(_filterTmpScreen);
			ClsDrawScreen();
			DrawRotaGraph(FILTER_SCREEN_SIZE / 2, FILTER_SCREEN_SIZE / 2, 1.5, 0.0, det->_handle, true);
			GraphFilterBlt(_filterTmpScreen, _filterScreen, DX_GRAPH_FILTER_GAUSS, 8, 600);

			SetDrawScreen(_screen);
			DrawRotaGraph(_parts[i]->_pos.x + offset.x, _parts[i]->_pos.y + offset.y, 1.05, 0.0, _filterScreen, true);
		}

		DrawRotaGraph(_parts[i]->_pos.x + offset.x, _parts[i]->_pos.y + offset.y, 1.5, 0.0, det->_handle, true);
	}

	DrawMenuBox(S_BOX_OFFSET_X, S_BOX_OFFSET_Y, S_BOX_SIZE_X, S_BOX_SIZE_Y, 0x333333, 0xffffff, 220);

	int posX = S_BOX_OFFSET_X + S_ICON_OFFSET_X;
	for (int i = 0; i < static_cast<int>(ATK_TYPE::MAX); i++)
	{
		det = lpAtkDetails.GetDetail(static_cast<int>(colorTable[_cursor]), i).get();

		if (_selectCursor == i)
		{
			SetDrawScreen(_filterScreen);
			ClsDrawScreen();
			SetDrawScreen(_filterTmpScreen);
			ClsDrawScreen();
			DrawRotaGraph(FILTER_SCREEN_SIZE / 2, FILTER_SCREEN_SIZE / 2, 1.5, 0.0, det->_handle, true);
			GraphFilterBlt(_filterTmpScreen, _filterScreen, DX_GRAPH_FILTER_GAUSS, 8, 600);

			SetDrawScreen(_screen);
			DrawRotaGraph(posX, S_BOX_OFFSET_Y + S_BOX_SIZE_Y / 2, 1.05, 0.0, _filterScreen, true);

			DrawMagicDesc(static_cast<int>(colorTable[_cursor]), i);
		}

		DrawRotaGraph(posX, S_BOX_OFFSET_Y + S_BOX_SIZE_Y / 2, 1.5, 0.0, det->_handle, true);

		posX += S_ICON_INTERVAL_X;
	}
}

void MagicMenu::DrawMagicDesc(int color, int type)
{
	assert(color >= 0 || color < static_cast<int>(COLOR::MAX));
	assert(type >= 0 || type < ATTACK_TYPE_MAX);

	Detail* det = lpAtkDetails.GetDetail(color, type).get();

	DrawRotaGraph(BOX_OFFSET_X + 50, BOX_OFFSET_Y + 90, 1.5, 0.0, det->_handle, true);

	std::stringstream str;
	str << det->_name;
	lpStrAdd.AddStringDraw(str.str().c_str(), "SQUARE_SMALL", BOX_OFFSET_X + 20, BOX_OFFSET_Y + 20, 0xffffff, DRAW_TO_LEFT);
	str.str("");
	str.clear(std::stringstream::goodbit);
	
	str << "MP:" << det->_magicPoint;
	lpStrAdd.AddStringDraw(str.str().c_str(), "SQUARE_SMALL", BOX_OFFSET_X + 100, BOX_OFFSET_Y + 70, 0xffffff, DRAW_TO_LEFT);
	str.str("");
	str.clear(std::stringstream::goodbit);

	//std::wstringstream wstr;
	//wstr << " " << det->_desc;
	//size_t size = str.str().length();
	//for (int i = 0; i * 10 < static_cast<int>(size); i++)
	//{
	//	lpStrAdd.AddStringDraw(str.str().substr(i * 10, min(10, size - i * 10)).c_str(), "SQUARE_SMALL", BOX_OFFSET_X + 10, BOX_OFFSET_Y + 150 + i * 30, 0xffffff, DRAW_TO_LEFT);
	//}
}

void MagicMenu::ControlInit(void)
{
	_controller[0] = [this]()
	{
		if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second != 0 || lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second != 0)
		{
			return;
		}

		if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).first == 2 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second != 2)
		{
			PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
			_cursor = 1;
		}
		else if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).first == 1 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second != 1)
		{
			PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
			_cursor = 2;
		}
		else if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).first == 1 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second != 1)
		{
			PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
			_cursor = 3;
		}
	};

	_controller[1] = [this]()
	{
		if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second != 0 || lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second != 0)
		{
			return;
		}

		if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).first == 1 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second != 1)
		{
			PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
			if (!StickYIsPositive())
			{
				_cursor = 0;
			}
			else
			{
				_cursor = 3;
			}
		}
		else if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).first == 2 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second != 2)
		{
			PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
			_cursor = 0;
		}
		else if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).first == 1 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second != 1)
		{
			PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
			_cursor = 4;
		}
	};

	_controller[2] = [this]()
	{
		if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second != 0 || lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second != 0)
		{
			return;
		}

		if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).first == 2 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second != 2)
		{
			PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
			if (!StickYIsPositive())
			{
				_cursor = 0;
			}
			else
			{
				_cursor = 3;
			}
		}
		else if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).first == 2 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second != 2)
		{
			PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
			_cursor = 0;
		}
		else if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).first == 1 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second != 1)
		{
			PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
			_cursor = 5;
		}
	};

	_controller[3] = [this]()
	{
		if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second != 0 || lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second != 0)
		{
			return;
		}

		if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).first == 2 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second != 2)
		{
			PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
			if (!StickYIsPositive())
			{
				_cursor = 1;
			}
			else
			{
				_cursor = 4;
			}
		}
		else if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).first == 1 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second != 1)
		{
			PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
			if (!StickYIsPositive())
			{
				_cursor = 2;
			}
			else
			{
				_cursor = 5;
			}
		}
		else if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).first == 2 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second != 2)
		{
			PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
			_cursor = 0;
		}
		else if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).first == 1 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second != 1)
		{
			PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
			_cursor = 6;
		}
	};

	_controller[4] = [this]()
	{
		if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second != 0 || lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second != 0)
		{
			return;
		}

		if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).first == 1 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second != 1)
		{
			PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
			if (!StickYIsPositive())
			{
				_cursor = 3;
			}
			else
			{
				_cursor = 6;
			}
		}
		else if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).first == 2 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second != 2)
		{
			PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
			_cursor = 1;
		}
		else if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).first == 1 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second != 1)
		{
			PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
			_cursor = 6;
		}
	};

	_controller[5] = [this]()
	{
		if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second != 0 || lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second != 0)
		{
			return;
		}

		if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).first == 2 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second != 2)
		{
			PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
			if (!StickYIsPositive())
			{
				_cursor = 3;
			}
			else
			{
				_cursor = 6;
			}
		}
		else if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).first == 2 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second != 2)
		{
			PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
			_cursor = 2;
		}
		else if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).first == 1 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second != 1)
		{
			PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
			_cursor = 6;
		}
	};

	_controller[6] = [this]()
	{
		if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second != 0 || lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second != 0)
		{
			return;
		}

		if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).first == 2 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second != 2)
		{
			PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
			_cursor = 4;
		}
		else if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).first == 1 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_X).second != 1)
		{
			PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
			_cursor = 5;
		}
		else if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).first == 2 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second != 1)
		{
			PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
			_cursor = 3;
		}
	};
}

bool MagicMenu::StickYIsPositive(void)
{
	short stx, sty;
	lpButtonMng.GetThumb(THUMB_LEFT, stx, sty);
	return sty >= 0;
}
