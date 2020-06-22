#include "GimmickMng.h"
#include "Gimmick.h"

GimmickMng* GimmickMng::sInstance = nullptr;

void GimmickMng::Update(void)
{
	for (const auto& data : _gimmickList)
	{
		data->Update();
	}
}

void GimmickMng::Draw(void)
{
	for (const auto& data : _gimmickList)
	{
		data->Draw();
	}
}

GimmickMng::GimmickMng()
{

}