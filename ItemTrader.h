#pragma once
#include <vector>
#include <memory>
#include "Object/Object.h"
#include "Object/Item.h"

#define lpTradeMng ItemTrader::GetInstance()

class ItemTrader
{
public:
	static ItemTrader &GetInstance()
	{
		Create();

		return *sInstance;
	}

	static void Create(void)
	{
		if (sInstance == nullptr)
		{
			sInstance = new ItemTrader();
		}
	}
	
	void Draw(void);
	void Trade(COLOR_TYPE color1, COLOR_TYPE color2);
	const void SetItemList(Vector2 pos, ITEM_TYPE itype,COLOR_TYPE ctype);
	const std::vector<std::shared_ptr<Object>> itemlist(void);
	void AddBag(void);
	void NoReturn(void);

private:
	ItemTrader();
	~ItemTrader();
	static ItemTrader* sInstance;
	std::vector<std::shared_ptr<Item>>_ItemList;
	// std::map<std::pair<ITEM_TYPE, COLOR_TYPE>, int> _Itembag;
	//std::vector<std::shared_ptr<Object>> _ItemBag;
	std::vector<std::shared_ptr<Item>> _ItemBag;

	int color;
};

