#include "AttackDetails.h"
#include <DxLib.h>
#include <cassert>
#include <vector>

namespace
{
	const char* magicname[static_cast<int>(COLOR::MAX) * ATTACK_TYPE_MAX] = 
	{
		"黒1", "黒2", "黒3", 
		"ファイア"			, "ボム"				, "バリア",
		"くだもののちから"	, "スーパージャンプ"	, "バリア",
		"サンダー"			, "スパーク"			, "黄3",
		"バブル"			, "ウルトラダッシュ"	, "バリア",
		"ポイズンミスト"	, "せいめいのき"		, "紫3",
		"アイス"			, "フリーズ"			, "水色3",
		"ジャッジメント"	, "オーバードライブ"	, "クロノレジスタンス",
	};
}

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
	int mp_fp, mc_fp, pathfp;
	mp_fp = FileRead_open("data/mp_data.dat");
	mc_fp = FileRead_open("data/mp_cooltime.dat");
	pathfp = FileRead_open("data/magic_icon_path.txt");

	assert(mp_fp != -1);

	std::vector<uint8_t> mp;
	mp.resize(24);
	FileRead_read(mp.data(), mp.size(), mp_fp);

	std::vector<uint8_t> mc;
	mc.resize(24);
	FileRead_read(mc.data(), mc.size(), mc_fp);

	char path[64];

	for (int i = 0; i < static_cast<int>(COLOR::MAX); i++)
	{
		for (int j = 0; j < ATTACK_TYPE_MAX; j++)
		{
			FileRead_scanf(pathfp, "%s", path);
			_details[i][j]->_magicPoint = mp[i * ATTACK_TYPE_MAX + j];
			_details[i][j]->_cooltime = mc[i * ATTACK_TYPE_MAX + j];
			_details[i][j]->_name = magicname[i * ATTACK_TYPE_MAX + j];
			_details[i][j]->_handle = LoadGraph(path);
		}
	}
	
	FileRead_close(mp_fp);
	FileRead_close(mc_fp);
	FileRead_close(pathfp);
}
