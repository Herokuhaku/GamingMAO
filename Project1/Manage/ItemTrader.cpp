#include "ItemTrader.h"
#include "../Scene/SceneMng.h"

ItemTrader* ItemTrader::sInstance = nullptr;

Vector2 _offpush = {200, 150 };



void ItemTrader::Draw(void)
{
	for (auto data : _ItemList)
	{
		if ((*data).getStage() == lpMapMng.GetnowStage())
		{
			(*data).Draw();
		}
	}
}

void ItemTrader::BagDraw(Vector2D pos,LAYER lay,int off)
{
	_pos.x = pos.x;
	_pos.y = pos.y;
	for (auto data : _IBag)
	{
		if (data.first.itemtype == ITEM_TYPE::BOOK)
		{
			data.first.pos = { _pos.x + (100 * data.first.book),_pos.y };
			lpImageMng.AddBackDraw({ lpImageMng.getImage(data.first.image[0])[0],data.first.pos.x,data.first.pos.y, 1.0, 0.0,LAYER::EX, 110, DX_BLENDMODE_NOBLEND, 0 });
		}
		else if (data.first.itemtype == ITEM_TYPE::STONE)
		{
			data.first.pos = { _pos.x + (100 * data.first.stone),_pos.y };
			lpImageMng.AddBackDraw({ lpImageMng.getImage(data.first.image[0])[0],data.first.pos.x,data.first.pos.y, 1.0, 0.0,LAYER::EX, 110, DX_BLENDMODE_NOBLEND, 0 });
		}
	}
}

COLOR_TYPE ItemTrader::Trade(COLOR_TYPE color1, COLOR_TYPE color2)
{
	color = static_cast<int>(color1) + static_cast<int>(color2);

	return static_cast<COLOR_TYPE>(color);
}

bool ItemTrader::TradeCheck(COLOR_TYPE color1, COLOR_TYPE color2)
{
	if (color1 == color2) { return false; }	// �����F���m�̑����Z�͂��Ȃ�

	// RGB�ȊO�̑����Z�����Ȃ�
	if (color1 != COLOR_TYPE::RED && color1 != COLOR_TYPE::BLUE && color1 != COLOR_TYPE::GREEN)
	{
		return false;
	}
	else if (color2 != COLOR_TYPE::RED && color2 != COLOR_TYPE::BLUE && color2 != COLOR_TYPE::GREEN)
	{
		return false;
	}
	return true;
}

const void ItemTrader::SetItemList(Vector2 pos, ITEM_TYPE itype, COLOR_TYPE ctype,int stage)
{
	_ItemList.emplace_back(new Item(pos, itype, ctype, _ItemList.size(),stage));	// �T�C�Y�ԍ�������B
	return;
}

ItemSave &ItemTrader::ReturnBag(int no)
{
	return _IBag.at(no).first;
}

void ItemTrader::DeleteItem(ItemSave &item)
{
	for (auto bag = _IBag.begin();bag != _IBag.end();)
	{
		if ((*bag).first.bagNo == item.bagNo)
		{
			bag = _IBag.erase(std::move(bag));
		}
		else
		{
			bag++;
		}
	}
	BagTypeSort();
	BagTypeCount();
	BagNoSort();
}

void ItemTrader::AddBag(void)
{
	for (auto data = _ItemList.begin();data != _ItemList.end();)
	{
		if ((*data)->getPos().x - 50 <= (*lpSceneMng.GetPlObj(lpTimeMng.getTime()))->getPos().x + 50 &&
			(*data)->getPos().x + 50 >= (*lpSceneMng.GetPlObj(lpTimeMng.getTime()))->getPos().x - 50)
		{
		_IBag.emplace_back((*data)->ReturnSave(),_IBag.size());
			data = _ItemList.erase(data);		// ����Ԃ�
		}
		else
		{
			data++;								// ���₳�Ȃ��Ɖ��Ȃ� else����Ȃ��Ă�����ς�������++�Ɠ����l
		}
	}
	BagTypeSort();
	BagTypeCount();
}

void ItemTrader::AddBag(ItemSave&save)
{
	for (auto& bag : _IBag)
	{
		if (bag.first.bagNo == save.bagNo)
		{
			save.image[0] = ChangeName(save.itemtype,save.colortype);
			bag.first = save;
		}
	}
}


bool ItemTrader::NoReturn(int no)
{
	// �A�C�e���o�b�O�ɉ��������Ă��Ȃ��ꍇfalse��Ԃ�
	if (_IBag.empty() == true)
	{
		return false;
	}
	// �I�񂾔ԍ����T�C�Y�����傫���ꍇfalse��Ԃ�
	if (_IBag.size() <= no)
	{
		return false;
	}
	return true;
}

void ItemTrader::BagNoSort(void)
{
	int count = 0;
	for (int i = 0;i < _IBag.size();i++)
	{
		if (_IBag.at(i).second != count)
		{
			_IBag.at(i).second = count;
			_IBag.at(i).first.bagNo = count;
		}
		count++;
	}
}

void ItemTrader::BagTypeSort(void)
{
	_stone = 0;
	_book  = 0;

	for (auto &data:_IBag)
	{
		switch(data.first.itemtype)
		{
		case ITEM_TYPE::BOOK:
			data.first.book = _book;
			_book++;
			break;
		case ITEM_TYPE::STONE:
			data.first.stone = _stone;
 			_stone++;
			break;
		default:
			break;
		};
	}
}

void ItemTrader::BagTypeCount(void)
{
	for (int i = 0;i < 6;i++)
	{
		rock.at(i) = 0;
	}
	for (auto item : _IBag)
	{
		if (item.first.itemtype == ITEM_TYPE::STONE)
		{
			switch(item.first.colortype)
			{
			case COLOR_TYPE::BLACK:
				break;
			case COLOR_TYPE::RED:
				rock.at(0)++;
				break;
			case COLOR_TYPE::GREEN:
				rock.at(1)++;
				break;
			case COLOR_TYPE::BLUE:
				rock.at(2)++;
				break;
			case COLOR_TYPE::YELLOW:
				rock.at(3)++;
				break;
			case COLOR_TYPE::MAGENTA:
				rock.at(4)++;
				break;		
			case COLOR_TYPE::CYAN:
				rock.at(5)++;
				break;
			default:
				break;
			}
		}
	}
}


std::pair<int, int> ItemTrader::getcount(void)
{
	return {_book,_stone};
}

std::array<int, 6> ItemTrader::getrock(void)
{
	return rock;
}

ItemTrader::ItemTrader()
{
	for (int i = 0;i < 6;i++)
	{
		rock.at(i) = 0;
	}
	_book = 0;
	_stone = 0;
	color = 0x000000;
}

ItemTrader::~ItemTrader()
{
}

const char* ItemTrader::ChangeName(ITEM_TYPE _itemtype,COLOR_TYPE _colortype)
{
	AnmVec data;
	data.clear();

	// �ʏ�T�C�Y
	switch (_itemtype)
	{
	case ITEM_TYPE::BOOK:

		switch (_colortype)
		{
		case COLOR_TYPE::BLUE:
			save.image[0] = "BlueBook";
			break;
		case COLOR_TYPE::GREEN:
			save.image[0] = "GreenBook";
			break;
		case COLOR_TYPE::RED:
			save.image[0] = "RedBook";
			break;
		default:
			break;
		}
		break;
	case ITEM_TYPE::STONE:

		switch (_colortype)
		{
		case COLOR_TYPE::BLACK:
			break;
		case COLOR_TYPE::BLUE:
			save.image[0] = "BlueStone";
			break;
		case COLOR_TYPE::CYAN:
			save.image[0] = "CyanStone";
			break;
		case COLOR_TYPE::GREEN:
			save.image[0] = "GreenStone";
			break;
		case COLOR_TYPE::MAGENTA:
			save.image[0] = "MagentaStone";
			break;
		case COLOR_TYPE::RED:
			save.image[0] = "RedStone";
			break;
		case COLOR_TYPE::YELLOW:
			save.image[0] = "YellowStone";
			break;
		case COLOR_TYPE::WHITE:
			break;
		}
		break;
	}
	return save.image[0];
}
