#pragma once
#include <string>
#include <type_traits>
#include <cassert>

namespace algo
{
	/// <summary>
	/// 数値をクランプする
	/// </summary>
	/// <param name="val">比較する値</param>
	/// <param name="min_val">最小値</param>
	/// <param name="max_val">最大値</param>
	/// <returns>最小値～最大値の値</returns>
	template<typename T>
	T Clamp(T val, T min_val, T max_val)
	{
		return min(max(val, min_val), max_val);
	}

	/// <summary>
	/// 値が正か
	/// </summary>
	/// <param name="val">チェックしたい値</param>
	/// <returns>正ならtrue 負ならfalse</returns>
	template<typename T>
	bool IsPositive(T val)
	{
		assert(std::is_arithmetic<T>::value == true);

		return val >= static_cast<T>(0.0);
	}

	/// <summary>
	/// stringからwstringを取得
	/// </summary>
	/// <param name="str">変換したいstring型文字列</param>
	/// <returns>wstring型文字列</returns>
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
