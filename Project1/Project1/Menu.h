#pragma once
#include <vector>
#include "common/Vector2.h"

#define lpMenuMng Menu::GetInstance()

enum class MENU_TYPE
{
	SELECT,
	ITEMPLUS,
	ITEMMINUS,
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

private:

	Menu();
	~Menu();
	void SELECT(void);				// メニュー開いた状態
	void (Menu::*type)(void);				// メニューの次に選んだUpdate

	void ItemPup(void);		// Itemの合成
	void ItemMup(void);		// Itemの分解

	void Start(bool *a);
	void End(bool *a);

	void SelectDraw(void);				// Select画面での表示物
	void MixDraw(void);					// Mix画面での表示物


	// 変数

	Vector2 _offpush;							// 間隔
	static Menu* sInstance;
	MENU_TYPE _type;
	int _select;

	bool push_select;	// メニュー決定
	bool _start;		// Updateが呼ばれた時点か1周した後かのふらぐ

	Vector2D _cpos;
};

