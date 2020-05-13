#include "Menu.h"
#include "../Scene/SceneMng.h"
#include "ButtonMng.h"

Menu* Menu::sInstance = nullptr;

Menu::Menu()
{
	type = &Menu::SELECT;
	_start = false;
	push_select = false;
	_select = 0;
	_offpush.y = 150;
	_offpush.x = 200;
	MixFlag = false;

	lpImageMng.getImage("image/ÉÅÉjÉÖÅ[.png", "Menu");
	lpImageMng.getImage("image/Space.png", "Space");
	lpImageMng.getImage("image/arrow.png", "Arrow");
	lpImageMng.getImage("image/çáê¨.png", "Mix");
}

Menu::~Menu()
{
}

bool Menu::Update(void)
{
	// ÉÅÉjÉÖÅ[äJén
	if (_start == false)
	{
		_start = true;
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_BACK, 1, 1);
	}
	_cpos = lpSceneMng.GetcPos();

	(this->*type)();	// select,mix,


	// ÉÅÉjÉÖÅ[èIóπ
	if(lpButtonMng.Buttonf(0, XINPUT_BUTTON_BACK).first == 1 &&
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_BACK).second == 0)
	{
		type = &Menu::SELECT;
		MixFlag = false;
		_select = 0;
		_start = false;
		return false;
	}
	
	return true;
}

bool Menu::GetMixFlag(void)
{
	return MixFlag;
}


void Menu::SELECT(void)
{
	if (lpButtonMng.Buttonf(0,XINPUT_BUTTON_DPAD_UP).first == 1&&
		lpButtonMng.Buttonf(0,XINPUT_BUTTON_DPAD_UP).second == 0)
	{
		_select--;
		if (_select < 0)
		{
			_select = static_cast<int>(MENU_TYPE::ITEMMINUS);
		}
	}
	
	if (lpButtonMng.Buttonf(0, XINPUT_BUTTON_DPAD_DOWN).first == 1 &&
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_DPAD_DOWN).second == 0)
	{
		_select++;
		if (_select > static_cast<int>(MENU_TYPE::ITEMMINUS))
		{
			_select = 0;
		}
	}
	SelectDraw();
	// SELECTÇ©ÇÁÇÃêÿÇËë÷Ç¶
	if (lpButtonMng.Buttonf(0, XINPUT_BUTTON_B).first == 1 &&
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_B).second == 0)
	{
		_type = static_cast<MENU_TYPE>(_select);
		_select = 0;
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
	if (!MixFlag)
	{
		// ñÓàÛÇâEÇ…à⁄ìÆÇ≥ÇπÇÈ
		if (lpButtonMng.Buttonf(0, XINPUT_BUTTON_DPAD_RIGHT).first == 1 &&
			lpButtonMng.Buttonf(0, XINPUT_BUTTON_DPAD_RIGHT).second == 0)
		{
			_select++;
			if (_select > 2)
			{
				_select = 0;
			}
		}
		//Å@ñÓàÛÇç∂Ç…à⁄ìÆÇ≥ÇπÇÈ
		if (lpButtonMng.Buttonf(0, XINPUT_BUTTON_DPAD_LEFT).first == 1 &&
			lpButtonMng.Buttonf(0, XINPUT_BUTTON_DPAD_LEFT).second == 0)
		{
			_select--;
			if (_select < 0)
			{
				_select = 2;
			}
		}

		MixDraw();

		// ÉAÉCÉeÉÄÇëIë
		if (lpButtonMng.Buttonf(0, XINPUT_BUTTON_B).first == 1 &&
			lpButtonMng.Buttonf(0, XINPUT_BUTTON_B).second == 0)
		{
			lpButtonMng.Buttonf(0, XINPUT_BUTTON_B, 1, 1);
			_selectNo = static_cast<SELECT_ITEM>(_select);
			MixFlag = true;
		}
		// Select Ç…ñﬂÇÈ
		if (lpButtonMng.Buttonf(0, XINPUT_BUTTON_A).first == 1 &&
			lpButtonMng.Buttonf(0, XINPUT_BUTTON_A).second == 0)
		{
			type = &Menu::SELECT;
		}
	}
	else 
	{
		switch (_selectNo)
		{
		case SELECT_ITEM::ITEM1:
			Item1();
			break;
		case SELECT_ITEM::ITEM2:
			Item2();
			break;
		case SELECT_ITEM::ITEM3:
			Item3();
			break;
		default:
			break;
		}
	}
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

void Menu::SelectDraw(void)
{
	// ïóòCï~ÇÃï`âÊ
	lpImageMng.AddDraw({ lpImageMng.getImage("Menu")[0],_cpos.x + 200,_cpos.y,0.0,LAYER::EX,100 });

	// ñÓàÛÇÃï`âÊ
	lpImageMng.AddDraw({ lpImageMng.getImage("Arrow")[0],_cpos.x - 300,_cpos.y - 150 + (100 * _select),0,LAYER::EX,101 });

	// çáê¨ÇÃï∂éöï`âÊ
	lpImageMng.AddDraw({ lpImageMng.getImage("Mix")[0],_cpos.x - 200,_cpos.y - 50,0.0,LAYER::EX,101 });
}

void Menu::MixDraw(void)
{
	// ïóòCï~ÇÃï`âÊ
	lpImageMng.AddDraw({ lpImageMng.getImage("Menu")[0],_cpos.x + 200,_cpos.y,0.0,LAYER::EX,100 });

	// ÉAÉCÉeÉÄëIë
	for (int x = 0;x < 3;x++)
	{
		lpImageMng.AddDraw({ lpImageMng.getImage("Space")[0],_cpos.x - 200 + (_offpush.x * x),_cpos.y - _offpush.y,0.0,LAYER::EX,150 });
	}

	// ñÓàÛ
	lpImageMng.AddDraw({ lpImageMng.getImage("Arrow")[0],_cpos.x - 300 + (_offpush.x * _select),_cpos.y - _offpush.y,0.0,LAYER::EX,150 });
}

void Menu::Item1(void)
{
	// ïóòCï~Ç∆òg
	lpImageMng.AddDraw({ lpImageMng.getImage("Menu")[0],_cpos.x + 200,_cpos.y,0.0,LAYER::EX,20 });
	lpImageMng.AddDraw({ lpImageMng.getImage("Space")[0],_cpos.x - 200 + _offpush.x,_cpos.y - _offpush.y,0.0,LAYER::EX,30 });

	// ñÓàÛ

	lpImageMng.AddDraw({ lpImageMng.getImage("Arrow")[0],lpSceneMng.GetcPos().x - 300,lpSceneMng.GetcPos().y,0.0,LAYER::EX,31 });
	lpTradeMng.BagDraw({ -200,0 },LAYER::EX,200);

}

void Menu::Item2(void)
{
	// ïóòCï~Ç∆òg
	lpImageMng.AddDraw({ lpImageMng.getImage("Menu")[0],_cpos.x + 200,_cpos.y,0.0,LAYER::EX,20 });
	lpImageMng.AddDraw({ lpImageMng.getImage("Space")[0],_cpos.x - 200 + _offpush.x,_cpos.y - _offpush.y,0.0,LAYER::EX,30 });

	lpTradeMng.BagDraw({ -200,0 }, LAYER::EX,200);
}

void Menu::Item3(void)
{
	// ïóòCï~Ç∆òg
	lpImageMng.AddDraw({ lpImageMng.getImage("Menu")[0],_cpos.x + 200,_cpos.y,0.0,LAYER::EX,20 });
	lpImageMng.AddDraw({ lpImageMng.getImage("Space")[0],_cpos.x - 200 + _offpush.x,_cpos.y - _offpush.y,0.0,LAYER::EX,30 });

	lpTradeMng.BagDraw({ -200,0 }, LAYER::EX,200);
}