#include "..\Vector2.h"


template<class T> Vector2Template<T>::Vector2Template()
{
	x = 0;
	y = 0;
}

template<class T> Vector2Template<T>::Vector2Template(T x, T y)
{
	this->x = x;
	this->y = y;
}


template<class T> Vector2Template<T>::~Vector2Template()
{
}

template<class T>
inline int Vector2Template<T>::CrossProduct(const Vector2Template & vec)
{
	return static_cast<int>(x * vec.y - y * vec.x);
}

template<class T>
inline int Vector2Template<T>::CrossProduct(const Vector2Template& a, const Vector2Template& b)
{
	return static_cast<int>(a.x * b.y - a.y * b.x);
}

template<class T>
Vector2Template<T>& Vector2Template<T>::operator = (const Vector2Template& vec)
{
	x = vec.x;
	y = vec.y;

	return *this;
}

template<class T>
Vector2Template<T>& Vector2Template<T>::operator += (const Vector2Template& vec)
{
	x += vec.x;
	y += vec.y;

	return *this;
}

template<class T>
Vector2Template<T>& Vector2Template<T>::operator -= (const Vector2Template& vec)
{
	x -= vec.x;
	y -= vec.y;

	return *this;
}

template<class T>
Vector2Template<T>& Vector2Template<T>::operator *= (int k)
{
	x *= k;
	y *= k;

	return *this;
}

template<class T>
Vector2Template<T>& Vector2Template<T>::operator /= (int k)
{
	x /= k;
	y /= k;

	return *this;
}

template<class T>
Vector2Template<T> Vector2Template<T>::operator + ()const
{
	return *this;
}

template<class T>
Vector2Template<T> Vector2Template<T>::operator - ()const
{
	return Vector2(-this->x, -this->y);
}

template<class T>
bool Vector2Template<T>::operator == (const Vector2Template& vec) const
{
	return ((this->x == vec.x) && (this->y == vec.y));			// ？return *this == vec;
}

template<class T>
bool Vector2Template<T>::operator != (const Vector2Template& vec) const
{
	return !((this->x == vec.x) && (this->y == vec.y));			// ？return !(*this == vec);
}

template<class T>
bool Vector2Template<T>::operator > (const Vector2Template& vec) const
{
	return (this->x > vec.x) && (this->y > vec.y);
}

template<class T>
bool Vector2Template<T>::operator >= (const Vector2Template& vec) const
{
	return (this->x >= vec.x) && (this->y >= vec.y);
}

template<class T>
bool Vector2Template<T>::operator < (const Vector2Template& vec) const
{
	return (this->x < vec.x) && (this->y < vec.y);
}

template<class T>
bool Vector2Template<T>::operator <= (const Vector2Template& vec) const
{
	return (this->x <= vec.x) && (this->y <= vec.y);
}

template<class T>
int& Vector2Template<T>:: operator [] (Vector2Template i)								// ﾌｧｲﾙからﾃﾞｰﾀを取り出すときfor文と組み合わせる
{
	if (i == 0)
	{
		return x;
	}
	else if (i == 1)
	{
		return y;
	}
	else
	{
		return x;
	}
}

template<class T>
Vector2Template<T> operator + (const Vector2Template<T>& u, int k)
{
	Vector2 vec;
	vec.x = u.x + k;
	vec.y = u.y + k;

	return vec;
}

template<class T>
Vector2Template<T> operator - (const Vector2Template<T>& u, int k)
{
	Vector2Template<T> vec;
	vec.x = u.x - k;
	vec.y = u.y - k;

	return vec;
}

template<class T>
Vector2Template<T> operator * (const Vector2Template<T>& u, int k)
{
	Vector2Template<T> vec;
	vec.x = u.x * k;
	vec.y = u.y * k;

	return vec;
}

template<class T>
inline Vector2Template<T> operator*(const Vector2Template<T>& u, double k)
{
	Vector2Template<T> vec;
	vec.x = static_cast<T>(u.x * k);
	vec.y = static_cast<T>(u.y * k);

	return vec;
}

template<class T>
inline Vector2Template<T> operator/(const Vector2Template<T>& u, int k)
{
	Vector2Template<T> vec;
	vec.x = u.x / k;
	vec.y = u.y / k;

	return vec;
}

template<class T>
Vector2Template<T> operator / (const Vector2Template<T>& u, double k)
{
	Vector2Template<T> vec;
	vec.x = u.x / k;
	vec.y = u.y / k;

	return vec;
}

template<class T>
Vector2Template<T> operator % (const Vector2Template<T>& u, int k)
{
	Vector2 vec;
	vec.x = u.x % k;
	vec.y = u.y % k;

	return vec;
}



template<class T>
Vector2Template<T> operator + (const Vector2Template<T>& u, const Vector2Template<T>& v)
{
	Vector2Template<T> vec;
	vec.x = u.x + v.x;
	vec.y = u.y + v.y;

	return vec;
}

template<class T>
Vector2Template<T> operator - (const Vector2Template<T>& u, const Vector2Template<T>& v)
{
	Vector2Template<T> vec;
	vec.x = u.x - v.x;
	vec.y = u.y - v.y;

	return vec;
}

template<class T>
inline Vector2Template<T> operator*=(const Vector2Template<T>& u, const Vector2Template<T>& v)
{
	return u * v;
}

template<class T>
Vector2Template<T> operator * (const Vector2Template<T>& u, const Vector2Template<T>& v)
{
	Vector2Template<T> vec;
	vec.x = u.x * v.x;
	vec.y = u.y * v.y;

	return vec;
}

template<class T>
Vector2Template<T> operator / (const Vector2Template<T>& u, const Vector2Template<T>& v)
{
	Vector2 vec;
	vec.x = u.x / v.x;
	vec.y = u.y / v.y;

	return vec;
}

template<class T>
Vector2Template<T> operator % (const Vector2Template<T>& u, const Vector2Template<T>& v)
{
	Vector2 vec;
	vec.x = u.x % v.x;
	vec.y = u.y % v.y;

	return vec;
}

//template<class T>
//inline Vector2Template<T> operator abs()(const Vector2Template<T>& u)
//{
//	if (u < 0)
//	{
//		u *= -1;
//	}
//	return u;
//}



//int opreator * (const Vector2)
//{
//	Vector2 vec;
//	vec.x = u.x + k;
//	vec.y = u.y + k;
//
//	return vec;
//}