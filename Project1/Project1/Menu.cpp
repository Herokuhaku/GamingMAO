#include "Menu.h"
#include "Scene/SceneMng.h"
#include "ButtonMng.h"

Menu* Menu::sInstance = nullptr;

Menu::Menu()
{
	type = &Menu::SELECT;
	_start = false;
	push_select = false;
	_select = 0;

	lpImageMng.getImage("image/メニュー.png", "Menu");
	lpImageMng.getImage("image/Space.png", "Space");
}

Menu::~Menu()
{
}

bool Menu::Update(void)
{
	// メニュー開始
	if (_start == false)
	{
		_start = true;
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_BACK, 1, 1);
	}
	Start(&_start);
	// メニュー画面表示
//	lpImageMng.AddDraw({ lpImageMng.getImage("Menu")[0],lpSceneMng.GetcPos().x+200,lpSceneMng.GetcPos().y-200,0.0,LAYER::EX,100 });
	
	// メニュー画面 or 合成画面

	(this->*type)();


	// メニュー終了
	if(lpButtonMng.Buttonf(0, XINPUT_BUTTON_BACK).first == 1 &&
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_BACK).second == 0)
	{
		_start = false;
		return false;
	}
	
	return true;
}


void Menu::SELECT(void)
{
	if (lpButtonMng.Buttonf(0,XINPUT_BUTTON_DPAD_UP).first == 0&&
		lpButtonMng.Buttonf(0,XINPUT_BUTTON_DPAD_UP).second == 1)
	{
		_select--;
		if (_select < 0)
		{
			_select = static_cast<int>(MENU_TYPE::ITEMMINUS);
		}
	}
	
	if (lpButtonMng.Buttonf(0, XINPUT_BUTTON_DPAD_DOWN).first == 0 &&
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_DPAD_DOWN).second == 1)
	{
		_select++;
		if (_select > static_cast<int>(MENU_TYPE::ITEMMINUS))
		{
			_select = 0;
		}
	}
	//lpImageMng.AddDraw({ lpImageMng.getImage("矢印")[0],lpSceneMng.GetcPos().x,lpSceneMng.GetcPos().y,0.0,LAYER::EX,50 });
	lpImageMng.AddDraw({ lpImageMng.getImage("Menu")[0],lpSceneMng.GetcPos().x + 200,lpSceneMng.GetcPos().y,0.0,LAYER::EX,100 });
	

	if (lpButtonMng.Buttonf(0, XINPUT_BUTTON_B).first == 1 &&
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_B).second == 0)
	{
		_type = static_cast<MENU_TYPE>(_select);
		switch (_type)
		{

		case MENU_TYPE::SELECT:
			break;
		case MENU_TYPE::ITEMPLUS:
			type = &Menu::ItemPup;
			break;
		case MENU_TYPE::ITEMMINUS:
			type = &Menu::ItemMup;
			break;
		default:
			break;
		}
	}

}

void Menu::ItemPup(void)
{
	//Start(&push_select);

	lpImageMng.AddDraw({ lpImageMng.getImage("Menu")[0],lpSceneMng.GetcPos().x + 200,lpSceneMng.GetcPos().y,0.0,LAYER::EX,100 });
	lpImageMng.AddDraw({ lpImageMng.getImage("Space")[0],lpSceneMng.GetcPos().x-200,lpSceneMng.GetcPos().y-100,0.0,LAYER::EX,150 });

	if (lpButtonMng.Buttonf(0, XINPUT_BUTTON_A).first == 1 &&
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_A).second == 0)
	{
		type = &Menu::SELECT;
	}

	//End(&push_select);
}

void Menu::ItemMup(void)
{
	
}

void Menu::Start(bool *a)
{
	if (*a == false)
	{
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_A, 1, 1);
		*a = true;
	}
}

void Menu::End(bool *a)
{
	if (lpButtonMng.Buttonf(0, XINPUT_BUTTON_A).first == 1 &&
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_A).second == 0)
	{
		*a = false;
	}
}
