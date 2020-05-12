#pragma once
#include "Object.h"
#include "../common/Vector2.h"

enum class COLOR_TYPE :int
{
	BLACK = 0x000000,
	RED = 0xff0000,			// �Ԃ̖���
	GREEN = 0x00ff00,			// �΂̖���
	BLUE = 0x0000ff,			// �̖���
	YELLOW = 0xffff00,			// �C�G���[�̖���
	MAGENTA = 0xff00ff,			// �}�[���^�̖���
	CYAN = 0x00ffff,			// �V�A���̖���
	WHITE = 0xffffff,
	MAX = 0xfffff				// �ō��l
};

enum class ITEM_TYPE
{
	BOOK,
	STONE,
};
class Item :
	public Object
{
public:
	Item();
	Item(Vector2 pos,ITEM_TYPE itemtype,COLOR_TYPE colortype,int no);	// pos,itemtype,colortype,�����ԍ�
	~Item();

	void Update(void);
	void Draw(void);
	void OLDraw(LAYER lay);		// �Ⴄ���C���[�ɓ��ꂽ���Ƃ��p
private:
	void Init(void);
	ITEM_TYPE _itemtype;
	COLOR_TYPE _colortype;
	int _bagno;
};

