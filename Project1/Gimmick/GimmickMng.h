#pragma once
#include <memory>
#include <vector>

class Gimmick;
struct ItemSave;
template<typename T> class Vector2Template;

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

	void CheckUsableRange(Vector2Template<int> pos, int stage, const ItemSave& item);

	static void DeleteAll(void);
private:
	static std::vector<std::shared_ptr<Gimmick>> _gimmickList;	
};

