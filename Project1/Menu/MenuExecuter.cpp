#include "MenuExecuter.h"
#include "SelectMenu.h"
#include "../Graphic/ImageMng.h"
#include "../Manage/ButtonMng.h"
#include "../Scene/GameScene.h"
#include "../Audio/AudioContainer.h"
#include "../Manage/AttackUI.h"
#include "../Object/Player.h"
#include "../Object/Attack/white/StopTime.h"

bool MenuExecuter::_active;

namespace
{
	Vector2Template<int> scSize;
}

MenuExecuter::MenuExecuter(GameScene* gs) : _gameScene(gs)
{
	_pageChanger = []() {};
	lpImageMng.getImage("image/ÉÅÉjÉÖÅ[.png", "Menu");
	GetWindowSize(&scSize.x, &scSize.y);
	scSize = scSize / 2;

	_audio = std::make_shared<AudioContainer>();
	_audio->LoadSound("sound/system/cursor_move.wav", "move", 5);
	_audio->LoadSound("sound/system/cursor_select.wav", "select", 3);
	_audio->LoadSound("sound/system/cancel.wav", "cancel", 3);
	_audio->ChangeVolume("move", 150);
	_audio->ChangeVolume("select", 180);
	_audio->ChangeVolume("cancel", 150);

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
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Menu")[0], scSize.x,scSize.y, 1.0, 0.0, LAYER::EX, 30, DX_BLENDMODE_NOBLEND, 0, true });
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
	if (std::dynamic_pointer_cast<Player>(lpSceneMng.GetPlObj2(TIME::FTR))->GetStopTime()->IsCountdowned())
	{
		_active = false;
		lpAttackUI.Active(true);
	}

	if (lpButtonMng.ButtonTrg(0, XINPUT_BUTTON_BACK))
	{
		if (_active)
		{
			PlaySoundMem(_audio->GetSound("cancel"), DX_PLAYTYPE_BACK, true);
			_active = false;
			lpAttackUI.Active(true);
		}
		else
		{
			PlaySoundMem(_audio->GetSound("select"), DX_PLAYTYPE_BACK, true);
			_active = true;
			_currentMenu.reset(new SelectMenu(0, _gameScene->GetMenuExecuter(), _audio));
			lpAttackUI.Active(false);
		}
	}
	return _active;
}

