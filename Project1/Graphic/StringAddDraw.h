#pragma once
#include <string>


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
	// pos_x : X���W	pos_y : ����y���W
	// color : �`��F
	// draw_type : x���W���ǂ��ɍ��킹�邩(���@�����@�E)
	// �Ԃ�l : ������̉��T�C�Y
	int AddStringDraw(const char* string, int pos_x, int pos_y, int color, int draw_type);

	void Draw(void);
	void ClearScreen(void);

	int GetFont(void);				// �t�H���g�̃n���h����get

private:
	static StringAddDraw* sInstance;

	int _strScreen;

	int _fontHandle;		// �t�H���g�̃n���h��

	StringAddDraw();
	~StringAddDraw();
};

