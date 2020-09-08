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
	Vector2 pos;			// 座標(x:中心　y:下辺)
	int bagNo;				// バッグの中で何番目か
	int book;				// 本の番号　本でなければ-1
	int stone;				// 石の番号　石でなければ-1
	int tool;
	int hp;					// 体力
	const char* image[2];	// 画像の種類
	bool use;
};

class Item :
	public Object
{
public:
	Item();
	Item(Vector2 pos,ITEM_TYPE itemtype,COLOR colortype,int no,int stage);	// pos,itemtype,colortype,生成番号
	~Item();

	void Update(void);
	void Draw(void);
	void OLDraw(LAYER lay);		// 違うレイヤーに入れたいとき用

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

	int _book;				// 本の番号　本でなければ-1
	int _stone;				// 石の番号　石でなければ-1
	int _tool;
	const char* _image[2];	// 画像番号		// 0 通常,1 小
	ItemSave save;

	double _vel;

	static constexpr double G_ACC_NORMAL = 0.4;
	static constexpr double VEL_MAX = 9.0;


};

