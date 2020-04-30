#include "Menu.h"
#include "Scene/SceneMng.h"
#include "ButtonMng.h"

Menu* Menu::sInstance = nullptr;

Menu::Menu()
{
	type = &Menu::SELECT;
	start = false;
	push_select = false;

	lpImageMng.getImage("image/メニュー.png", "Menu");
}

Menu::~Menu()
{
}

bool Menu::Update(void)
{
	// メニュー開始
	if (start == false)
	{
		start = true;
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_BACK, 1, 1);
	}

	// メニュー画面表示
	lpImageMng.AddDraw({ lpImageMng.getImage("Menu")[0],lpSceneMng.GetcPos().x+200,lpSceneMng.GetcPos().y-200,0.0,LAYER::EX,100 });
	
	// メニュー画面 or 合成画面

	(this->*type)();


	// メニュー終了
	if(lpButtonMng.Buttonf(0, XINPUT_BUTTON_BACK).first == 1 &&
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_BACK).second == 0)
	{
		start = false;
		return false;
	}
	
	return true;
}


void Menu::SELECT(void)
{
	if (CheckHitKey(KEY_INPUT_UP))
	{
		_select--;
	}

	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		_select++;
	}
	

	if (_select > static_cast<int>(MENU_TYPE::ITEMMINUS))
	{
		_select = 0;
	}
	else if (_select < 0)
	{
		_select = static_cast<int>(MENU_TYPE::ITEMMINUS);
	}

	if (lpButtonMng.Buttonf(0, XINPUT_BUTTON_A).first == 0 &&
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_A).second == 1)
	{
		_type = static_cast<MENU_TYPE>(_select);
		switch (_type)
		{
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
	
}

void Menu::ItemMup(void)
{

}
