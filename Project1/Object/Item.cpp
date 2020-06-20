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
	_colortype = COLOR::BLACK;
	_image[0] = "error";
	_image[1] = "error";
}

Item::Item(Vector2 pos, ITEM_TYPE itemtype,COLOR colortype,int no,int stage)
{
	_book = -1;
	_stone = -1;
	_tool = -1;
	_type = OBJ_TYPE::ITEM;
	_pos = pos;
	_itemtype = itemtype;
	_colortype = colortype;
	_zOrder = 201;
	_bagNo = no;
	_stage = stage;

	save.bagNo = _bagNo;
	save.book = _book;
	save.tool = _tool;
	save.colortype = colortype;
	save.itemtype = itemtype;
	save.hp = -1;
	save.image[0] = "error";
	save.image[1] = "error";
	save.pos = _pos;
	save.stone = _stone;

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

std::pair<ITEM_TYPE, COLOR> Item::getItemType(void)
{
	return {_itemtype, _colortype};
}

void Item::ChangeType(ITEM_TYPE item,COLOR color)
{
	_itemtype = item;
	_colortype = color;

	Init();
}

void Item::ChangeDir(DIR dir)
{
	_state_dir.second = dir;
}

ItemSave &Item::ReturnSave(void)
{
	setSave();
	return save;
}

void Item::setSave(void)
{
	save.bagNo = _bagNo;
	save.book = _book;
	save.tool = _tool;
	save.colortype = _colortype;
	save.hp = _hp;
	save.image[0] = _image[0];
	save.image[1] = _image[1];
	save.itemtype = _itemtype;
	save.pos = _pos;
	save.stone = _stone;
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
		case COLOR::BLUE:
			_image[0] = "BlueBook";
			data.emplace_back(lpImageMng.getImage(_image[0])[0],0);
			break;
		case COLOR::GREEN:
			_image[0] = "GreenBook";
			data.emplace_back(lpImageMng.getImage(_image[0])[0], 0);
			break;
		case COLOR::RED:
			_image[0] = "RedBook";
			data.emplace_back(lpImageMng.getImage(_image[0])[0], 0);
			break;
		default:
			break;
		}
		break;
	case ITEM_TYPE::STONE:
		switch (_colortype)
		{
		case COLOR::BLACK:
			break;
		case COLOR::BLUE:
			_image[0] = "BlueStone";
			data.emplace_back(lpImageMng.getImage(_image[0])[0], 0);
			break;
		case COLOR::CYAN:
			_image[0] = "CyanStone";
			data.emplace_back(lpImageMng.getImage(_image[0])[0], 0);
			break;
		case COLOR::GREEN:
			_image[0] = "GreenStone";
			data.emplace_back(lpImageMng.getImage(_image[0])[0], 0);
			break;
		case COLOR::MAGENTA:
			_image[0] = "MagentaStone";
			data.emplace_back(lpImageMng.getImage(_image[0])[0], 0);
			break;
		case COLOR::RED:
			_image[0] = "RedStone";
			data.emplace_back(lpImageMng.getImage(_image[0])[0], 0);
			break;
		case COLOR::YELLOW:
			_image[0] = "YellowStone";
			data.emplace_back(lpImageMng.getImage(_image[0])[0], 0);
			break;
		case COLOR::WHITE:
			break;
		}
		break;
	case ITEM_TYPE::TOOL:
		switch (_colortype)
		{
		case COLOR::BLACK:
			break;
		case COLOR::RED:
			_image[0] = "530";
			data.emplace_back(lpImageMng.getImage(_image[0])[0], 0);
			break;
		case COLOR::GREEN:
			_image[0] = "531";
			data.emplace_back(lpImageMng.getImage(_image[0])[0], 0);
			break;
		case COLOR::BLUE:
			_image[0] = "532";
			data.emplace_back(lpImageMng.getImage(_image[0])[0], 0);
			break;
		case COLOR::YELLOW:
			_image[0] = "533";
			data.emplace_back(lpImageMng.getImage(_image[0])[0], 0);
			break;
		case COLOR::MAGENTA:
			_image[0] = "534";
			data.emplace_back(lpImageMng.getImage(_image[0])[0], 0);
			break;
		case COLOR::CYAN:
			_image[0] = "535";
			data.emplace_back(lpImageMng.getImage(_image[0])[0], 0);
			break;
		case COLOR::WHITE:
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
	switch (_itemtype)
	{
	case ITEM_TYPE::BOOK:
		break;
	case ITEM_TYPE::STONE:

		switch (_colortype)
		{
		case COLOR::BLACK:
			break;
		case COLOR::BLUE:
			_image[1] = "SBlueStone";
			data.emplace_back(lpImageMng.getImage(_image[1])[0], 0);
			break;
		case COLOR::CYAN:
			_image[1] = "SCyanStone";
			data.emplace_back(lpImageMng.getImage(_image[1])[0], 0);
			break;
		case COLOR::GREEN:
			_image[1] = "SGreenStone";
			data.emplace_back(lpImageMng.getImage(_image[1])[0], 0);
			break;
		case COLOR::MAGENTA:
			_image[1] = "SMagentaStone";
			data.emplace_back(lpImageMng.getImage(_image[1])[0], 0);
			break;
		case COLOR::RED:
			_image[1] = "SRedStone";
			data.emplace_back(lpImageMng.getImage(_image[1])[0], 0);
			break;
		case COLOR::YELLOW:
			_image[1] = "SYellowStone";
			data.emplace_back(lpImageMng.getImage(_image[1])[0], 0);
			break;
		case COLOR::WHITE:
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

