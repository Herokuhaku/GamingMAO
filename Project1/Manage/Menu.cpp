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
	tmpos = lpSceneMng.ScreenSize;
	_cpos = tmpos / 2;
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

	(this->*type)();	// select,mix,


	// ���j���[�I��
	if(lpButtonMng.Buttonf(0, XINPUT_BUTTON_BACK).first == 1 &&
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_BACK).second == 0)
	{
		type = &Menu::SELECT;
		MixFlag = false;
		_select = 0;
		_start = false;

		for (int x = 0;x < _asize;x++)
		{
			_selectItem.at(x) = { nullptr,0 };
		}
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
	if (!MixFlag)
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

		// �A�C�e����I��
		if (lpButtonMng.Buttonf(0, XINPUT_BUTTON_B).first == 1 &&
			lpButtonMng.Buttonf(0, XINPUT_BUTTON_B).second == 0)
		{
			lpButtonMng.Buttonf(0, XINPUT_BUTTON_B, 1, 1);
			_selectNo = static_cast<SELECT_ITEM>(_select);
			_select = 0;
			MixFlag = true;
		}
		// Select �ɖ߂�
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
	// ���C�~�̕`��
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Menu")[0],_cpos.x,_cpos.y,0.0,LAYER::EX,100 });

	// ���̕`��
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Arrow")[0],_cpos.x - 300,_cpos.y - 150 + (100 * _select),0,LAYER::EX,101 });

	// �����̕����`��
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Mix")[0],_cpos.x - 200,_cpos.y - 50,0.0,LAYER::EX,101 });
}

void Menu::MixDraw(void)
{
	// ���C�~�̕`��
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Menu")[0],_cpos.x,_cpos.y,0.0,LAYER::EX,100 });

	// �A�C�e���I��
	for (int x = 0;x < 3;x++)
	{
		//lpImageMng.AddBackDraw({ lpImageMng.getImage("Space")[0],_cpos.x - 200 + (_offpush.x * x),_cpos.y - _offpush.y,0.0,LAYER::EX,150 });
		lpImageMng.AddBackDraw({ lpImageMng.getImage("Space")[0],_cpos.x -200+(_offpush.x*x),_cpos.y - _offpush.y,0.0,LAYER::EX,100 });
	}

	// ���
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Arrow")[0],_cpos.x - 300 + (_offpush.x * _select),_cpos.y - _offpush.y,0.0,LAYER::EX,150 });

	// �I����
	ItemSelectDraw();
}

void Menu::ItemSelectDraw(void)
{
	for (auto data : _selectItem)
	{
		if (data.first != nullptr)
		{
			(*data.first).setPos({_cpos.x - 200 + (_offpush.x * (data.second)),_cpos.y- _offpush.y });
			(*data.first).OLDraw(LAYER::EX);
		}
	}


}

void Menu::Item1(void)
{
	ItemSelectD();
	// �I�����Ă���A�C�e���̕\��
	if (_selectItem.at(0).first != nullptr) //�@���̒��ɃA�C�e��������ꍇ�̂݁B
	{
		(*_selectItem.at(0).first).setPos({_cpos.x,_cpos.y-_offpush.y});
		(*_selectItem.at(0).first).OLDraw(LAYER::EX);
	}

	if (lpButtonMng.Buttonf(0, XINPUT_BUTTON_B).first == 1 &&
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_B).second == 0)
	{
		if (lpTradeMng.ReBag(_select) != nullptr)
		{
			_selectItem.at(0) = { lpTradeMng.ReBag(_select), 0 };
			MixFlag = false;
			// array�̃T�C�Y���񂷁B
			for (int i = 0;i<_asize;i++)		
			{
				// �A�C�e���������Ă���ꍇ�̂�
				if (_selectItem.at(i).first != nullptr)	
				{
					// �����A�C�e�����Ⴄ�Ƃ���ɓ����Ă�����Ⴄ�ق��̃A�C�e����nullptr�ɂ���
					if ((*_selectItem.at(i).first).GetBagNo() == _select && _selectItem.at(i) != _selectItem.at(0))
					{
						_selectItem.at(i).first = nullptr;
					}
				}
			}
		}
	}
	// _selectItem.at(0).first->
}

void Menu::Item2(void)
{
	ItemSelectD();
	// �I�����Ă���A�C�e���̕\��
	if (_selectItem.at(1).first != nullptr) //�@���̒��ɃA�C�e��������ꍇ�̂݁B
	{
		(*_selectItem.at(1).first).setPos({ _cpos.x,_cpos.y - _offpush.y });
		(*_selectItem.at(1).first).OLDraw(LAYER::EX);
	}

	if (lpButtonMng.Buttonf(0, XINPUT_BUTTON_B).first == 1 &&
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_B).second == 0)
	{
		if (lpTradeMng.ReBag(_select) != nullptr)
		{
			_selectItem.at(1) = { lpTradeMng.ReBag(_select),1 };
			MixFlag = false;
			// array�̃T�C�Y���񂷁B
			for (int i = 0;i < _asize;i++)
			{
				// �A�C�e���������Ă���ꍇ�̂�
				if (_selectItem.at(i).first != nullptr)
				{
					// �����A�C�e�����Ⴄ�Ƃ���ɓ����Ă�����Ⴄ�ق��̃A�C�e����nullptr�ɂ���
					if ((*_selectItem.at(i).first).GetBagNo() == _select && _selectItem.at(i) != _selectItem.at(1))
					{
						_selectItem.at(i).first = nullptr;
					}
				}
			}
		}

	}
}

void Menu::Item3(void)
{
	ItemSelectD();
	// �I�����Ă���A�C�e���̕\��
	if (_selectItem.at(2).first != nullptr)	//�@���̒��ɃA�C�e��������ꍇ�̂݁B
	{
		(*_selectItem.at(2).first).setPos({ _cpos.x,_cpos.y - _offpush.y });
		(*_selectItem.at(2).first).OLDraw(LAYER::EX);
	}

	if (lpButtonMng.Buttonf(0, XINPUT_BUTTON_B).first == 1 &&
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_B).second == 0)
	{
		if (lpTradeMng.ReBag(_select) != nullptr)
		{
			_selectItem.at(2) = { lpTradeMng.ReBag(_select), 2 };
			MixFlag = false;
			// array�̃T�C�Y���񂷁B
			for (int i = 0;i < _asize;i++)
			{
				// �A�C�e���������Ă���ꍇ�̂�
				if (_selectItem.at(i).first != nullptr)
				{
					// �����A�C�e�����Ⴄ�Ƃ���ɓ����Ă�����Ⴄ�ق��̃A�C�e����nullptr�ɂ���
					if ((*_selectItem.at(i).first).GetBagNo() == _select && _selectItem.at(i) != _selectItem.at(2))
					{
						_selectItem.at(i).first = nullptr;
					}
				}
			}
		}
	}
}

void Menu::ItemSelectD(void)
{
	// ���C�~�Ƙg
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Menu")[0],_cpos.x,_cpos.y,0.0,LAYER::EX,20 });
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Space")[0],_cpos.x,_cpos.y - _offpush.y,0.0,LAYER::EX,30 });

	
	// ���
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Arrow")[0],(_cpos.x - 300) + (_select * 200),
		_cpos.y,0.0,LAYER::EX,31 });

	lpTradeMng.BagDraw({ _cpos.x*1.0 -200,_cpos.y*1.0 }, LAYER::EX, 200);

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

	if (lpButtonMng.Buttonf(0, XINPUT_BUTTON_A).first == 1 &&
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_A).second == 0)
	{
		MixFlag = false;
	}
}
