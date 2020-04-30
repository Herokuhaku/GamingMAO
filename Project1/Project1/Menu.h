#pragma once
#include <vector>

#define lpMenu Menu::GetInstance()

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
	Menu();
	~Menu();
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

	void SELECT(void);				// メニュー開いた状態
	void (Menu::*type)(void);				// メニューの次に選んだUpdate

	void ItemPup(void);		// Itemの合成
	void ItemMup(void);		// Itemの分解

	static Menu* sInstance;
	MENU_TYPE _type;
	int _select;

	bool push_select;	// メニュー決定

	
	bool start;		// Updateが呼ばれた時点か1周した後かのふらぐ
};

