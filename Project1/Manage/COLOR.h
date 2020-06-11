#pragma once
#include <type_traits>

// êFÇÃéÌóﬁ
enum class COLOR : int
{
	BLACK	= 0,
	RED		= 1,
	GREEN	= 2,
	YELLOW	= 3,
	BLUE	= 4,
	MAGENTA	= 5,
	CYAN	= 6,
	WHITE	= 7,
	MAX		= 8
};

inline COLOR operator+(const COLOR& lval, const COLOR& rval)
{
	return static_cast<COLOR>(std::underlying_type<COLOR>::type(lval) + std::underlying_type<COLOR>::type(rval));
}

inline int operator-(const COLOR& lval, const int& rval)
{
	return std::underlying_type<COLOR>::type(lval) - rval;
}

inline COLOR operator|(const COLOR& lval, const COLOR& rval)
{
	return static_cast<COLOR>(std::underlying_type<COLOR>::type(lval) | std::underlying_type<COLOR>::type(rval));
}