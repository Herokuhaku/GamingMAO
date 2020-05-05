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

	int getEffect(const std::string& key);														// �L�[��n���ƃG�t�F�N�g�̃n���h����Ԃ�
	int getEffect(const std::string& filename, const std::string& key, const float& exLate);	// �t�@�C�����œǂݍ��݁A�L�[�ɓ����

	int playEffect(const int& efcHd, const int& time);											// efcHd:�n���h����time:���ԁ@���̃G�t�F�N�g���w�肵���t���[���Đ�
	void stopEffectAll(void);																	// ���ׂẴG�t�F�N�g���~����

	void UpdateEffekseer(void);																	// �Đ����̃G�t�F�N�g�̍X�V

private:
	static EffekseerMng* sInstance;

	std::map<std::string, int> _effectMap;			// �G�t�F�N�g�̃n���h��
	
	std::vector<std::pair<int, int>> _effectList;	// �Đ����̃G�t�F�N�g�̃��X�g

	EffekseerMng();
	~EffekseerMng();

	void EffectMngInit(void);
};

