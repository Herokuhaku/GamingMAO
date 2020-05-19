#include "Item.h"
#include "../Graphic/ImageMng.h"
#include "../Scene/SceneMng.h"

Item::Item()
{
}

Item::Item(Vector2 pos, ITEM_TYPE itemtype,COLOR_TYPE colortype,int no)
{
	_book = 0;
	_stone = 0;
	_type = OBJ_TYPE::ITEM;
	_pos = pos;
	_itemtype = itemtype;
	_colortype = colortype;
	_zOrder = 201;
	_bagNo = no;

	Init();
}

Item::~Item()
{

}

void Item::Update(void)
{
	// 効果のあるアイテムを動かす用
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

	lpImageMng.AddBackDraw({ _anmMap[_state_dir][_anmFlame].first, _pos.x, _pos.y - _drawOffset_y, 1.0, _rad, lay, _zOrder, DX_BLENDMODE_NOBLEND, 0 });
}

void Item::SetBagNo(int no)
{
	_bagNo = no;
	return;
}

int Item::GetBagNo(void)
{
	return _bagNo;
}

const void Item::setItemTypeNo(int book,int stone)
{
	_stone = stone;
	_book = book;

	return ;
}

std::pair<ITEM_TYPE, COLOR_TYPE> Item::getItemType(void)
{
	return {_itemtype, _colortype};
}

void Item::ChangeType(ITEM_TYPE item,COLOR_TYPE color)
{
	_itemtype = item;
	_colortype = color;

	AnmVec data;

	_anmMap.clear();
	data.clear();

	switch (_colortype)
	{
	case COLOR_TYPE::CYAN:
		lpImageMng.getImage("image/item/Cyan_Stone.png", "CyanStone");
		data.emplace_back(lpImageMng.getImage("CyanStone")[0], 0);
		break;
	case COLOR_TYPE::MAGENTA:
		lpImageMng.getImage("image/item/Magenta_Stone.png", "MagentaStone");
		data.emplace_back(lpImageMng.getImage("MagentaStone")[0], 0);
		break;
	case COLOR_TYPE::YELLOW:
		lpImageMng.getImage("image/item/Yellow_Stone.png", "YellowStone");
		data.emplace_back(lpImageMng.getImage("YellowStone")[0], 0);
		break;
	default:
		break;
	}
	if (data.size() == 0)
	{
		return;
	}
	setAnm({ OBJ_STATE::NORMAL, DIR::RIGHT }, data);			// dirの初期値はRIGHTなのを覚えておく(OBJのコンストラクタで初期化)
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
		case COLOR_TYPE::BLUE:
			lpImageMng.getImage("image/item/Blue_Book.png", "BlueBook");
			data.emplace_back(lpImageMng.getImage("BlueBook")[0],0);
			break;
		case COLOR_TYPE::GREEN:
			break;
		case COLOR_TYPE::RED:
			break;
		default:
			break;
		}
		break;
	case ITEM_TYPE::STONE:

		switch (_colortype)
		{
		case COLOR_TYPE::BLACK:
			break;
		case COLOR_TYPE::BLUE:
			lpImageMng.getImage("image/item/Blue_Stone.png", "BlueStone");
			data.emplace_back(lpImageMng.getImage("BlueStone")[0], 0);
			break;
		case COLOR_TYPE::CYAN:
			lpImageMng.getImage("image/item/CYAN_Stone.png", "CyanStone");
			data.emplace_back(lpImageMng.getImage("CyanStone")[0], 0);
			break;
		case COLOR_TYPE::GREEN:
			lpImageMng.getImage("image/item/Green_Stone.png", "GreenStone");
			data.emplace_back(lpImageMng.getImage("GreenStone")[0], 0);
			break;
		case COLOR_TYPE::MAGENTA:
			lpImageMng.getImage("image/item/Magenta_Stone.png", "MagentaStone");
			data.emplace_back(lpImageMng.getImage("MagentaStone")[0], 0);
			break;
		case COLOR_TYPE::RED:
			lpImageMng.getImage("image/item/Red_Stone.png", "RedStone");
			data.emplace_back(lpImageMng.getImage("RedStone")[0], 0);
			break;
		case COLOR_TYPE::YELLOW:
			lpImageMng.getImage("image/item/Yellow_Stone.png", "YellowStone");
			data.emplace_back(lpImageMng.getImage("YellowStone")[0], 0);
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

