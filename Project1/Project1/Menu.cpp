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
	_offpush.y = 150;
	_offpush.x = 200;

	lpImageMng.getImage("image/���j���[.png", "Menu");
	lpImageMng.getImage("image/Space.png", "Space");
	lpImageMng.getImage("image/arrow.png", "Arrow");
	lpImageMng.getImage("image/����.png", "Mix");
}

Menu::~Menu()
{
}

bool Menu::Update(void)
{
	// ���j���[�J�n
	if (_start == false)
	{
		_start = true;
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_BACK, 1, 1);
	}
	_cpos = lpSceneMng.GetcPos();

	(this->*type)();	// select,mix,


	// ���j���[�I��
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
	// SELECT����̐؂�ւ�

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
	// �����E�Ɉړ�������
	if (lpButtonMng.Buttonf(0, XINPUT_BUTTON_DPAD_RIGHT).first == 1 &&
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_DPAD_RIGHT).second == 0)
	{
		_select++;
		if (_select > 2)
		{
			_select = 0;
		}
	}

	//�@�������Ɉړ�������
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

	// Select �ɖ߂�
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

void Menu::SelectDraw(void)
{
	// ���C�~�̕`��
	lpImageMng.AddDraw({ lpImageMng.getImage("Menu")[0],_cpos.x + 200,_cpos.y,0.0,LAYER::EX,100 });

	// ���̕`��
	lpImageMng.AddDraw({ lpImageMng.getImage("Arrow")[0],_cpos.x - 300,_cpos.y - 150 + (100 * _select),0,LAYER::EX,101 });

	// �����̕����`��
	lpImageMng.AddDraw({ lpImageMng.getImage("Mix")[0],_cpos.x - 200,_cpos.y - 50,0.0,LAYER::EX,101 });
}

void Menu::MixDraw(void)
{
	// ���C�~�̕`��
	lpImageMng.AddDraw({ lpImageMng.getImage("Menu")[0],_cpos.x + 200,_cpos.y,0.0,LAYER::EX,100 });

	// �A�C�e���I��
	for (int x = 0;x < 3;x++)
	{
		lpImageMng.AddDraw({ lpImageMng.getImage("Space")[0],_cpos.x - 200 + (_offpush.x * x),_cpos.y - _offpush.y,0.0,LAYER::EX,150 });
	}

	// ���
	lpImageMng.AddDraw({ lpImageMng.getImage("Arrow")[0],_cpos.x - 300 + (_offpush.x * _select),_cpos.y - _offpush.y,0.0,LAYER::EX,150 });
}
