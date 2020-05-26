#pragma once
#include <vector>
#include <memory>
#include <map>
#include "../Object/Object.h"
#include "../Object/Item.h"

#define lpTradeMng ItemTrader::GetInstance()

#define BAGOFF_X 200
#define BAGOFF_Y 200

class ItemTrader
{
public:
	static ItemTrader &GetInstance()
	{
		Create();

		return *sInstance;
	}

	static void Create(void)
	{
		if (sInstance == nullptr)
		{
			sInstance = new ItemTrader();
		}
	}
	
	void Draw(void);
	void BagDraw(Vector2D pos,LAYER lay, Vector2 off , Vector2D rad);
	COLOR_TYPE Trade(COLOR_TYPE color1, COLOR_TYPE color2);
	bool TradeCheck(COLOR_TYPE color1, COLOR_TYPE color2);
	const void SetItemList(Vector2 pos, ITEM_TYPE itype,COLOR_TYPE ctype, int stage);
	bool NoReturn(int no);
	ItemSave& ReturnBag(int no);

	void DeleteItem(ItemSave& item);
	void AddBag(void);
	void AddBag(ItemSave &save);




	
	std::pair<int, int> getcount(void);	// �{,�΂̐���Ԃ�
	
	std::array<int, 6> getrock(void);	// ���F�̐΂������邩��Ԃ� //���Ԃ� ��,��,��,��,�}�[���^,�V�A��

private:
	ItemTrader();
	~ItemTrader();
	static ItemTrader* sInstance;
	std::vector<std::shared_ptr<Item>>_ItemList;				// �����Ă���A�C�e��
//	std::vector<std::pair<std::shared_ptr<Item>,int>> _ItemBag;	// �����Ă���A�C�e��

	void BagTypeSort(void);			// �o�b�O�̒��̐΂Ɩ{�̐��𐔂���
	void BagTypeCount(void);		// ���F�̐΂������邩������
	void BagNoSort(void);			// �o�b�O�̒��̂��̂����Ԃɔԍ���t����

	const char* ChangeName(ITEM_TYPE _itemtype, COLOR_TYPE _colortype);
	std::array<int,6> rock;										// �΂̎�ނƂ��̐� //���Ԃ� ��,��,��,��,�}�[���^,�V�A��

	int color;
	Vector2 _pos;
	int _stone;
	int _book;
	std::vector<std::pair<ItemSave, int>> _IBag;
	ItemSave save;
};

