#pragma once
#include "MenuBase.h"

class ItemMenu :
	public MenuBase
{
public:
	ItemMenu() = default;
	ItemMenu(std::shared_ptr<MenuExecuter> exe, std::shared_ptr<AudioContainer> audio);
	~ItemMenu();

	void Update(void);
	void Draw(void);
private:
};

