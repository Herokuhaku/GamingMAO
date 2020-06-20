#pragma once
#include <vector>
#include <array>
#include <memory>
#include <map>
#include "../Object/Object.h"
#include "../Object/Item.h"
#include "../Graphic/LAYER.h"

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
	static void Destroy(void)
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}
	
	void Draw(void);
	void BagDraw(Vector2D pos,LAYER lay, Vector2 off , Vector2D rad);
	void ToolDraw(Vector2 pos, LAYER lay, Vector2 off, Vector2D rad);

	void inTool(void);

	COLOR Trade(COLOR color1, COLOR color2);
	bool ColorTradeCheck(COLOR color1, COLOR color2);
	const void SetItemList(Vector2 pos, ITEM_TYPE itype,COLOR ctype, int stage);
	bool NoReturn(int no);
	ItemSave& ReturnBag(int no);

	void DeleteItem(ItemSave& item);
	void AddBag(void);
	void AddBag(ItemSave &save);

	int ReturnNo(ITEM_TYPE itemtype, COLOR color);
	bool ReBook(COLOR color);

	std::pair<int, int> getcount(void);	// �{,�΂̐���Ԃ�
	
	std::array<int, 6> getrock(void);	// ���F�̐΂������邩��Ԃ� //���Ԃ� ��,��,��,��,�}�[���^,�V�A��
	void ChangeCount(bool num);
	

private:
	ItemTrader();
	~ItemTrader();
	static ItemTrader* sInstance;
	std::vector<std::shared_ptr<Item>>_ItemList;				// �����Ă���A�C�e��
//	std::vector<std::pair<std::shared_ptr<Item>,int>> _ItemBag;	// �����Ă���A�C�e��

	void BagTypeSort(void);			// �o�b�O�̒��̐΂Ɩ{�̐��𐔂���
	void BagTypeCount(void);		// ���F�̐΂������邩������
	void BagNoSort(void);			// �o�b�O�̒��̂��̂����Ԃɔԍ���t����

	const char* ChangeName(ITEM_TYPE _itemtype, COLOR _colortype);
	std::array<int,6> rock;										// �΂̎�ނƂ��̐� //���Ԃ� ��,��,��,��,�}�[���^,�V�A��

	int color;
	Vector2 _pos;
	int _stone;
	int _book;
	int _tool;
	int _toolMax;
	std::vector<std::pair<ItemSave, int>> _IBag;
	std::vector<std::pair<ItemSave, int>> _ItemBag;
	ItemSave save;
	
	int _drawtool[5];
	static int _count;
};

