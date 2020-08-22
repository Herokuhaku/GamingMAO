#pragma once
#include "../../Manage/COLOR.h"
#include <memory>
#include <array>
#include <string>
#include "../../common/Vector2.h"
#include "../../Manage/TimeMng.h"

class Object;
enum class OBJ_TYPE;

class Barrier
{
public:
	Barrier() = delete;
	Barrier(std::weak_ptr<Object> owner, COLOR color, const Vector2& offset, const std::string& imageKey);
	~Barrier() = default;

	void Update(void);
	void Draw(void);
	
	/// <summary>
	/// アクティブか
	/// </summary>
	bool IsActive(void);

	/// <summary>
	/// 消えてもいいか
	/// </summary>
	bool IsDelete(void);

	/// <summary>
	/// 所有者が死んでるか
	/// </summary>
	bool IsDead(void);

	Vector2 GetPos(void);
	std::array<int, 4> GetHitOffset(void);
	TIME GetTimeLine(void);
	int GetStage(void);
	OBJ_TYPE GetOwnerType(void);
private:
	std::weak_ptr<Object> _owner;
	Vector2 _offset;
	std::array<int, 4> _hitBox;

	COLOR _color;
	std::string _imageKey;

	bool _active = false;
	bool _delete = false;

	int _timer;

	void ExpandUpdate(void);
	void ActiveUpdate(void);
	void ReduceUpdate(void);
	void (Barrier::*_update)(void);

	void DeactiveDraw(void);
	void ActiveDraw(void);
	void (Barrier::*_draw)(void);
};

