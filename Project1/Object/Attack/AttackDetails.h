#pragma once
#include <array>
#include <string>
#include <memory>
#include "../../Manage/COLOR.h"

#define lpAtkDetails AttackDetails::GetInstance()

constexpr int ATTACK_TYPE_MAX = 3;

struct Detail
{
	std::string _name;	// ���@��
	int _magicPoint;	// ����MP
	std::string _desc;	// ���@�̐���
	int _handle;		// �摜�n���h��
};

struct AttackDetails
{
public:
	/// <summary>
	/// �C���X�^���X�̎擾
	/// </summary>
	/// <returns></returns>
	static AttackDetails& GetInstance(void);

	/// <summary>
	/// ���ׂĂ̍U�������擾
	/// </summary>
	/// <returns>�U���̏��</returns>
	const std::array<std::array<std::unique_ptr<Detail>, ATTACK_TYPE_MAX>, static_cast<int>(COLOR::MAX)>& GetDetailsAll(void);
	
	/// <summary>
	/// �U�����̎擾
	/// </summary>
	/// <param name="color">�F</param>
	/// <param name="type">���</param>
	/// <returns>���</returns>
	const std::unique_ptr<Detail>& GetDetail(int color, int type);
private:
	AttackDetails();
	AttackDetails(const AttackDetails&) = delete;
	void operator=(const AttackDetails&) = delete;
	~AttackDetails() = default;

	void LoadAttackData(void);

	std::array<std::array<std::unique_ptr<Detail>, ATTACK_TYPE_MAX>, static_cast<int>(COLOR::MAX)> _details;
};
