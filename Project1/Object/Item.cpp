#include "Item.h"
#include "../Graphic/ImageMng.h"
#include "../Scene/SceneMng.h"

Item::Item()
{
}

Item::Item(Vector2 pos, ITEM_TYPE itemtype,COLOR_TYPE colortype,int no)
{
	_type = OBJ_TYPE::ITEM;
	_pos = pos;
	_itemtype = itemtype;
	_colortype = colortype;
	_zOrder = 201;
	Init();

}

Item::~Item()
{

}

void Item::Update(void)
{
	Draw();
}

void Item::Draw(void)
{
	Object::Draw();
}

void Item::OLDraw(LAYER lay)
{
	if (!anmUpdate())
	{
		return;
	}

	lpImageMng.AddDraw({ _anmMap[_state_dir][_anmFlame].first, _pos.x, _pos.y - _drawOffset_y, _rad, lay, _zOrder });
}

void Item::Init(void)
{
	AnmVec data;
	data.clear();

	switch (_itemtype)
	{
	case ITEM_TYPE::BOOK:

		switch (_colortype)
		{
		case COLOR_TYPE::BLACK:
			break;
		case COLOR_TYPE::BLUE:
			data.emplace_back(lpImageMng.getImage("BlueBook")[0],0);
			break;
		case COLOR_TYPE::CYAN:
			break;
		case COLOR_TYPE::GREEN:
			break;
		case COLOR_TYPE::MAGENTA:
			break;
		case COLOR_TYPE::RED:
			break;
		case COLOR_TYPE::YELLOW:
			break;
		case COLOR_TYPE::WHITE:
			break;
		}
		break;
	case ITEM_TYPE::STONE:

		switch (_colortype)
		{
		case COLOR_TYPE::BLACK:
			break;
		case COLOR_TYPE::BLUE:
			break;
		case COLOR_TYPE::CYAN:
			break;
		case COLOR_TYPE::GREEN:
			break;
		case COLOR_TYPE::MAGENTA:
			break;
		case COLOR_TYPE::RED:
			break;
		case COLOR_TYPE::YELLOW:
			break;
		case COLOR_TYPE::WHITE:
			break;
		}
		break;
	}
	if (data.size() == 0)
	{
		return;
	}
	setAnm({ OBJ_STATE::NORMAL, DIR::RIGHT }, data);			// dirの初期値はRIGHTなのを覚えておく(OBJのコンストラクタで初期化)
}

