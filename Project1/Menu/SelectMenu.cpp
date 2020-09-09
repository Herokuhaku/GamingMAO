#include "SelectMenu.h"
#include "../Graphic/ImageMng.h"
#include "../Manage/ButtonMng.h"
#include "../Manage/TimeMng.h"
#include "../common/Vector2.h"
#include "MenuExecuter.h"
#include "ItemMenu.h"
#include "MagicMenu.h"
#include "../Audio/AudioContainer.h"
#include "../Scene/SceneMng.h"
#include "../Scene/GameScene.h"


namespace
{
	constexpr int SELECT_CURSOR_RANGE = 3;

	constexpr int PARTS_POS_X = 400;
	constexpr int PARTS_OFFSET_Y = 200;
	constexpr int PARTS_SPACE = 100;
}

SelectMenu::SelectMenu(int cursor, std::shared_ptr<MenuExecuter> exe, std::shared_ptr<AudioContainer> audio) : MenuBase(exe, audio)
{
	if (cursor >= SELECT_CURSOR_RANGE || cursor < 0)
	{
		cursor = 0;
	}
	_cursor = cursor;

	int partsPosY = PARTS_OFFSET_Y;

	lpImageMng.getImage("image/Title/cursor.png", "cursor");

	if (lpTimeMng.getTime() == TIME::NOW)
	{
		_parts.emplace_back(new MenuParts("合成", Vector2Template<int>(PARTS_POS_X, partsPosY), [this]() { _executer->ChangePage(new ItemMenu(_executer, _audio)); }));
		partsPosY += PARTS_SPACE;
	}
	else
	{
		_parts.emplace_back(new MenuParts("魔法", Vector2Template<int>(PARTS_POS_X, partsPosY), [this]() { _executer->ChangePage(new MagicMenu(_executer, _audio)); }));
		partsPosY += PARTS_SPACE;
	}
	_parts.emplace_back(new MenuParts("リセット", Vector2Template<int>(PARTS_POS_X, partsPosY), []() { lpSceneMng.ChangeScene(new GameScene()); }));
	partsPosY += PARTS_SPACE;
	_parts.emplace_back(new MenuParts("終了", Vector2Template<int>(PARTS_POS_X, partsPosY), []() { lpSceneMng.Quit(); }));
}

SelectMenu::~SelectMenu()
{
}

void SelectMenu::Update(void)
{
	CursorControl();
}

void SelectMenu::Draw(void)
{
	int color;
	for (size_t i = 0; i < _parts.size(); i++)
	{
		color = 0xffffff;
		if (i == _cursor)
		{
			color = 0xff4444;
			lpImageMng.AddBackDraw({ lpImageMng.getImage("cursor")[0], _parts[i]->_pos.x - 40, _parts[i]->_pos.y + 25, 1.0, 0.0, LAYER::EX, 1001, DX_BLENDMODE_NOBLEND, 0, true });
		}
		_parts[i]->Draw(color);
	}
}

void SelectMenu::CursorControl(void)
{
	if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).first == 2 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second != 2)
	{
		PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
		_cursor = (_parts.size() + _cursor - 1) % _parts.size();
	}
	if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).first == 1 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second != 1)
	{
		PlaySoundMem(_audio->GetSound("move"), DX_PLAYTYPE_BACK, true);
		_cursor = (_cursor + 1) % _parts.size();
	}

	if (lpButtonMng.ButtonTrg(0, XINPUT_BUTTON_B))
	{
		PlaySoundMem(_audio->GetSound("select"), DX_PLAYTYPE_BACK, true);
		_parts[_cursor]->_func();
	}
}
