#pragma once
#include <vector>
#include "../common/Vector2.h"

#define lpMenuMng Menu::GetInstance()

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
private:

	Menu();
	~Menu();

	bool MixFlag;
	void (Menu::* type)(void);				// メニュー

	void SELECT(void);						// メニュー開いた状態
	void ItemPup(void);						// Itemの合成
	void ItemMup(void);						// Itemの分解

	void Item1(void);
	void Item2(void);
	void Item3(void);


	// 
	void Start(bool *a);
	void End(bool *a);

	// 画像描画まとめ
	void SelectDraw(void);					// Select画面での表示物
	void MixDraw(void);						// Mix画面での表示物
	
	// 変数
	static Menu* sInstance;

	Vector2 _offpush;						// 間隔
	MENU_TYPE _type;
	int _select;

	bool push_select;						// メニュー決定
	bool _start;							// Updateが呼ばれた時点か1周した後かのふらぐ

	Vector2D _cpos;

	SELECT_ITEM _selectNo;
	
	int Item[3];


};

