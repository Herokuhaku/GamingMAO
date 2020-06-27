#include <DxLib.h>
#include <cassert>
#include "AudioContainer.h"

void AudioContainer::LoadSound(const std::string& filename, const std::string& key, const int& buffer_count = 3)
{
	if (_container.find(key) != _container.end())
	{
		return;
	}
	_container.emplace(key, LoadSoundMem(filename.c_str(), buffer_count));
}

int AudioContainer::GetSound(const std::string & key)
{
	if (_container.find(key) == _container.end())
	{
		assert(false);
		return -1;
	}
	return _container[key];
}

void AudioContainer::ChangeVolume(const std::string & key, const int & volume)
{
	if (_container.find(key) == _container.end() || volume < 0 || volume > 255)
	{
		assert(false);
		return;
	}

	ChangeVolumeSoundMem(volume, _container[key]);
}
