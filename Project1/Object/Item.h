#pragma once
#include "Object.h"
#include "../common/Vector2.h"
#include "../Manage/COLOR.h"
#include "../Graphic/LAYER.h"


enum class ITEM_TYPE
{
	BOOK,
	STONE,
	TOOL,
	NON,
};

struct ItemSave
{
	ITEM_TYPE itemtype;
	COLOR colortype;
	Vector2 pos;			// ���W(x:���S�@y:����)
	int bagNo;				// �o�b�O�̒��ŉ��Ԗڂ�
	int book;				// �{�̔ԍ��@�{�łȂ����-1
	int stone;				// �΂̔ԍ��@�΂łȂ����-1
	int tool;
	int hp;					// �̗�
	const char* image[2];	// �摜�̎��
	bool use;
};

class Item :
	public Object
{
public:
	Item();
	Item(Vector2 pos,ITEM_TYPE itemtype,COLOR colortype,int no,int stage);	// pos,itemtype,colortype,�����ԍ�
	~Item();

	void Update(void);
	void Draw(void);
	void OLDraw(LAYER lay);		// �Ⴄ���C���[�ɓ��ꂽ���Ƃ��p

	void SetBagNo(int no);
	int GetBagNo(void);
	const void setItemTypeNo(int book,int stone);
	const std::pair<int, int> getItemTypeNo(void);

	std::pair<ITEM_TYPE, COLOR> getItemType(void);
	void ChangeType(ITEM_TYPE item, COLOR color);
	void ChangeDir(DIR dir);

	ItemSave &ReturnSave(void);
	int GetStage(void);
	void setSave(void);
private:
	void Init(void);
	ITEM_TYPE _itemtype;
	COLOR _colortype;
	int _bagNo;

	int _book;				// �{�̔ԍ��@�{�łȂ����-1
	int _stone;				// �΂̔ԍ��@�΂łȂ����-1
	int _tool;
	const char* _image[2];	// �摜�ԍ�		// 0 �ʏ�,1 ��
	ItemSave save;

	double _vel;

	static constexpr double G_ACC_NORMAL = 0.4;
	static constexpr double VEL_MAX = 9.0;


};

