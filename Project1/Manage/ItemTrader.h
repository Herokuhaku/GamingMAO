#pragma once
#include <vector>
#include <memory>
#include <map>
#include "../Object/Object.h"
#include "../Object/Item.h"

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
	void BagDraw(Vector2D pos,LAYER lay, int off);
	COLOR_TYPE Trade(COLOR_TYPE color1, COLOR_TYPE color2);
	bool TradeCheck(COLOR_TYPE color1, COLOR_TYPE color2);
	const void SetItemList(Vector2 pos, ITEM_TYPE itype,COLOR_TYPE ctype, int stage);
	bool NoReturn(int no);
	ItemSave &ReturnBag(int no);

	void DeleteItem(ItemSave& item);
	void AddBag(void);


	void BagNoSort(void);			// バッグの中のものを順番に番号を付ける
	void BagTypeSort(void);			// バッグの中の石と本の数を数える
	void BagTypeCount(void);		// 何色の石が何個あるか数える
	
	std::pair<int, int> getcount(void);	// 本,石の数を返す
	
	std::array<int, 6> getrock(void);	// 何色の石が何個あるかを返す //順番は 赤,緑,青,黄,マゼンタ,シアン

private:
	ItemTrader();
	~ItemTrader();
	static ItemTrader* sInstance;
	std::vector<std::shared_ptr<Item>>_ItemList;				// 落ちているアイテム
//	std::vector<std::pair<std::shared_ptr<Item>,int>> _ItemBag;	// 持っているアイテム

	std::array<int,6> rock;										// 石の種類とその数 //順番は 赤,緑,青,黄,マゼンタ,シアン

	int color;
	Vector2 _pos;
	int _stone;
	int _book;
	std::vector<std::pair<ItemSave, int>> _IBag;
	ItemSave save;
};

