#include "ItemTrader.h"
#include "Scene/SceneMng.h"

ItemTrader* ItemTrader::sInstance = nullptr;

void ItemTrader::Draw(void)
{
	for (auto data : _ItemList)
	{
		(*data).Draw();
	}
}

void ItemTrader::BagDraw(void)
{
	_pos.x = lpSceneMng.GetcPos().x + BAGOFF_X;
	_pos.y = lpSceneMng.GetcPos().y + BAGOFF_Y;
	for (auto data : _ItemBag)
	{
		(*data.first).setPos({_pos.x + (100*(data.second)),_pos.y});
		(*data.first).Draw();
	}
}

void ItemTrader::Trade(COLOR_TYPE color1, COLOR_TYPE color2)
{
	if (color1 == color2) { return; }	// �����F���m�̑����Z�͂��Ȃ�

	// RGB�ȊO�̑����Z�����Ȃ�
	if (color1 != COLOR_TYPE::RED && color1 != COLOR_TYPE::BLUE && color1 != COLOR_TYPE::GREEN)
	{
		return;
	}
	else if (color2 != COLOR_TYPE::RED && color2 != COLOR_TYPE::BLUE && color2 != COLOR_TYPE::GREEN)
	{
		return;
	}

	color = static_cast<int>(color1) + static_cast<int>(color2);

	return;

}

const void ItemTrader::SetItemList(Vector2 pos, ITEM_TYPE itype, COLOR_TYPE ctype)
{
	_ItemList.emplace_back(new Item(pos, itype, ctype, _ItemList.size()));	// �T�C�Y�ԍ�������B
	return;
}


void ItemTrader::AddBag(void)
{
	for (auto data = _ItemList.begin();data != _ItemList.end();)
	{
		if ((*data)->getPos().x - 50 <= (*lpSceneMng.GetPlObj())->getPos().x + 50 &&
			(*data)->getPos().x + 50 >= (*lpSceneMng.GetPlObj())->getPos().x - 50)
		{
			_ItemBag.emplace_back(*data,_ItemBag.size());
			data = _ItemList.erase(data);		// ����Ԃ�
		}
		else
		{
			data++;								// ���₳�Ȃ��Ɖ��Ȃ� else����Ȃ��Ă�����ς�������++�Ɠ����l
		}
	}
}


void ItemTrader::NoReturn(void)
{
	
}

ItemTrader::ItemTrader()
{
	color = 0x000000;
}

ItemTrader::~ItemTrader()
{
}
