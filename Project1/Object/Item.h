#pragma once
#include "Object.h"
#include "../common/Vector2.h"

enum class COLOR_TYPE :int
{
	BLACK = 0x000000,
	RED = 0xff0000,				// 赤
	GREEN = 0x00ff00,			// 緑
	BLUE = 0x0000ff,			// 青
	YELLOW = 0xffff00,			// イエロー
	MAGENTA = 0xff00ff,			// マゼンタ
	CYAN = 0x00ffff,			// シアン
	WHITE = 0xffffff,
	MAX = 0xffffff+1			// 最高値
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

	void SetBagNo(int no);
	int GetBagNo(void);
	const void setItemTypeNo(int book,int stone);
	const std::pair<int, int> getItemTypeNo(void);

	std::pair<ITEM_TYPE, COLOR_TYPE> getItemType(void);
	void ChangeType(ITEM_TYPE item, COLOR_TYPE color);
	void ChangeDir(DIR dir);

private:
	void Init(void);
	ITEM_TYPE _itemtype;
	COLOR_TYPE _colortype;
	int _bagNo;

	int _book;				// 本の番号　本でなければ-1
	int _stone;				// 石の番号　石でなければ-1
};

