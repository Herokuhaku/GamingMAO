#pragma once
#include "MenuBase.h"
#include "../Manage/ItemTrader.h"
//#include "../Manage/COLOR.h"

struct Zorder
{
	static constexpr int furoshiki = 30;		// ���C�~��zorder
	static constexpr int space = 40;			// �󔒂�zorder
	static constexpr int arrow = 150;			// ����zorder
	static constexpr int item = 100;			// �A�C�e����zorder
};

enum class SELECT_ITEM
{
	ITEM1,
	ITEM2,
	ITEM3,
	MAX
};

class ItemMenu :
	public MenuBase
{
public:
	ItemMenu() = default;
	ItemMenu(std::shared_ptr<MenuExecuter> exe, std::shared_ptr<AudioContainer> audio);
	~ItemMenu();

	void Update(void);
	void Draw(void);
private:
	bool Mix(ItemSave& item1, ItemSave& item2, ItemSave& item3);			// ��������
	// Mix���V�s(���Ƃł܂Ƃ߂邩��)

	bool Dynamite(ItemSave& item1, ItemSave& item2);		// �_�C�i�}�C�g	(�ԐF)	���b�h
	bool Vine(ItemSave& item1, ItemSave& item2);			// ��			(�ΐF)	�O���[��
	bool Bard(ItemSave& item1, ItemSave& item2);			// ��			(�F)	�u���[
	bool Key(ItemSave& item1, ItemSave& item2);				// ��			(���F)	�C�G���[
	bool Powder(ItemSave& item1, ItemSave& item2);			// ��			(���F)	�}�[���^
	bool Hose(ItemSave& item1, ItemSave& item2);			// �z�[�X		(���F)	�V�A��

	void ItemSelectD(int no);					// ����Ɩ߂�B����ƕ��C�~�Ȃǂ�Draw

	void SelectCount(int& select, int thumb, int count);			// ���̑���
	void MixDraw(void);
	void ItemSelectDraw(void);
	void Item(SELECT_ITEM item);
	bool MixFlag;

	void Ins(int no, ITEM_TYPE itemtype, COLOR colortype);		// �A�C�e����I���ɓ����

	static constexpr int _asize = 3;							// �A�C�e�����I���ł���array�̑傫��
	std::array<std::pair<ItemSave, int>, _asize> _sItem;		// �A�C�e�������̂��߂̘g�@1�߂�2�߂̃A�C�e���������� 3�߂͐݌v�}������
	Zorder _zorder;
	int _select;							// ���Ԗڂ��B �����ȂƂ���Ŏg��
	int _select2;							// �ʕ����̉��Ԗڂ����~�����Ȃ������p

	Vector2 _cpos;							// �J������pos
	SELECT_ITEM _selectNo;					// �A�C�e���I����ʂ̂ǂ��I��ł��邩�B

	Vector2 _count;	
	Vector2 _offpush;						// �Ԋu

	COLOR ColorPtr(int no);
	ItemSave mix_;

	std::shared_ptr<MenuExecuter> exe_;
};

