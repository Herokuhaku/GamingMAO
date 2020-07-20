#include "MenuExecuter.h"
#include "SelectMenu.h"
#include "../Graphic/ImageMng.h"
#include "../Manage/ButtonMng.h"
#include "../Scene/GameScene.h"

bool MenuExecuter::_active;

namespace
{
	Vector2Template<int> scSize;
}

MenuExecuter::MenuExecuter(GameScene* gs) : _gameScene(gs)
{
	_pageChanger = []() {};
	lpImageMng.getImage("image/ƒƒjƒ…[.png", "Menu");
	GetWindowSize(&scSize.x, &scSize.y);
	scSize = scSize / 2;

	_active = false;
}

void MenuExecuter::Update(void)
{
	if (!Control())
	{
		return;
	}
	_currentMenu->Update();
}

void MenuExecuter::Draw(void)
{
	if (!_active)
	{
		return;
	}
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Menu")[0], scSize.x,scSize.y, 1.0, 0.0, LAYER::EX, 1000, DX_BLENDMODE_NOBLEND, 0 });
	_currentMenu->Draw();
	_pageChanger();
	_pageChanger = []() {};
}

void MenuExecuter::ChangePage(MenuBase* menu)
{
	_pageChanger = [menu, this]()
	{ 
		_currentMenu.reset(menu); 
	};
}

bool MenuExecuter::IsActive(void)
{
	return _active;
}

std::shared_ptr<MenuExecuter>& MenuExecuter::GetThis(void)
{
	return _gameScene->GetMenuExecuter();
}

bool MenuExecuter::Control(void)
{
	if (lpButtonMng.ButtonTrg(0, XINPUT_BUTTON_BACK))
	{
		if (_active)
		{
			_active = false;
		}
		else
		{
			_active = true;
			_currentMenu.reset(new SelectMenu(0, _gameScene->GetMenuExecuter()));
		}
	}
	return _active;
}

