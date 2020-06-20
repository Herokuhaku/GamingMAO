#pragma once
#include <vector>
#include <array>
#include <memory>
#include <map>
#include "../Object/Object.h"
#include "../Object/Item.h"
#include "../Graphic/LAYER.h"

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
	static void Destroy(void)
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}
	
	void Draw(void);
	void BagDraw(Vector2D pos,LAYER lay, Vector2 off , Vector2D rad);
	void ToolDraw(Vector2 pos, LAYER lay, Vector2 off, Vector2D rad);

	void inTool(void);

	COLOR Trade(COLOR color1, COLOR color2);
	bool ColorTradeCheck(COLOR color1, COLOR color2);
	const void SetItemList(Vector2 pos, ITEM_TYPE itype,COLOR ctype, int stage);
	bool NoReturn(int no);
	ItemSave& ReturnBag(int no);

	void DeleteItem(ItemSave& item);
	void AddBag(void);
	void AddBag(ItemSave &save);

	int ReturnNo(ITEM_TYPE itemtype, COLOR color);
	bool ReBook(COLOR color);

	std::pair<int, int> getcount(void);	// 本,石の数を返す
	
	std::array<int, 6> getrock(void);	// 何色の石が何個あるかを返す //順番は 赤,緑,青,黄,マゼンタ,シアン
	void ChangeCount(bool num);
	

private:
	ItemTrader();
	~ItemTrader();
	static ItemTrader* sInstance;
	std::vector<std::shared_ptr<Item>>_ItemList;				// 落ちているアイテム
//	std::vector<std::pair<std::shared_ptr<Item>,int>> _ItemBag;	// 持っているアイテム

	void BagTypeSort(void);			// バッグの中の石と本の数を数える
	void BagTypeCount(void);		// 何色の石が何個あるか数える
	void BagNoSort(void);			// バッグの中のものを順番に番号を付ける

	const char* ChangeName(ITEM_TYPE _itemtype, COLOR _colortype);
	std::array<int,6> rock;										// 石の種類とその数 //順番は 赤,緑,青,黄,マゼンタ,シアン

	int color;
	Vector2 _pos;
	int _stone;
	int _book;
	int _tool;
	int _toolMax;
	std::vector<std::pair<ItemSave, int>> _IBag;
	std::vector<std::pair<ItemSave, int>> _ItemBag;
	ItemSave save;
	
	int _drawtool[5];
	static int _count;
};

