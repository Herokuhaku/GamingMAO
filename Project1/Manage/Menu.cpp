#include "Menu.h"
#include "../Scene/SceneMng.h"
#include "ButtonMng.h"
#include "../Graphic/StringAddDraw.h"

Menu* Menu::sInstance = nullptr;


Menu::Menu()
{
	type = &Menu::SELECT;
	_start = false;
	push_select = false;
	_select = 0;
	_select2 = 0;
	_offpush.y = 150;
	_offpush.x = 200;
	MixFlag = false;
	tmpos = lpSceneMng.ScreenSize;
	_cpos = tmpos / 2;
	_count = 2;
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
		lpTradeMng.ChangeDir(DIR::RIGHT);
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
		lpTradeMng.ChangeDir(DIR::LEFT);
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
	return _start;
}


void Menu::SELECT(void)
{
	// ��󑀍�(�X�e�B�b�N)
	SelectCount(_select,XINPUT_THUMBL_Y);
	//�@��󑀍� (DPAD)
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
		// ��󑀍�(�X�e�B�b�N)
		SelectCount(_select,XINPUT_THUMBL_X);
		// ������ɂ��炷
		if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).first == 2 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second == 0)
		{
			_select2++;
			if (_select2 > 1)
			{
				_select2 = 0;
			}
		}
		// �������ɂ��炷
		if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).first == 1 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second == 0)
		{
			_select2--;
			if (_select2 < 0)
			{
				_select2 = 1;
			}
		}

		// �����E�Ɉړ�������
		if (lpButtonMng.Buttonf(0, XINPUT_BUTTON_DPAD_RIGHT).first == 1 &&
			lpButtonMng.Buttonf(0, XINPUT_BUTTON_DPAD_RIGHT).second == 0)
		{
			_select++;
			if (_select > _count)
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
				_select = _count;
			}
		}



		// ����`��
		lpStrAdd.AddDraw("����", _cpos.x, _cpos.y+75, 0xffffff, DRAW_TO_CENTER);

		MixDraw();

		// �A�C�e����I��
		if ((lpButtonMng.Buttonf(0, XINPUT_BUTTON_B).first == 1 &&
			lpButtonMng.Buttonf(0, XINPUT_BUTTON_B).second == 0))
		{
			if (_select2 == 0)
			{
				lpButtonMng.Buttonf(0, XINPUT_BUTTON_B, 1, 1);
				_selectNo = static_cast<SELECT_ITEM>(_select);
				_select = 0;
				_count = lpTradeMng.getcount().second-1;
				MixFlag = true;
			}
			else if (_select2 == 1)
			{
				lpButtonMng.Buttonf(0, XINPUT_BUTTON_B, 1, 1);
				if (_selectItem.at(0).first != nullptr && _selectItem.at(1).first != nullptr && _selectItem.at(2).first != nullptr)
				{
					Mix(_selectItem.at(0).first, _selectItem.at(1).first, _selectItem.at(2).first);
				}
			}
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
		// ���Ԗڂ̃A�C�e���I�����Ă��邩�B
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

bool Menu::Mix(ItemS& item1, ItemS& item2, ItemS& item3)
{
	if (item1->getItemType().first == ITEM_TYPE::BOOK || item2->getItemType().first == ITEM_TYPE::BOOK)
	{
		return false;
	}
	if (!lpTradeMng.TradeCheck(item1->getItemType().second, item2->getItemType().second))
	{
		return false;
	}

	item1->ChangeType(ITEM_TYPE::STONE, lpTradeMng.Trade(item1->getItemType().second, item2->getItemType().second));
	lpTradeMng.DeleteItem(item2);
	lpTradeMng.BagNoSort();
	// �A�C�e���̓�ڂ��������ߍ������X�g���������
	for (int i = 0;i < 3;i++)
	{
		_selectItem.at(i) = { nullptr,i};
	}
	return true;
}

void Menu::ItemMup(void)
{
	
}

void Menu::SelectCount(int& select, int thumb)
{
	// �����E or ��Ɉړ�������
	if (lpButtonMng.Thumbf(0, thumb).first == 1 &&
		lpButtonMng.Thumbf(0, thumb).second == 0)
	{
		select++;
		if (select > _count)
		{
			select = 0;
		}
	}
	// ������ or ���Ɉړ�������
	if (lpButtonMng.Thumbf(0, thumb).first == 2 &&
		lpButtonMng.Thumbf(0, thumb).second == 0)
	{
		select--;
		if (select < 0)
		{
			select = _count;
		}
	}

}


void Menu::SelectDraw(void)
{
	// ���C�~�̕`��
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Menu")[0], _cpos.x,_cpos.y, 1.0, 0.0, LAYER::EX, 100, DX_BLENDMODE_NOBLEND, 0 });

	// ���̕`��
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Arrow")[0], _cpos.x - 300, _cpos.y - 150 + (100 * _select), 1.0, 0, LAYER::EX, 101, DX_BLENDMODE_NOBLEND, 0 });

	// �����̕����`��
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Mix")[0], _cpos.x - 200, _cpos.y - 50, 1.0, 0.0, LAYER::EX, 101, DX_BLENDMODE_NOBLEND, 0 });
}

void Menu::MixDraw(void)
{
	// ���C�~�̕`��
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Menu")[0], _cpos.x, _cpos.y, 1.0, 0.0, LAYER::EX, 100, DX_BLENDMODE_NOBLEND, 0 });

	// �A�C�e���I��
	for (int x = 0;x < 3;x++)
	{
		lpImageMng.AddBackDraw({ lpImageMng.getImage("Space")[0], _cpos.x - 200 + (_offpush.x * x), _cpos.y - _offpush.y, 1.0, 0.0, LAYER::EX, 100, DX_BLENDMODE_NOBLEND, 0 });
	}

	// ���
	if (_select2 == 0)
	{
		lpImageMng.AddBackDraw({ lpImageMng.getImage("Arrow")[0], _cpos.x - 300 + (_offpush.x * _select), _cpos.y - _offpush.y, 1.0, 0.0, LAYER::EX, 150, DX_BLENDMODE_NOBLEND, 0 });
	}
	else
	{
		lpImageMng.AddBackDraw({ lpImageMng.getImage("Arrow")[0], _cpos.x - 75, _cpos.y + 100, 1.0, 0.0, LAYER::EX, 150, DX_BLENDMODE_NOBLEND, 0 });
	}
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
			_select = 0;
			_count = 2;
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
			_count = 2;
			_select = 0;
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
			_count = 2;
			_select = 0;
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
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Menu")[0], _cpos.x, _cpos.y, 1.0, 0.0, LAYER::EX, 20, DX_BLENDMODE_NOBLEND, 0 });
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Space")[0], _cpos.x, _cpos.y - _offpush.y, 1.0, 0.0, LAYER::EX, 30, DX_BLENDMODE_NOBLEND, 0 });

	
	// ���
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Arrow")[0], (_cpos.x - 300) + (_select * 200),
		_cpos.y, 1.0, 0.0, LAYER::EX, 31, DX_BLENDMODE_NOBLEND, 0 });

	lpTradeMng.BagDraw({ static_cast<double>(_cpos.x - 200), static_cast<double>(_cpos.y) }, LAYER::EX, 200);

	SelectCount(_select,XINPUT_THUMBL_X);
	//// �����E�Ɉړ�������


	if (lpButtonMng.Buttonf(0, XINPUT_BUTTON_A).first == 1 &&
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_A).second == 0)
	{
		MixFlag = false;
	}
}
