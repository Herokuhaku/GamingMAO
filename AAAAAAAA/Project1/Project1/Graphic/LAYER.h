#pragma once


// レイヤー
enum class LAYER
{
	BG,				// 背景
	CHAR,			// キャラクター
	UI,				// UI
	EX,				// 特殊
	MAX
};

LAYER begin(LAYER);
LAYER end(LAYER);

LAYER operator++(LAYER& key);
LAYER operator*(LAYER key);