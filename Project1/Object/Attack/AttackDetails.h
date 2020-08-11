#pragma once
#include <array>
#include <string>
#include <memory>
#include "../../Manage/COLOR.h"

#define lpAtkDetails AttackDetails::GetInstance()

constexpr int ATTACK_TYPE_MAX = 3;

struct Detail
{
	std::string _name;	// 魔法名
	int _magicPoint;	// 消費MP
	std::string _desc;	// 魔法の説明
	int _handle;		// 画像ハンドル
};

struct AttackDetails
{
public:
	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns></returns>
	static AttackDetails& GetInstance(void);

	/// <summary>
	/// すべての攻撃情報を取得
	/// </summary>
	/// <returns>攻撃の情報</returns>
	const std::array<std::array<std::unique_ptr<Detail>, ATTACK_TYPE_MAX>, static_cast<int>(COLOR::MAX)>& GetDetailsAll(void);
	
	/// <summary>
	/// 攻撃情報の取得
	/// </summary>
	/// <param name="color">色</param>
	/// <param name="type">種類</param>
	/// <returns>情報</returns>
	const std::unique_ptr<Detail>& GetDetail(int color, int type);
private:
	AttackDetails();
	AttackDetails(const AttackDetails&) = delete;
	void operator=(const AttackDetails&) = delete;
	~AttackDetails() = default;

	void LoadAttackData(void);

	std::array<std::array<std::unique_ptr<Detail>, ATTACK_TYPE_MAX>, static_cast<int>(COLOR::MAX)> _details;
};
