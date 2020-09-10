#pragma once
#include "MenuBase.h"
#include "../Manage/ItemTrader.h"
//#include "../Manage/COLOR.h"

struct Zorder
{
	static constexpr int furoshiki = 30;		// 風呂敷のzorder
	static constexpr int space = 40;			// 空白のzorder
	static constexpr int arrow = 150;			// 矢印のzorder
	static constexpr int item = 100;			// アイテムのzorder
};

enum class SELECT_ITEM
{
	ITEM1,
	ITEM2,
	ITEM3,
	MAX
};

class ItemMenu :
	public MenuBase
{
public:
	ItemMenu() = default;
	ItemMenu(std::shared_ptr<MenuExecuter> exe, std::shared_ptr<AudioContainer> audio);
	~ItemMenu();

	void Update(void);
	void Draw(void);
private:
	bool Mix(ItemSave& item1, ItemSave& item2, ItemSave& item3);			// 合成処理
	// Mixレシピ(あとでまとめるかも)

	bool Dynamite(ItemSave& item1, ItemSave& item2);		// ダイナマイト	(赤色)	レッド
	bool Vine(ItemSave& item1, ItemSave& item2);			// 蔓			(緑色)	グリーン
	bool Bard(ItemSave& item1, ItemSave& item2);			// 鳥			(青色)	ブルー
	bool Key(ItemSave& item1, ItemSave& item2);				// 鍵			(黄色)	イエロー
	bool Powder(ItemSave& item1, ItemSave& item2);			// 粉			(紫色)	マゼンタ
	bool Hose(ItemSave& item1, ItemSave& item2);			// ホース		(水色)	シアン

	void ItemSelectD(int no);					// 決定と戻る。それと風呂敷などのDraw

	void SelectCount(int& select, int thumb, int count);			// 矢印の操作
	void MixDraw(void);
	void ItemSelectDraw(void);
	void Item(SELECT_ITEM item);
	bool MixFlag;

	void Ins(int no, ITEM_TYPE itemtype, COLOR colortype);		// アイテムを選択に入れる

	static constexpr int _asize = 3;							// アイテムが選択できるarrayの大きさ
	std::array<std::pair<ItemSave, int>, _asize> _sItem;		// アイテム合成のための枠　1つめに2つめのアイテムを混ぜる 3つめは設計図を入れる
	Zorder _zorder;
	int _select;							// 何番目か。 いろんなところで使う
	int _select2;							// 別方向の何番目かが欲しくなった時用

	Vector2 _cpos;							// カメラのpos
	SELECT_ITEM _selectNo;					// アイテム選択画面のどれを選んでいるか。

	Vector2 _count;	
	Vector2 _offpush;						// 間隔

	COLOR ColorPtr(int no);
	ItemSave mix_;

	std::shared_ptr<MenuExecuter> exe_;
};

