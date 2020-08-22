#pragma once

template<class T> class Vector2Template
{
public:
	Vector2Template();
	Vector2Template(T  x, T y);
	~Vector2Template();
	T x;
	T y;
	T& x1;
	T& x2;


	// ì‡êœ

	// ìÒéüå≥ÇÃäOêœ
	int CrossProduct(const Vector2Template& vec);
	int CrossProduct(const Vector2Template& a, const Vector2Template& b);

	// ëÂÇ´Ç≥
	T Magnitude(void);
	// ëÂÇ´Ç≥ÇÃ2èÊ
	T Magnitude2(void);
	
	// íPà ÉxÉNÉgÉã
	Vector2Template<float> UnitVec(void);


	// ï‘ílÇ™ç∂ï”éÆÅ@à¯êîÇ™âEï”éÆ

	// ë„ì¸ââéZéq
	Vector2Template& operator = (const Vector2Template& vec);

	// íPçÄââéZéq
	Vector2Template& operator += (const Vector2Template& vec);

	Vector2Template& operator -= (const Vector2Template& vec);

	Vector2Template& operator *= (int k);

	Vector2Template& operator /= (int k);

	Vector2Template operator + () const;								// ∫Àﬂ∞Çï‘ãpÇ∑ÇÈ

	Vector2Template operator - () const;								// ∫Àﬂ∞Çï‘ãpÇ∑ÇÈ

	// î‰ärââéZéq												// 1or0ÇçÏÇÈÇ©ÇÁââéZéqÇ…Ç»ÇÈ
	bool operator == (const Vector2Template& vec) const;

	bool operator != (const Vector2Template& vec) const;

	bool operator > (const Vector2Template& vec) const;

	bool operator >= (const Vector2Template& vec) const;

	bool operator < (const Vector2Template& vec) const;

	bool operator <= (const Vector2Template& vec) const;

	// ìYÇ¶éöââéZéq
	int& operator [] (Vector2Template i);


};


// Õﬁ∏ƒŸÇÃââéZ
// Vector2 + int
template<class T>
Vector2Template<T> operator + (const Vector2Template<T>& u, int k);
// Vector2 - int
template<class T>
Vector2Template<T> operator - (const Vector2Template<T>& u, int k);
// Vector2 * int
template<class T>
Vector2Template<T> operator * (const Vector2Template<T>& u, int k);
// Vector2 * double
template<class T>
Vector2Template<T> operator * (const Vector2Template<T>& u, double k);
// Vector2 / int
template<class T>
Vector2Template<T> operator / (const Vector2Template<T>& u, int k);
// Vector2 / int
template<class T>
Vector2Template<T> operator / (const Vector2Template<T>& u, double k);
// Vector2 % int
template<class T>
Vector2Template<T> operator % (const Vector2Template<T>& u, int k);

// int * Vector2
//int opreator * (const Vector2);


// Vector2 + Vector2
template<class T>
Vector2Template<T> operator + (const Vector2Template<T>& u, const Vector2Template<T>& v);
// Vector2 - Vector2
template<class T>
Vector2Template<T> operator - (const Vector2Template<T>& u, const Vector2Template<T>& v);
// Vector2 * Vector2
template<class T>
Vector2Template<T> operator * (const Vector2Template<T>& u, const Vector2Template<T>& v);
// Vector2 / Vector2
template<class T>
Vector2Template<T> operator / (const Vector2Template<T>& u, const Vector2Template<T>& v);
// Vector2 % Vector2
template<class T>
Vector2Template<T> operator % (const Vector2Template<T>& u, const Vector2Template<T>& v);

// Vector2 * Vector2
template<class T>
Vector2Template<T> operator *= (const Vector2Template<T>& u, const Vector2Template<T>& v);



// abs
//template<class T>
//Vector2Template<T> operator abs() (const Vector2Template<T>& u);

using Vector2 = Vector2Template<int>;
using Vector2F = Vector2Template<float>;
using Vector2D = Vector2Template<double>;

#include "./detailes/Vector2.h"
