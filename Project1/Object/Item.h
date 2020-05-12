#pragma once
#include "Object.h"
#include "../common/Vector2.h"

enum class COLOR_TYPE :int
{
	BLACK = 0x000000,
	RED = 0xff0000,			// 赤の魔石
	GREEN = 0x00ff00,			// 緑の魔石
	BLUE = 0x0000ff,			// 青の魔石
	YELLOW = 0xffff00,			// イエローの魔石
	MAGENTA = 0xff00ff,			// マゼンタの魔石
	CYAN = 0x00ffff,			// シアンの魔石
	WHITE = 0xffffff,
	MAX = 0xfffff				// 最高値
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
	Item(Vector2 pos,ITEM_TYPE itemtype,COLOR_TYPE colortype,int no);	// pos,itemtype,colortype,生成番号
	~Item();

	void Update(void);
	void Draw(void);
	void OLDraw(LAYER lay);		// 違うレイヤーに入れたいとき用
private:
	void Init(void);
	ITEM_TYPE _itemtype;
	COLOR_TYPE _colortype;
	int _bagno;
};

