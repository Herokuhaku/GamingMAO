#pragma once
#include <memory>
#include <vector>

class Gimmick;

class GimmickMng
{
public:
	GimmickMng();
	GimmickMng(const GimmickMng&) = delete;
	GimmickMng operator=(const GimmickMng&) = delete;
	~GimmickMng() = default;

	void Update(void);
	void Draw(void);

	void AddGimmick(Gimmick* gimmick);
	static const std::vector<std::shared_ptr<Gimmick>>& GetGimmicks(void);
private:
	static std::vector<std::shared_ptr<Gimmick>> _gimmickList;	
};

