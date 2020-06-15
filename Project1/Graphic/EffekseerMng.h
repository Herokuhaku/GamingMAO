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

	int getEffect(const std::string& key);														// �L�[��n���ƃG�t�F�N�g�̃n���h����Ԃ�
	int getEffect(const std::string& filename, const std::string& key, const float& exRate);	// �t�@�C�����œǂݍ��݁A�L�[�ɓ����

	// efcHd:�n���h�� time:���� pos_x,pos_y:���W offset_x,pffset_y:�I�t�Z�b�g dir:���� 
	int playEffect(const int efcHd, const int time, int* pos_x, int* pos_y, int offset_x, int offset_y, DIR* dir);			
	void stopEffect(int playEfcHd);
	void stopEffectAll(void);																	// ���ׂẴG�t�F�N�g���~����

	void UpdateEffekseer(void);																	// �Đ����̃G�t�F�N�g�̍X�V

private:
	static EffekseerMng* sInstance;

	static std::map<std::string, int> _effectMap;			// �G�t�F�N�g�̃n���h��
	
	std::vector<std::tuple<int, int, std::pair<int*,int*>, std::pair<int,int>, DIR*>> _effectList;	// �Đ����̃G�t�F�N�g�̃��X�g �n���h��,����,���W,�I�t�Z�b�g,����

	EffekseerMng();
	~EffekseerMng();
};

