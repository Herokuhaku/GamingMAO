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
	lpImageMng.getImage("image/メニュー.png", "Menu");
	lpImageMng.getImage("image/Space.png", "Space");
	lpImageMng.getImage("image/arrow.png", "Arrow");
	lpImageMng.getImage("image/合成.png", "Mix");

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
		lpTradeMng.ChangeDir(DIR::RIGHT);
	}

	(this->*type)();	// select,mix,


	// メニュー終了
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
	// 矢印操作(スティック)
	SelectCount(_select,XINPUT_THUMBL_Y);
	//　矢印操作 (DPAD)
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
	// SELECTからの切り替え
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
		// 矢印操作(スティック)
		SelectCount(_select,XINPUT_THUMBL_X);
		// 矢印を上にずらす
		if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).first == 2 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second == 0)
		{
			_select2++;
			if (_select2 > 1)
			{
				_select2 = 0;
			}
		}
		// 矢印を下にずらす
		if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).first == 1 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second == 0)
		{
			_select2--;
			if (_select2 < 0)
			{
				_select2 = 1;
			}
		}

		// 矢印を右に移動させる
		if (lpButtonMng.Buttonf(0, XINPUT_BUTTON_DPAD_RIGHT).first == 1 &&
			lpButtonMng.Buttonf(0, XINPUT_BUTTON_DPAD_RIGHT).second == 0)
		{
			_select++;
			if (_select > _count)
			{
				_select = 0;
			}
		}
		//　矢印を左に移動させる
		if (lpButtonMng.Buttonf(0, XINPUT_BUTTON_DPAD_LEFT).first == 1 &&
			lpButtonMng.Buttonf(0, XINPUT_BUTTON_DPAD_LEFT).second == 0)
		{
			_select--;
			if (_select < 0)
			{
				_select = _count;
			}
		}



		// 決定描画
		lpStrAdd.AddDraw("決定", _cpos.x, _cpos.y+75, 0xffffff, DRAW_TO_CENTER);

		MixDraw();

		// アイテムを選択
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
		// Select に戻る
		if (lpButtonMng.Buttonf(0, XINPUT_BUTTON_A).first == 1 &&
			lpButtonMng.Buttonf(0, XINPUT_BUTTON_A).second == 0)
		{
			type = &Menu::SELECT;
		}
	}
	else 
	{
		// 何番目のアイテム選択しているか。
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
	// アイテムの二つ目を消すため合成リストからも消す
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
	// 矢印を右 or 上に移動させる
	if (lpButtonMng.Thumbf(0, thumb).first == 1 &&
		lpButtonMng.Thumbf(0, thumb).second == 0)
	{
		select++;
		if (select > _count)
		{
			select = 0;
		}
	}
	// 矢印を左 or 下に移動させる
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
	// 風呂敷の描画
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Menu")[0], _cpos.x,_cpos.y, 1.0, 0.0, LAYER::EX, 100, DX_BLENDMODE_NOBLEND, 0 });

	// 矢印の描画
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Arrow")[0], _cpos.x - 300, _cpos.y - 150 + (100 * _select), 1.0, 0, LAYER::EX, 101, DX_BLENDMODE_NOBLEND, 0 });

	// 合成の文字描画
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Mix")[0], _cpos.x - 200, _cpos.y - 50, 1.0, 0.0, LAYER::EX, 101, DX_BLENDMODE_NOBLEND, 0 });
}

void Menu::MixDraw(void)
{
	// 風呂敷の描画
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Menu")[0], _cpos.x, _cpos.y, 1.0, 0.0, LAYER::EX, 100, DX_BLENDMODE_NOBLEND, 0 });

	// アイテム選択
	for (int x = 0;x < 3;x++)
	{
		lpImageMng.AddBackDraw({ lpImageMng.getImage("Space")[0], _cpos.x - 200 + (_offpush.x * x), _cpos.y - _offpush.y, 1.0, 0.0, LAYER::EX, 100, DX_BLENDMODE_NOBLEND, 0 });
	}

	// 矢印
	if (_select2 == 0)
	{
		lpImageMng.AddBackDraw({ lpImageMng.getImage("Arrow")[0], _cpos.x - 300 + (_offpush.x * _select), _cpos.y - _offpush.y, 1.0, 0.0, LAYER::EX, 150, DX_BLENDMODE_NOBLEND, 0 });
	}
	else
	{
		lpImageMng.AddBackDraw({ lpImageMng.getImage("Arrow")[0], _cpos.x - 75, _cpos.y + 100, 1.0, 0.0, LAYER::EX, 150, DX_BLENDMODE_NOBLEND, 0 });
	}
	// 選択後
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
	// 選択しているアイテムの表示
	if (_selectItem.at(0).first != nullptr) //　その中にアイテムがある場合のみ。
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
			// arrayのサイズ分回す。
			for (int i = 0;i<_asize;i++)		
			{
				// アイテムが入っている場合のみ
				if (_selectItem.at(i).first != nullptr)	
				{
					// 同じアイテムが違うところに入っていたら違うほうのアイテムをnullptrにする
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
	// 選択しているアイテムの表示
	if (_selectItem.at(1).first != nullptr) //　その中にアイテムがある場合のみ。
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
			// arrayのサイズ分回す。
			for (int i = 0;i < _asize;i++)
			{
				// アイテムが入っている場合のみ
				if (_selectItem.at(i).first != nullptr)
				{
					// 同じアイテムが違うところに入っていたら違うほうのアイテムをnullptrにする
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
	// 選択しているアイテムの表示
	if (_selectItem.at(2).first != nullptr)	//　その中にアイテムがある場合のみ。
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
			// arrayのサイズ分回す。
			for (int i = 0;i < _asize;i++)
			{
				// アイテムが入っている場合のみ
				if (_selectItem.at(i).first != nullptr)
				{
					// 同じアイテムが違うところに入っていたら違うほうのアイテムをnullptrにする
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
	// 風呂敷と枠
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Menu")[0], _cpos.x, _cpos.y, 1.0, 0.0, LAYER::EX, 20, DX_BLENDMODE_NOBLEND, 0 });
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Space")[0], _cpos.x, _cpos.y - _offpush.y, 1.0, 0.0, LAYER::EX, 30, DX_BLENDMODE_NOBLEND, 0 });

	
	// 矢印
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Arrow")[0], (_cpos.x - 300) + (_select * 200),
		_cpos.y, 1.0, 0.0, LAYER::EX, 31, DX_BLENDMODE_NOBLEND, 0 });

	lpTradeMng.BagDraw({ static_cast<double>(_cpos.x - 200), static_cast<double>(_cpos.y) }, LAYER::EX, 200);

	SelectCount(_select,XINPUT_THUMBL_X);
	//// 矢印を右に移動させる


	if (lpButtonMng.Buttonf(0, XINPUT_BUTTON_A).first == 1 &&
		lpButtonMng.Buttonf(0, XINPUT_BUTTON_A).second == 0)
	{
		MixFlag = false;
	}
}
