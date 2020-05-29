#pragma once
#include <vector>
#include <array>
#include "../common/Vector2.h"
#include "ItemTrader.h"

#define lpMenuMng Menu::GetInstance()

using ItemS = std::shared_ptr<Item>;

enum class MENU_TYPE
{
	SELECT,			// 選択画面
	ITEMPLUS,		// 結合画面(合成)
	ITEMMINUS,		// 分解画面
	MAX
};

enum class SELECT_ITEM
{
	ITEM1,
	ITEM2,
	ITEM3,
	MAX
};

struct Zorder
{
	static constexpr int furoshiki = 30;		// 風呂敷のzorder
	static constexpr int space = 40;			// 空白のzorder
	static constexpr int arrow = 150;			// 矢印のzorder
	static constexpr int item = 100;			// アイテムのzorder
};
class Menu
{
public:
	static Menu& GetInstance()
	{
		Create();
		
		return *sInstance;
	}
	static void Create(void)
	{
		if (sInstance == nullptr)
		{
			sInstance = new Menu;
		}
	}
	bool Update(void);
	bool GetMixFlag(void);
	void ItemDraw(int tmp, Vector2 pos, Vector2 offset,Vector2 stroffset,LAYER lay);
	COLOR_TYPE ColorPtr(int no);

private:
	Menu();
	~Menu();

	void (Menu::* type)(void);				// メニュー
	void SELECT(void);						// メニュー開いた状態
	void ItemPup(void);						// Itemの合成
	void ItemMup(void);						// Itemの分解

	void Item(SELECT_ITEM item);			// 選択場所を選択したあとの画面
	
	void SelectCount(int& select,int thumb,int count);								// 矢印の操作
	bool Mix(ItemSave& item1, ItemSave& item2, ItemSave& item3);			// 合成処理
	// Mixで使うレシピ
	bool Key(ItemSave & item1,ItemSave & item2);
	bool Vine(ItemSave&item1,ItemSave&item2);
	bool Dynamite(ItemSave& item1, ItemSave& item2);
	bool Hose(ItemSave& item1, ItemSave& item2);
	bool Bard(ItemSave& item1, ItemSave& item2);


	void Ins(int no,ITEM_TYPE itemtype, COLOR_TYPE colortype);
	// 画像描画まとめ
	void SelectDraw(void);						// Select画面での表示物
	void MixDraw(void);							// Mix画面での表示物
	void ItemSelectD(int no);					// 決定と戻る。それと風呂敷などのDraw
	void ItemSelectDraw(void);
	// 固定値

	// 変数
	static Menu* sInstance;

	bool MixFlag;

	MENU_TYPE _type;



	int _select;							// 何番目か。 いろんなところで使う
	int _select2;							// 別方向の何番目かが欲しくなった時用

	bool push_select;						// メニュー決定
	bool _start;							// Updateが呼ばれた時点か1周した後かのふらぐ

	Vector2 _cpos;							// カメラのpos
	Vector2 _offpush;						// 間隔

	SELECT_ITEM _selectNo;					// アイテム選択画面のどれを選んでいるか。
	

	static constexpr int _asize = 3;			// アイテムが選択できるarrayの大きさ
	std::array<std::pair<ItemSave, int>,_asize> _sItem;		// アイテム合成のための枠　1つめに2つめのアイテムを混ぜる 3つめは設計図を入れる
	Zorder _zorder;
	Vector2 tmpos;		// ScreenSize
	Vector2 tmpcpos;	// centerpos

	Vector2 _count;
};

