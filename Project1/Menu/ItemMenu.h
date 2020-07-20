#pragma once
#include "MenuBase.h"

class ItemMenu :
	public MenuBase
{
public:
	ItemMenu() = delete;
	ItemMenu(std::shared_ptr<MenuExecuter> exe);
	~ItemMenu();

	void Update(void);
	void Draw(void);
private:
};

