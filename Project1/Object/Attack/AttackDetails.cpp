#include "AttackDetails.h"
#include <DxLib.h>
#include <cassert>

AttackDetails& AttackDetails::GetInstance(void)
{
	static AttackDetails atd;
	return atd;
}

const std::array<std::array<std::unique_ptr<Detail>, ATTACK_TYPE_MAX>, static_cast<int>(COLOR::MAX)>& AttackDetails::GetDetailsAll(void)
{
	return _details;
}

const std::unique_ptr<Detail> & AttackDetails::GetDetail(int color, int type)
{
	assert(color >= 0 || color < static_cast<int>(COLOR::MAX));
	assert(type >= 0 || type < ATTACK_TYPE_MAX);

	return _details[color][type];
}

AttackDetails::AttackDetails()
{
	for (auto& dt : _details)
	{
		for (auto& indt : dt)
		{
			indt.reset(new Detail());
		}
	}
	LoadAttackData();
}

void AttackDetails::LoadAttackData(void)
{
	int fp, pathfp;
	fp = FileRead_open("data/attack_data.txt");
	pathfp = FileRead_open("data/magic_icon_path.txt");

	assert(fp != -1);

	char name[32];
	char desc[32];
	int mp;
	char path[64];

	for (auto& col : _details)
	{
		for (auto& type : col)
		{
			FileRead_scanf(fp, "%s %d %s\n", name, &mp, desc);
			FileRead_scanf(pathfp, "%s", path);
			type->_name = name;
			type->_magicPoint = mp;
			type->_desc = desc;
			type->_handle = LoadGraph(path);
		}
	}
	
	FileRead_close(fp);
	FileRead_close(pathfp);
}
