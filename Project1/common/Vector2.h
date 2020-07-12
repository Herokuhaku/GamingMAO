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


	// ����

	// �񎟌��̊O��
	int CrossProduct(const Vector2Template& vec);
	int CrossProduct(const Vector2Template& a, const Vector2Template& b);

	// �Ԓl�����ӎ��@�������E�ӎ�

	// ������Z�q
	Vector2Template& operator = (const Vector2Template& vec);

	// �P�����Z�q
	Vector2Template& operator += (const Vector2Template& vec);

	Vector2Template& operator -= (const Vector2Template& vec);

	Vector2Template& operator *= (int k);

	Vector2Template& operator /= (int k);

	Vector2Template operator + () const;								// ��߰��ԋp����

	Vector2Template operator - () const;								// ��߰��ԋp����

	// ��r���Z�q												// 1or0����邩�牉�Z�q�ɂȂ�
	bool operator == (const Vector2Template& vec) const;

	bool operator != (const Vector2Template& vec) const;

	bool operator > (const Vector2Template& vec) const;

	bool operator >= (const Vector2Template& vec) const;

	bool operator < (const Vector2Template& vec) const;

	bool operator <= (const Vector2Template& vec) const;

	// �Y�������Z�q
	int& operator [] (Vector2Template i);


};


// �޸�ق̉��Z
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
