#pragma once
#include <DxLib.h>
#include <map>
#include <vector>
#include <tuple>
#include <string>
#include "LAYER.h"
#include "../common/Vector2.h"

enum class MAP_DATA;

// �`��f�[�^�̗v�f
enum class DrawElm : int
{
	ID,
	X,
	Y,
	EX_RATE,
	RAD,
	LAYER,
	ZORDER,
	BLEND
};

// �G�t�F�N�g�̗v�f
enum class EffectElm : int
{
	KEY,
	X,
	Y,
	EX_RATE,
	RAD,
	LAYER,
	ZORDER,
	BLEND,
	BLEND_PARAM,
	COUNT,
	FLAME
};

// ��ʌ���
enum class ScrEff
{
	FADE,
	FADE2X,
	FADEIN,
	FADEOUT,
	MAX
};

// �G�t�F�N�g�̃I�v�V����
enum class EffectDrawType
{
	DRAW_TO_RELATIVE,
	DRAW_TO_ABSOLUTE
};

#define lpImageMng ImageMng::GetInstance()

using DrawData = std::tuple<int, int, int, double, double,  LAYER, int, int, int>;	// �`��p�f�[�^�@�摜ID, ���Wx, y, �g�嗦�A�p�x, ���C���[, z�I�[�_�[�A�u�����h�A�p�����[�^
using EffectData = std::vector<std::pair<int, int>>;

class ImageMng
{
public:
	static ImageMng& GetInstance()
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

	void setEffect(const std::string& key, EffectData& data);

	const std::vector<int>& getImage(const std::string& key);
	const std::vector<int>& getImage(const std::string& filename, const std::string& key);
	const std::vector<int>& getImage(const std::string& filename, const std::string& key, int size_x, int size_y, int cnt_x, int cnt_y);

	void Draw(void);				// �`��
	void Draw(int screen, bool deleteFlag);


	void playEffect(std::string key, const int* posX, const int* posY, double exRate, double rad, LAYER layer, int zOrder, int blend_mode, int blend_prm, int stage, EffectDrawType draw);	// �G�t�F�N�g�̍Đ�
	void stopEffect(void);
	void UpdateEffect(void);		// �G�t�F�N�g�̕`��ƍX�V

	void AddDraw(DrawData data);	// �`����̒ǉ� _workLayer
	void AddBackDraw(DrawData data);// DX_SCREEN_BACK�ɕ`��

	void setGkind(ScrEff kind);		// ��ʃG�t�F�N�g�̎��
private:
	static ImageMng* sInstance;		// �C���X�^���X
	int _workLayer;

	std::map<std::string, std::vector<int>> _imageMap;					// �摜ID�ۑ��p
	std::map<std::string, EffectData>		_effectMap;		// �G�t�F�N�g�ۑ��p

	std::vector<DrawData> _drawList[2];							// �`����ۑ��p
	std::vector<std::tuple<std::string, const int*, const int*, double, double, LAYER, int, int, int, int, int, int, EffectDrawType>> _effectList;		// �i�s���̃G�t�F�N�g

	//---------------------------------------------------------
	void ScreenEffect(void);		// ��ʃG�t�F�N�g�̕���
	void Fade(void);				// ��ʃG�t�F�N�g�F�t�F�[�h plF : �v���C���[�̃t�F�[�h�iMAP�ړ��j
	void FadeIn(void);
	void FadeOut(void);
	//void Fade2x(void);
	
	ScrEff _Gkind;
	int _fadeCnt;
	int _fadeSpeed;
	bool _plSmoveF;					// �v���C���[�̃X�e�[�W�ړ��̃t���O
	MAP_DATA _plFBXmoveF;				// �v���C���[���ǂ̕����Ɉړ�������
public:
	void SetplmoveF(bool plSmoveF, MAP_DATA plf);
private:
	
	int _screen;
	int _screenCap;
	bool _screenCapF;				// �X�N���[���L���v�`���t���O


	std::pair<int, int> _oldBlend;

	//---------------------------------------------------------

	ImageMng();
	ImageMng(const ImageMng&) = delete;
	ImageMng operator=(const ImageMng&) = delete;
	~ImageMng();

	void ImageMngInit(void);
};

