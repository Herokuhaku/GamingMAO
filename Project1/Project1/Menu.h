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

	void SELECT(void);				// ���j���[�J�������
	void (Menu::*type)(void);				// ���j���[�̎��ɑI��Update

	void ItemPup(void);		// Item�̍���
	void ItemMup(void);		// Item�̕���

	static Menu* sInstance;
	MENU_TYPE _type;
	int _select;

	bool push_select;	// ���j���[����

	
	bool start;		// Update���Ă΂ꂽ���_��1�������ォ�̂ӂ炮
};

