#pragma once
#include <DxLib.h>
#include <map>
#include <vector>
#include <tuple>
#include "LAYER.h"
#include "../common/Vector2.h"
#include <string>
#include "EffekseerMng.h"

#include "../Manage/MapMng.h"

// 描画データの要素
enum class DrawElm
{
	ID,
	X,
	Y,
	RAD,
	LAYER,
	ZORDER
};

// エフェクトの種類
enum class EFFECT
{
	SMOKE,
	GRIP
};

// 画面効果
enum class ScrEff
{
	FADE,
	FADE2X,
	FADEIN,
	FADEOUT,
	MAX
};

#define lpImageMng ImageMng::getInstance()

using DrawData = std::tuple<int, int, int, double, LAYER, int>;	// 描画用データ　画像ID, 座標x, y, 角度, レイヤー, zオーダー

class ImageMng
{
public:
	static ImageMng& getInstance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new ImageMng();
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

	void setEffect(EFFECT effect, Vector2Template<int> pos);

	std::vector<int> getImage(const std::string& key);
	std::vector<int> getImage(const std::string& filename, const std::string& key);
	std::vector<int> getImage(const std::string& filename, const std::string& key, int size_x, int size_y, int cnt_x, int cnt_y);

	void Draw(void);				// 描画
	void UpdateEffect(void);		// エフェクトの描画と更新

	void AddDraw(DrawData data);	// 描画情報の追加 _workLayer
	void AddBackDraw(DrawData data);// DX_SCREEN_BACKに描画

	void setGkind(ScrEff kind);		// 画面エフェクトの種類
private:
	static ImageMng* sInstance;		// インスタンス
	int _workLayer;

	std::map<std::string, std::vector<int>> _imageMap;					// 画像ID保存用
	std::map<EFFECT, std::vector<std::pair<int, int>>>	_effectMap;		// エフェクト保存用

	std::vector<DrawData> _drawList[2];							// 描画情報保存用
	std::vector<std::tuple<EFFECT, Vector2Template<int>, int, int>> _effectList;		// 進行中のエフェクト

	//---------------------------------------------------------
	void ScreenEffect(void);		// 画面エフェクトの分岐
	void Fade(void);				// 画面エフェクト：フェード plF : プレイヤーのフェード（MAP移動）
	void FadeIn(void);
	void FadeOut(void);
	//void Fade2x(void);
	
	ScrEff _Gkind;
	int _fadeCnt;
	int _fadeSpeed;
	bool _plSmoveF;					// プレイヤーのステージ移動のフラグ
	MAP_DATA _plFBXmoveF;				// プレイヤーがどの方向に移動したか
public:
	void SetplmoveF(bool flag, MAP_DATA plf);
private:
	//---------------------------------------------------------

	ImageMng();
	~ImageMng();

	void ImageMngInit(void);
};

