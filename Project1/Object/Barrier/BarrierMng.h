#pragma once
#include <memory>
#include <vector>
#include "../../common/Vector2.h"

class Barrier;
class Object;
enum class COLOR;
class GameScene;

class BarrierMng
{
public:
	BarrierMng() = delete;
	BarrierMng(GameScene* gs);
	~BarrierMng() = default;

	void Update(void);
	void Draw(void);

	const std::vector<std::shared_ptr<Barrier>>& GetBarrier(void);

	void MakeBarrier(Object* owner, COLOR color, const Vector2& offset);
private:
	std::vector<std::shared_ptr<Barrier>> _barriers;
	GameScene* _gamescene;
};

