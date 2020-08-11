#pragma once
#include <vector>
#include <memory>
#include "MenuParts.h"

class MenuExecuter;
struct AudioContainer;

class MenuBase
{
public:
	MenuBase() = default;
	MenuBase(std::shared_ptr<MenuExecuter> exe, std::shared_ptr<AudioContainer> audio);
	virtual ~MenuBase();

	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
protected:
	std::vector<std::unique_ptr<MenuParts>> _parts;
	int _cursor = 0;

	std::shared_ptr<MenuExecuter> _executer;
	std::shared_ptr<AudioContainer> _audio;

	void DrawMenuBox(int posX, int posY, int sizeX, int sizeY, unsigned int boxColor, unsigned int edgeColor, int transParam);
};

