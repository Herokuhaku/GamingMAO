#pragma once
#include <string>
#include <type_traits>
#include <cassert>

namespace algo
{
	/// <summary>
	/// ���l���N�����v����
	/// </summary>
	/// <param name="val">��r����l</param>
	/// <param name="min_val">�ŏ��l</param>
	/// <param name="max_val">�ő�l</param>
	/// <returns>�ŏ��l�`�ő�l�̒l</returns>
	template<typename T>
	T Clamp(T val, T min_val, T max_val)
	{
		return min(max(val, min_val), max_val);
	}

	/// <summary>
	/// �l������
	/// </summary>
	/// <param name="val">�`�F�b�N�������l</param>
	/// <returns>���Ȃ�true ���Ȃ�false</returns>
	template<typename T>
	bool IsPositive(T val)
	{
		assert(std::is_arithmetic<T>::value == true);

		return val >= static_cast<T>(0.0);
	}

	/// <summary>
	/// string����wstring���擾
	/// </summary>
	/// <param name="str">�ϊ�������string�^������</param>
	/// <returns>wstring�^������</returns>
	inline std::wstring StringToWideString(const std::string& str)
	{
		std::wstring wstr;
		auto bufferSize = MultiByteToWideChar(CP_ACP,
			MB_PRECOMPOSED | MB_ERR_INVALID_CHARS,
			str.c_str(), -1, nullptr, 0);
		wstr.resize(bufferSize);

		auto num2 = MultiByteToWideChar(CP_ACP,
			MB_PRECOMPOSED | MB_ERR_INVALID_CHARS,
			str.c_str(), -1, &wstr[0], bufferSize);

		return wstr;
	}
}
