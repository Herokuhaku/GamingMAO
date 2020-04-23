#pragma once
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include <map>
#include <vector>
#include <tuple>


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
	int getEffect(const std::string& filename, const std::string& key, const float& exLate);	// ファイル名で読み込み、キーに入れる

	int playEffect(const int& efcHd, const int& time);											// efcHd:ハンドルとtime:時間　そのエフェクトを指定したフレーム再生
	void stopEffectAll(void);																	// すべてのエフェクトを停止する

	void UpdateEffekseer(void);																	// 再生中のエフェクトの更新

private:
	static EffekseerMng* sInstance;

	std::map<std::string, int> _effectMap;			// エフェクトのハンドル
	
	std::vector<std::pair<int, int>> _effectList;	// 再生中のエフェクトのリスト

	EffekseerMng();
	~EffekseerMng();

	void EffectMngInit(void);
};

