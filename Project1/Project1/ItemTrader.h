#pragma once
#include <vector>
#include <memory>
#include "Object/Object.h"
#include "Object/Item.h"

#define lpTradeMng ItemTrader::GetInstance()

#define BAGOFF_X 200
#define BAGOFF_Y 200

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
	void BagDraw(void);
	void Trade(COLOR_TYPE color1, COLOR_TYPE color2);
	const void SetItemList(Vector2 pos, ITEM_TYPE itype,COLOR_TYPE ctype);
	void AddBag(void);
	void NoReturn(void);

private:
	ItemTrader();
	~ItemTrader();
	static ItemTrader* sInstance;
	std::vector<std::shared_ptr<Item>>_ItemList;
	// std::map<std::pair<ITEM_TYPE, COLOR_TYPE>, int> _Itembag;
	//std::vector<std::shared_ptr<Object>> _ItemBag;
	std::vector<std::pair<std::shared_ptr<Item>,int>> _ItemBag;

	int color;
	Vector2 _pos;
};

