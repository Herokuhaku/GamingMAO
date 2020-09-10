#pragma once
#include <string>
#include <unordered_map>
#include <DxLib.h>

#define lpStrAdd StringAddDraw::GetInstance()

#define DRAW_TO_LEFT	0
#define DRAW_TO_CENTER	1
#define DRAW_TO_RIGHT	2

class StringAddDraw
{
public:
	static StringAddDraw& GetInstance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new StringAddDraw();
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

	// string : �`�悷�镶����
	// font_key:�t�H���g���ʃL�[
	// pos_x : X���W	pos_y : ����y���W
	// color : �`��F
	// draw_type : x���W���ǂ��ɍ��킹�邩(���@�����@�E)
	// �Ԃ�l : ������̉��T�C�Y
	int AddStringDraw(const char* string, const std::string& font_key, int pos_x, int pos_y, int color, int draw_type, int blendMode = DX_BLENDMODE_NOBLEND, int param = 0);

	void Draw(void);
	void ClearScreen(void);
	
	// font_key�ɑΉ�����L�[��Ԃ�
	int GetFont(const std::string& font_key);				

private:
	static StringAddDraw* sInstance;

	int _strScreen;

	std::unordered_map<std::string, int> _fontHandle;		// �t�H���g�̃n���h��

	StringAddDraw();
	StringAddDraw(const StringAddDraw&) = delete;
	StringAddDraw operator+(const StringAddDraw&) = delete;
	~StringAddDraw();
};

