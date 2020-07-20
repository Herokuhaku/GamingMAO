#pragma once
#include "MenuBase.h"
#include <memory>

class SelectMenu :
	public MenuBase
{
public:
	SelectMenu() = delete;
	SelectMenu(int cursor, std::shared_ptr<MenuExecuter> exe);
	~SelectMenu();

	void Update(void);
	void Draw(void);
private:
	void CursorControl(void);
};

