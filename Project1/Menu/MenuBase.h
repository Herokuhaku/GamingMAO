#pragma once
#include <vector>
#include <memory>
#include "MenuParts.h"

class MenuExecuter;

class MenuBase
{
public:
	MenuBase() = delete;
	MenuBase(std::shared_ptr<MenuExecuter> exe);
	virtual ~MenuBase();

	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
protected:
	std::vector<std::unique_ptr<MenuParts>> _parts;
	int _cursor = 0;

	std::shared_ptr<MenuExecuter> _executer;
};

