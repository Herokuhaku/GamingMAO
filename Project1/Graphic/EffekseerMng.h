#pragma once
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include <map>
#include <vector>
#include <tuple>
#include <type_traits>
#include "../Object/DIR.h"


enum class EFK_DATA : int
{
	HD,
	TIME,
	POS,
	OFFSET,
	DIR
};

#define lpEffectMng EffekseerMng::getInstance()

class EffekseerMng
{
public:
	static EffekseerMng& getInstance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new EffekseerMng();
		}
		return *sInstance;
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}

	int getEffect(const std::string& key);														// キーを渡すとエフェクトのハンドルを返す
	int getEffect(const std::string& filename, const std::string& key, const float& exRate);	// ファイル名で読み込み、キーに入れる

	// efcHd:ハンドル time:時間 pos_x,pos_y:座標 offset_x,pffset_y:オフセット dir:向き 
	int playEffect(const int efcHd, const int time, int* pos_x, int* pos_y, int offset_x, int offset_y, DIR* dir);			
	void stopEffect(int playEfcHd);
	void stopEffectAll(void);																	// すべてのエフェクトを停止する

	void UpdateEffekseer(void);																	// 再生中のエフェクトの更新

private:
	static EffekseerMng* sInstance;

	static std::map<std::string, int> _effectMap;			// エフェクトのハンドル
	
	std::vector<std::tuple<int, int, std::pair<int*,int*>, std::pair<int,int>, DIR*>> _effectList;	// 再生中のエフェクトのリスト ハンドル,時間,座標,オフセット,向き

	EffekseerMng();
	~EffekseerMng();
};

