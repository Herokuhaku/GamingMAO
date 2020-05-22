#pragma once
#include "Object.h"
#include "../common/Vector2.h"

enum class COLOR_TYPE :int
{
	BLACK = 0x000000,
	RED = 0xff0000,				// ��
	GREEN = 0x00ff00,			// ��
	BLUE = 0x0000ff,			// ��
	YELLOW = 0xffff00,			// �C�G���[
	MAGENTA = 0xff00ff,			// �}�[���^
	CYAN = 0x00ffff,			// �V�A��
	WHITE = 0xffffff,
	MAX = 0xffffff+1			// �ō��l
};


enum class ITEM_TYPE
{
	BOOK,
	STONE,
	NON,
};

typedef struct
{
	ITEM_TYPE itemtype;
	COLOR_TYPE colortype;
	Vector2 pos;			// ���W(x:���S�@y:����)
	int bagNo;				// �o�b�O�̒��ŉ��Ԗڂ�
	int book;				// �{�̔ԍ��@�{�łȂ����-1
	int stone;				// �΂̔ԍ��@�΂łȂ����-1
	int hp;					// �̗�
	const char* image[2];	// �摜�̎��
}ItemSave;

class Item :
	public Object
{
public:
	Item();
	Item(Vector2 pos,ITEM_TYPE itemtype,COLOR_TYPE colortype,int no,int stage);	// pos,itemtype,colortype,�����ԍ�
	~Item();

	void Update(void);
	void Draw(void);
	void OLDraw(LAYER lay);		// �Ⴄ���C���[�ɓ��ꂽ���Ƃ��p

	void SetBagNo(int no);
	int GetBagNo(void);
	const void setItemTypeNo(int book,int stone);
	const std::pair<int, int> getItemTypeNo(void);

	std::pair<ITEM_TYPE, COLOR_TYPE> getItemType(void);
	void ChangeType(ITEM_TYPE item, COLOR_TYPE color);
	void ChangeDir(DIR dir);

	ItemSave& ReturnSave(void);
	void setSave(void);
private:
	void Init(void);
	ITEM_TYPE _itemtype;
	COLOR_TYPE _colortype;
	int _bagNo;

	int _book;				// �{�̔ԍ��@�{�łȂ����-1
	int _stone;				// �΂̔ԍ��@�΂łȂ����-1
	const char* _image[2];	// �摜�ԍ�		// 0 �ʏ�,1 ��
	ItemSave save;
};

