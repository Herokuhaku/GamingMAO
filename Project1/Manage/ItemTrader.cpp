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
	for (auto data : _ItemBag)
	{
		if ((*data.first).getItemType().first == ITEM_TYPE::BOOK)
		{
			(*data.first).setPos({ _pos.x + (200 * (*data.first).getItemTypeNo().first),_pos.y });
		}
		else if ((*data.first).getItemType().first == ITEM_TYPE::STONE)
		{
			(*data.first).setPos({ _pos.x + (100 * (*data.first).getItemTypeNo().second),_pos.y });
		}
		(*data.first).OLDraw(lay);
	}
}

COLOR_TYPE ItemTrader::Trade(COLOR_TYPE color1, COLOR_TYPE color2)
{
	color = static_cast<int>(color1) + static_cast<int>(color2);

	return static_cast<COLOR_TYPE>(color);
}

bool ItemTrader::TradeCheck(COLOR_TYPE color1, COLOR_TYPE color2)
{
	if (color1 == color2) { return false; }	// 同じ色同士の足し算はしない

	// RGB以外の足し算もしない
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

const void ItemTrader::SetItemList(Vector2 pos, ITEM_TYPE itype, COLOR_TYPE ctype)
{
	_ItemList.emplace_back(new Item(pos, itype, ctype, _ItemList.size()));	// サイズ番号を入れる。
	return;
}

std::shared_ptr<Item> ItemTrader::ReBag(int no)
{
	if (_ItemBag.empty() == true)
	{
		return nullptr;
	}

	if (_ItemBag.size() <= no)
	{
		return nullptr;
	}

	return _ItemBag.at(no).first;
}



void ItemTrader::DeleteItem(std::shared_ptr<Item> &item)
{
	for (auto bag =_ItemBag.begin() ; bag != _ItemBag.end();)
	{
		if ((*bag).first == item)
		{
			bag = _ItemBag.erase(std::move(bag));
		}
		else
		{
			bag++;
		}
	}
	BagTypeSort();
	BagTypeCount();
}

void ItemTrader::AddBag(void)
{
	for (auto data = _ItemList.begin();data != _ItemList.end();)
	{
		if ((*data)->getPos().x - 50 <= (*lpSceneMng.GetPlObj(lpTimeMng.getTime()))->getPos().x + 50 &&
			(*data)->getPos().x + 50 >= (*lpSceneMng.GetPlObj(lpTimeMng.getTime()))->getPos().x - 50)
		{
			_ItemBag.emplace_back(*data,_ItemBag.size());
			(*data)->ChangeDir(DIR::LEFT);
			data = _ItemList.erase(data);		// 次を返す
		}
		else
		{
			data++;								// 増やさないと回らない elseじゃなくても次を変えすから++と同じ値
		}
	}
	BagTypeSort();
	BagTypeCount();
}


void ItemTrader::NoReturn(void)
{
	
}

void ItemTrader::BagNoSort(void)
{
	int count = 0;
	for (int i = 0;i < _ItemBag.size();i++)
	{
		if (_ItemBag.at(i).second != count)
		{
			_ItemBag.at(i).second = count;
			_ItemBag.at(i).first->SetBagNo(count);
		}
		count++;
	}
}

int ItemTrader::BagTypeSort(void)
{
	_stone = 0;
	_book  = 0;

	for (auto data : _ItemBag)
	{
		switch(data.first->getItemType().first)
		{
		case ITEM_TYPE::BOOK:
			data.first->setItemTypeNo(_book,-1);
			_book++;
			break;
		case ITEM_TYPE::STONE:
			data.first->setItemTypeNo(-1, _stone);
			_stone++;
			break;
		default:
			break;
		};
	}
	return 0;
}

void ItemTrader::BagTypeCount(void)
{
	for (int i = 0;i < 6;i++)
	{
		rock.at(i) = 0;
	}
	for (auto item : _ItemBag)
	{
		if ((*item.first).getItemType().first == ITEM_TYPE::STONE)
		{
			switch(item.first->getItemType().second)
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

void ItemTrader::ChangeDir(DIR dir)
{
	for (auto item : _ItemBag)
	{
		(*item.first).ChangeDir(dir);
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
