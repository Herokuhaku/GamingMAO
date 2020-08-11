#pragma once
#include "MenuBase.h"
#include <memory>

class SelectMenu :
	public MenuBase
{
public:
	SelectMenu() = default;
	SelectMenu(int cursor, std::shared_ptr<MenuExecuter> exe, std::shared_ptr<AudioContainer> audio);
	~SelectMenu();

	void Update(void);
	void Draw(void);
private:
	void CursorControl(void);
};

