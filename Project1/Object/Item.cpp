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
	_bagNo = no;
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
//	lpImageMng.AddDraw({ lpImageMng.getImage("BlueBook")[0],_pos.x,lpSceneMng.GetcPos().y+100,0.0,LAYER::CHAR,100 });
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

int Item::GetBagNo(void)
{
	return _bagNo;
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
		break;
	case COLOR_TYPE::MAGENTA:
		break;
	case COLOR_TYPE::YELLOW:
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

