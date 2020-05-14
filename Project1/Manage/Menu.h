#pragma once
#include <vector>
#include <array>
#include "../common/Vector2.h"
#include "ItemTrader.h"

#define lpMenuMng Menu::GetInstance()

enum class MENU_TYPE
{
	SELECT,			// �I�����
	ITEMPLUS,		// �������(����)
	ITEMMINUS,		// �������
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
	void (Menu::* type)(void);				// ���j���[

	void SELECT(void);						// ���j���[�J�������
	void ItemPup(void);						// Item�̍���
	void ItemMup(void);						// Item�̕���

	void Item1(void);
	void Item2(void);
	void Item3(void);

	void ItemSelectD(void);					// ����Ɩ߂�B����ƕ��C�~�Ȃǂ�Draw

	// 
	void Start(bool *a);
	void End(bool *a);

	// �摜�`��܂Ƃ�
	void SelectDraw(void);					// Select��ʂł̕\����
	void MixDraw(void);						// Mix��ʂł̕\����
	
	void ItemSelectDraw(void);

	// �ϐ�
	static Menu* sInstance;

	Vector2 _offpush;						// �Ԋu
	MENU_TYPE _type;
	int _select;

	bool push_select;						// ���j���[����
	bool _start;							// Update���Ă΂ꂽ���_��1�������ォ�̂ӂ炮

	Vector2 _cpos;
	//Vector2 _pos;
	SELECT_ITEM _selectNo;
	
	static constexpr int _asize = 3;

	std::array<std::pair<std::shared_ptr<Item>, int>,_asize> _selectItem;

	Vector2 tmpos;
	Vector2 tmpcpos;	// centerpos;
};

