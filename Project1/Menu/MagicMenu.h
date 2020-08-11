#pragma once
#include "MenuBase.h"
#include <array>

class Player;

class MagicMenu :
	public MenuBase
{
public:
	MagicMenu() = default;
	MagicMenu(std::shared_ptr<MenuExecuter> exe, std::shared_ptr<AudioContainer> audio);
	~MagicMenu();

	void Update(void);
	void Draw(void);
private:
	void CursorControlAtS_Color(void);
	void CursorControlAtS_Type(void);

	void (MagicMenu::*_control)(void);

	std::shared_ptr<Player> _player;
	int _screen;
	int _filterScreen;
	int _filterTmpScreen;

	std::array<std::function<void(void)>, 7> _controller;
	void ControlInit(void);
	bool StickYIsPositive(void);

	void SelectColorUpdate(void);
	void SelectTypeUpdate(void);

	void (MagicMenu::*_update)(void);

	void SelectColorDraw(void);
	void SelectTypeDraw(void);

	void (MagicMenu::*_draw)(void);

	void DrawMagicDesc(int color, int type);

	int _selectCursor;
};

