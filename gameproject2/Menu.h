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
	void SELECT(void);				// ���j���[�J�������
	void (Menu::*type)(void);				// ���j���[�̎��ɑI��Update

	void ItemPup(void);		// Item�̍���
	void ItemMup(void);		// Item�̕���

	void Start(bool *a);
	void End(bool *a);

	static Menu* sInstance;
	MENU_TYPE _type;
	int _select;

	bool push_select;	// ���j���[����
	bool _start;		// Update���Ă΂ꂽ���_��1�������ォ�̂ӂ炮
};

