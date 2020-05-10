#pragma once
#include <vector>

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

	static Menu* sInstance;
	MENU_TYPE _type;
	int _select;

	bool push_select;	// メニュー決定
	bool _start;		// Updateが呼ばれた時点か1周した後かのふらぐ
};

