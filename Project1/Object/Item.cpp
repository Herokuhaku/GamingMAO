#include "Item.h"
#include "../Graphic/ImageMng.h"
#include "../Scene/SceneMng.h"

Item::Item()
{
	_bagNo = -1;
	_zOrder = -1;
	_book = -1;
	_stone = -1;
	_itemtype = ITEM_TYPE::BOOK;
	_colortype = COLOR_TYPE::BLACK;
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
}

const std::pair<int, int> Item::getItemTypeNo(void)
{
	return {_book, _stone};
}

std::pair<ITEM_TYPE, COLOR_TYPE> Item::getItemType(void)
{
	return {_itemtype, _colortype};
}

void Item::ChangeType(ITEM_TYPE item,COLOR_TYPE color)
{
	_itemtype = item;
	_colortype = color;

	Init();
}

void Item::ChangeDir(DIR dir)
{
	_state_dir.second = dir;
}

void Item::Init(void)
{
	_anmMap.clear();
	AnmVec data;
	data.clear();

	// 通常サイズ
	switch (_itemtype)
	{
	case ITEM_TYPE::BOOK:

		switch (_colortype)
		{
		case COLOR_TYPE::BLUE:
			data.emplace_back(lpImageMng.getImage("BlueBook")[0],0);
			break;
		case COLOR_TYPE::GREEN:
			data.emplace_back(lpImageMng.getImage("GreenBook")[0], 0);
			break;
		case COLOR_TYPE::RED:
			data.emplace_back(lpImageMng.getImage("RedBook")[0], 0);
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
			data.emplace_back(lpImageMng.getImage("BlueStone")[0], 0);
			break;
		case COLOR_TYPE::CYAN:
			data.emplace_back(lpImageMng.getImage("CyanStone")[0], 0);
			break;
		case COLOR_TYPE::GREEN:
			data.emplace_back(lpImageMng.getImage("GreenStone")[0], 0);
			break;
		case COLOR_TYPE::MAGENTA:
			data.emplace_back(lpImageMng.getImage("MagentaStone")[0], 0);
			break;
		case COLOR_TYPE::RED:
			data.emplace_back(lpImageMng.getImage("RedStone")[0], 0);
			break;
		case COLOR_TYPE::YELLOW:
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

	// 小サイズ
	// 通常サイズ
	switch (_itemtype)
	{
	case ITEM_TYPE::BOOK:
		break;
	case ITEM_TYPE::STONE:

		switch (_colortype)
		{
		case COLOR_TYPE::BLACK:
			break;
		case COLOR_TYPE::BLUE:
			data.emplace_back(lpImageMng.getImage("SBlueStone")[0], 0);
			break;
		case COLOR_TYPE::CYAN:
			data.emplace_back(lpImageMng.getImage("SCyanStone")[0], 0);
			break;
		case COLOR_TYPE::GREEN:
			data.emplace_back(lpImageMng.getImage("SGreenStone")[0], 0);
			break;
		case COLOR_TYPE::MAGENTA:

			data.emplace_back(lpImageMng.getImage("SMagentaStone")[0], 0);
			break;
		case COLOR_TYPE::RED:
			data.emplace_back(lpImageMng.getImage("SRedStone")[0], 0);
			break;
		case COLOR_TYPE::YELLOW:

			data.emplace_back(lpImageMng.getImage("SYellowStone")[0], 0);
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
	setAnm({ OBJ_STATE::NORMAL, DIR::LEFT }, data);		
}

