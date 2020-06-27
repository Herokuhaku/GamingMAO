#pragma once
#include <unordered_map>
#include <string>


struct AudioContainer
{
public:
	// ���t�@�C���̓ǂݍ���
	// filename:�t�@�C����
	// key:�L�[
	// buffer_count:�����Đ��\��
	void LoadSound(const std::string& filename, const std::string& key, const int& buffer_count);

	// ���n���h���̎擾
	// key:�L�[
	int GetSound(const std::string& key);

	// ���ʕύX
	// key:�L�[
	// volme:����(0�`255�� �����傫���قǉ��ʂ��傫���Ȃ�)
	void ChangeVolume(const std::string& key, const int& volume);
private:
	std::unordered_map<std::string, int> _container;
};

