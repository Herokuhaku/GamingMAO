#pragma once
#include <unordered_map>
#include <string>


struct AudioContainer
{
public:
	// 音ファイルの読み込み
	// filename:ファイル名
	// key:キー
	// buffer_count:同時再生可能数
	void LoadSound(const std::string& filename, const std::string& key, const int& buffer_count);

	// 音ハンドルの取得
	// key:キー
	int GetSound(const std::string& key);

	// 音量変更
	// key:キー
	// volme:音量(0～255で 数が大きいほど音量も大きくなる)
	void ChangeVolume(const std::string& key, const int& volume);
private:
	std::unordered_map<std::string, int> _container;
};

