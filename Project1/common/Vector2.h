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


	// 内積

	// 二次元の外積
	int CrossProduct(const Vector2Template& vec);
	int CrossProduct(const Vector2Template& a, const Vector2Template& b);

	// 大きさ
	T Magnitude(void);
	// 大きさの2乗
	T Magnitude2(void);
	
	// 単位ベクトル
	Vector2Template<float> UnitVec(void);


	// 返値が左辺式　引数が右辺式

	// 代入演算子
	Vector2Template& operator = (const Vector2Template& vec);

	// 単項演算子
	Vector2Template& operator += (const Vector2Template& vec);

	Vector2Template& operator -= (const Vector2Template& vec);

	Vector2Template& operator *= (int k);

	Vector2Template& operator /= (int k);

	Vector2Template operator + () const;								// ｺﾋﾟｰを返却する

	Vector2Template operator - () const;								// ｺﾋﾟｰを返却する

	// 比較演算子												// 1or0を作るから演算子になる
	bool operator == (const Vector2Template& vec) const;

	bool operator != (const Vector2Template& vec) const;

	bool operator > (const Vector2Template& vec) const;

	bool operator >= (const Vector2Template& vec) const;

	bool operator < (const Vector2Template& vec) const;

	bool operator <= (const Vector2Template& vec) const;

	// 添え字演算子
	int& operator [] (Vector2Template i);


};


// ﾍﾞｸﾄﾙの演算
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

template<class T>
Vector2Template<T> operator / (const Vector2Template<T>& u, float k);
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
