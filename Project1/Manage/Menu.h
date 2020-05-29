#pragma once
#include <vector>
#include <array>
#include "../common/Vector2.h"
#include "ItemTrader.h"

#define lpMenuMng Menu::GetInstance()

using ItemS = std::shared_ptr<Item>;

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

struct Zorder
{
	static constexpr int furoshiki = 30;		// ���C�~��zorder
	static constexpr int space = 40;			// �󔒂�zorder
	static constexpr int arrow = 150;			// ����zorder
	static constexpr int item = 100;			// �A�C�e����zorder
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

	void (Menu::* type)(void);				// ���j���[
	void SELECT(void);						// ���j���[�J�������
	void ItemPup(void);						// Item�̍���
	void ItemMup(void);						// Item�̕���

	void Item(SELECT_ITEM item);			// �I���ꏊ��I���������Ƃ̉��
	
	void SelectCount(int& select,int thumb,int count);								// ���̑���
	bool Mix(ItemSave& item1, ItemSave& item2, ItemSave& item3);			// ��������
	// Mix�Ŏg�����V�s
	bool Key(ItemSave & item1,ItemSave & item2);
	bool Vine(ItemSave&item1,ItemSave&item2);
	bool Dynamite(ItemSave& item1, ItemSave& item2);
	bool Hose(ItemSave& item1, ItemSave& item2);
	bool Bard(ItemSave& item1, ItemSave& item2);


	void Ins(int no,ITEM_TYPE itemtype, COLOR_TYPE colortype);
	// �摜�`��܂Ƃ�
	void SelectDraw(void);						// Select��ʂł̕\����
	void MixDraw(void);							// Mix��ʂł̕\����
	void ItemSelectD(int no);					// ����Ɩ߂�B����ƕ��C�~�Ȃǂ�Draw
	void ItemSelectDraw(void);
	// �Œ�l

	// �ϐ�
	static Menu* sInstance;

	bool MixFlag;

	MENU_TYPE _type;



	int _select;							// ���Ԗڂ��B �����ȂƂ���Ŏg��
	int _select2;							// �ʕ����̉��Ԗڂ����~�����Ȃ������p

	bool push_select;						// ���j���[����
	bool _start;							// Update���Ă΂ꂽ���_��1�������ォ�̂ӂ炮

	Vector2 _cpos;							// �J������pos
	Vector2 _offpush;						// �Ԋu

	SELECT_ITEM _selectNo;					// �A�C�e���I����ʂ̂ǂ��I��ł��邩�B
	

	static constexpr int _asize = 3;			// �A�C�e�����I���ł���array�̑傫��
	std::array<std::pair<ItemSave, int>,_asize> _sItem;		// �A�C�e�������̂��߂̘g�@1�߂�2�߂̃A�C�e���������� 3�߂͐݌v�}������
	Zorder _zorder;
	Vector2 tmpos;		// ScreenSize
	Vector2 tmpcpos;	// centerpos

	Vector2 _count;
};

