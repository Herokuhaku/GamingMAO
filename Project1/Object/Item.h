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
	NON,
};

typedef struct
{
	ITEM_TYPE itemtype;
	COLOR_TYPE colortype;
	Vector2 pos;			// 座標(x:中心　y:下辺)
	int bagNo;				// バッグの中で何番目か
	int book;				// 本の番号　本でなければ-1
	int stone;				// 石の番号　石でなければ-1
	int hp;					// 体力
	const char* image[2];	// 画像の種類
}ItemSave;

class Item :
	public Object
{
public:
	Item();
	Item(Vector2 pos,ITEM_TYPE itemtype,COLOR_TYPE colortype,int no,int stage);	// pos,itemtype,colortype,生成番号
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

	ItemSave& ReturnSave(void);
	void setSave(void);
private:
	void Init(void);
	ITEM_TYPE _itemtype;
	COLOR_TYPE _colortype;
	int _bagNo;

	int _book;				// 本の番号　本でなければ-1
	int _stone;				// 石の番号　石でなければ-1
	const char* _image[2];	// 画像番号		// 0 通常,1 小
	ItemSave save;
};

