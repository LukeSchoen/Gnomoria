#ifndef VECTOR3_H
#define VECTOR3_H

#include "Vector.h"

template<typename T>
struct Vector3
{
	union
	{
		struct { T x, y, z; };
		struct { T r, g, b; };
		struct { Vector2<T> xy; T z; };
		struct { T x; Vector2<T> yz; };
		T components[3];
	};

	Vector3() {};
	Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {};
	Vector3(Vector3<T> const &other) : Vector3<T>(other.x, other.y, other.z) {};
	Vector3(Vector2<T> const &other, T _z) : Vector3<T>(other.x, other.y, _z) {};
	Vector3(T _x, Vector2<T> const &other) : Vector3<T>(_x, other.x, other.y) {};

	T X() const { return x; }
	T Y() const { return y; }
	T Z() const { return z; }
	Vector2<T> const XY() { return{ x, z }; }
	Vector2<T> const YX() { return{ z, x }; }
	Vector2<T> const XZ() { return{ x, z }; }
	Vector2<T> const ZX() { return{ z, x }; }
	Vector2<T> const YZ() { return{ y, z }; }
	Vector2<T> const ZY() { return{ z, y }; }
	Vector3<T> const XYZ() { return{ x, y, z }; }
	Vector3<T> const XZY() { return{ x, z, y }; }
	Vector3<T> const YZX() { return{ y, z, x }; }
	Vector3<T> const YXZ() { return{ y, x, z }; }
	Vector3<T> const ZXY() { return{ z, x, y }; }
	Vector3<T> const ZYX() { return{ z, y, x }; }

	void X(T _x) { x = _x };
	void Y(T _y) { y = _y };
	void Z(T _z) { z = _z };

	void XY(T _x, T _y) { x = _x; y = _y; };
	void YX(T _x, T _y) { y = _x; x = _y; };
	void XZ(T _x, T _y) { x = _x; z = _y; };
	void ZX(T _x, T _y) { z = _x; x = _y; };
	void YZ(T _x, T _y) { y = _x; z = _y; };
	void ZY(T _x, T _y) { z = _x; y = _y; };
	void XY(Vector2<T> const &_xy) { x = _xy.x; y = _xy.y; };
	void YX(Vector2<T> const &_xy) { y = _xy.x; x = _xy.y; };
	void XZ(Vector2<T> const &_xy) { x = _xy.x; z = _xy.y; };
	void ZX(Vector2<T> const &_xy) { z = _xy.x; x = _xy.y; };
	void YZ(Vector2<T> const &_xy) { y = _xy.x; z = _xy.y; };
	void ZY(Vector2<T> const &_xy) { z = _xy.x; y = _xy.y; };

	void XYZ(T _x, T _y, T _z) { x = _x; y = _y; z = _z; }
	void XZY(T _x, T _y, T _z) { x = _x; z = _y; y = _z; }
	void YZX(T _x, T _y, T _z) { y = _x; z = _y; x = _z; }
	void YXZ(T _x, T _y, T _z) { y = _x; x = _y; z = _z; }
	void ZXY(T _x, T _y, T _z) { z = _x; x = _y; y = _z; }
	void ZYX(T _x, T _y, T _z) { z = _x; y = _y; z = _z; }
	void XYZ(Vector2<T> const &_xy, T _z) { x = _xy.x; y = _xy.y; z = _z; }
	void XZY(Vector2<T> const &_xy, T _z) { x = _xy.x; z = _xy.y; y = _z; }
	void YZX(Vector2<T> const &_xy, T _z) { y = _xy.x; z = _xy.y; x = _z; }
	void YXZ(Vector2<T> const &_xy, T _z) { y = _xy.x; x = _xy.y; z = _z; }
	void ZXY(Vector2<T> const &_xy, T _z) { z = _xy.x; x = _xy.y; y = _z; }
	void ZYX(Vector2<T> const &_xy, T _z) { z = _xy.x; y = _xy.y; z = _z; }
	void XYZ(T _x, Vector2<T> const &_yz) { x = _x; y = _yz.x; z = _yz.y; }
	void XZY(T _x, Vector2<T> const &_yz) { x = _x; z = _yz.x; y = _yz.y; }
	void YZX(T _x, Vector2<T> const &_yz) { y = _x; z = _yz.x; x = _yz.y; }
	void YXZ(T _x, Vector2<T> const &_yz) { y = _x; x = _yz.x; z = _yz.y; }
	void ZXY(T _x, Vector2<T> const &_yz) { z = _x; x = _yz.x; y = _yz.y; }
	void ZYX(T _x, Vector2<T> const &_yz) { z = _x; y = _yz.x; z = _yz.y; }
	void XYZ(Vector3<T> const &_xyz) { x = _xyz.x; y = _xyz.y; z = _xyz.z; }
	void XZY(Vector3<T> const &_xyz) { x = _xyz.x; z = _xyz.y; y = _xyz.z; }
	void YZX(Vector3<T> const &_xyz) { y = _xyz.x; z = _xyz.y; x = _xyz.z; }
	void YXZ(Vector3<T> const &_xyz) { y = _xyz.x; x = _xyz.y; z = _xyz.z; }
	void ZXY(Vector3<T> const &_xyz) { z = _xyz.x; x = _xyz.y; y = _xyz.z; }
	void ZYX(Vector3<T> const &_xyz) { z = _xyz.x; y = _xyz.y; z = _xyz.z; }

	float Length() const { return sqrt(LengthSquared()); }
	float LengthSquared() const { return Dot3(*this); }
	Vector3<float> Normalise() const { return Vector3<float>(*this) / Length(); }

	T const &operator[](size_t index) const { return components[index]; }
	T &operator[](size_t index) { return components[index]; }

	friend Vector3<T> operator+(Vector3<T> lhs, Vector3<T> const &rhs) { lhs.x += rhs.x; lhs.y += rhs.y; lhs.z += rhs.z; return lhs; }
	friend Vector3<T> operator-(Vector3<T> lhs, Vector3<T> const &rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; lhs.z -= rhs.z; return lhs; }
	friend Vector3<T> operator*(Vector3<T> lhs, Vector3<T> const &rhs) { lhs.x *= rhs.x; lhs.y *= rhs.y; lhs.z *= rhs.z; return lhs; }
	friend Vector3<T> operator/(Vector3<T> lhs, Vector3<T> const &rhs) { lhs.x /= rhs.x; lhs.y /= rhs.y; lhs.z /= rhs.z; return lhs; }

	//template<typename T2> friend Vector3<T> operator+(Vector3<T> lhs, Vector3<T2> const &rhs) { lhs.x += rhs.x; lhs.y += rhs.y; lhs.z += rhs.z; return lhs; }
	//template<typename T2> friend Vector3<T> operator-(Vector3<T> lhs, Vector3<T2> const &rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; lhs.z -= rhs.z; return lhs; }
	//template<typename T2> friend Vector3<T> operator*(Vector3<T> lhs, Vector3<T2> const &rhs) { lhs.x *= rhs.x; lhs.y *= rhs.y; lhs.z *= rhs.z; return lhs; }
	//template<typename T2> friend Vector3<T> operator/(Vector3<T> lhs, Vector3<T2> const &rhs) { lhs.x /= rhs.x; lhs.y /= rhs.y; lhs.z /= rhs.z; return lhs; }

	//friend Vector3<T> operator+(Vector3<T> const &lhs, Vector3<T> rhs) { rhs.x = lhs + rhs.x; rhs.y = lhs.y + rhs.y; rhs.z = lhs.z + rhs.z; return rhs; }
	//friend Vector3<T> operator-(Vector3<T> const &lhs, Vector3<T> rhs) { rhs.x = lhs - rhs.x; rhs.y = lhs.y - rhs.y; rhs.z = lhs.z - rhs.z; return rhs; }
	//friend Vector3<T> operator*(Vector3<T> const &lhs, Vector3<T> rhs) { rhs.x = lhs * rhs.x; rhs.y = lhs.y * rhs.y; rhs.z = lhs.z * rhs.z; return rhs; }
	//friend Vector3<T> operator/(Vector3<T> const &lhs, Vector3<T> rhs) { rhs.x = lhs / rhs.x; rhs.y = lhs.y / rhs.y; rhs.z = lhs.z / rhs.z; return rhs; }

	//template<typename T2> friend Vector3<T> operator+(Vector3<T2> const &lhs, Vector3<T> rhs) { rhs.x = lhs + rhs.x; rhs.y = lhs.y + rhs.y; rhs.z = lhs.z + rhs.z; return rhs; }
	//template<typename T2> friend Vector3<T> operator-(Vector3<T2> const &lhs, Vector3<T> rhs) { rhs.x = lhs - rhs.x; rhs.y = lhs.y - rhs.y; rhs.z = lhs.z - rhs.z; return rhs; }
	//template<typename T2> friend Vector3<T> operator*(Vector3<T2> const &lhs, Vector3<T> rhs) { rhs.x = lhs * rhs.x; rhs.y = lhs.y * rhs.y; rhs.z = lhs.z * rhs.z; return rhs; }
	//template<typename T2> friend Vector3<T> operator/(Vector3<T2> const &lhs, Vector3<T> rhs) { rhs.x = lhs / rhs.x; rhs.y = lhs.y / rhs.y; rhs.z = lhs.z / rhs.z; return rhs; }

	friend Vector3<T> operator+(Vector3<T> lhs, T const &rhs) { lhs.x += rhs; lhs.y += rhs; lhs.z += rhs; return lhs; }
	friend Vector3<T> operator-(Vector3<T> lhs, T const &rhs) { lhs.x -= rhs; lhs.y -= rhs; lhs.z -= rhs; return lhs; }
	friend Vector3<T> operator*(Vector3<T> lhs, T const &rhs) { lhs.x *= rhs; lhs.y *= rhs; lhs.z *= rhs; return lhs; }
	friend Vector3<T> operator/(Vector3<T> lhs, T const &rhs) { lhs.x /= rhs; lhs.y /= rhs; lhs.z /= rhs; return lhs; }

	//template<typename T2> friend Vector3<T> operator+(Vector3<T> lhs, T2 const &rhs) { lhs.x += rhs; lhs.y += rhs; lhs.z += rhs; return lhs; }
	//template<typename T2> friend Vector3<T> operator-(Vector3<T> lhs, T2 const &rhs) { lhs.x -= rhs; lhs.y -= rhs; lhs.z -= rhs; return lhs; }
	//template<typename T2> friend Vector3<T> operator*(Vector3<T> lhs, T2 const &rhs) { lhs.x *= rhs; lhs.y *= rhs; lhs.z *= rhs; return lhs; }
	//template<typename T2> friend Vector3<T> operator/(Vector3<T> lhs, T2 const &rhs) { lhs.x /= rhs; lhs.y /= rhs; lhs.z /= rhs; return lhs; }

	//friend Vector3<T> operator+(T const &lhs, Vector3<T> rhs) { rhs.x = lhs + rhs.x; rhs.y = lhs + rhs.y; rhs.z = lhs + rhs.z; return rhs; }
	//friend Vector3<T> operator-(T const &lhs, Vector3<T> rhs) { rhs.x = lhs - rhs.x; rhs.y = lhs - rhs.y; rhs.z = lhs - rhs.z; return rhs; }
	//friend Vector3<T> operator*(T const &lhs, Vector3<T> rhs) { rhs.x = lhs * rhs.x; rhs.y = lhs * rhs.y; rhs.z = lhs * rhs.z; return rhs; }
	//friend Vector3<T> operator/(T const &lhs, Vector3<T> rhs) { rhs.x = lhs / rhs.x; rhs.y = lhs / rhs.y; rhs.z = lhs / rhs.z; return rhs; }

	//template<typename T2> friend Vector3<T> operator+(T2 const &lhs, Vector3<T> rhs) { rhs.x = lhs + rhs.x; rhs.y = lhs + rhs.y; rhs.z = lhs + rhs.z; return rhs; }
	//template<typename T2> friend Vector3<T> operator-(T2 const &lhs, Vector3<T> rhs) { rhs.x = lhs - rhs.x; rhs.y = lhs - rhs.y; rhs.z = lhs - rhs.z; return rhs; }
	//template<typename T2> friend Vector3<T> operator*(T2 const &lhs, Vector3<T> rhs) { rhs.x = lhs * rhs.x; rhs.y = lhs * rhs.y; rhs.z = lhs * rhs.z; return rhs; }
	//template<typename T2> friend Vector3<T> operator/(T2 const &lhs, Vector3<T> rhs) { rhs.x = lhs / rhs.x; rhs.y = lhs / rhs.y; rhs.z = lhs / rhs.z; return rhs; }

	Vector3<T> operator+=(Vector3<T> const &rhs) { *this = *this + rhs; return *this; }
	Vector3<T> operator-=(Vector3<T> const &rhs) { *this = *this - rhs; return *this; }
	Vector3<T> operator*=(Vector3<T> const &rhs) { *this = *this * rhs; return *this; }
	Vector3<T> operator/=(Vector3<T> const &rhs) { *this = *this / rhs; return *this; }

	//template<typename T2> Vector3<T> operator+=(Vector3<T2> const &rhs) { *this = *this + rhs; return *this; }
	//template<typename T2> Vector3<T> operator-=(Vector3<T2> const &rhs) { *this = *this - rhs; return *this; }
	//template<typename T2> Vector3<T> operator*=(Vector3<T2> const &rhs) { *this = *this * rhs; return *this; }
	//template<typename T2> Vector3<T> operator/=(Vector3<T2> const &rhs) { *this = *this / rhs; return *this; }

	Vector3<T> operator+=(T const &rhs) { *this = *this + rhs; return *this; }
	Vector3<T> operator-=(T const &rhs) { *this = *this - rhs; return *this; }
	Vector3<T> operator*=(T const &rhs) { *this = *this * rhs; return *this; }
	Vector3<T> operator/=(T const &rhs) { *this = *this / rhs; return *this; }

	//template<typename T2> Vector3<T> operator+=(T2 const &rhs) { *this = *this + rhs; return *this; }
	//template<typename T2> Vector3<T> operator-=(T2 const &rhs) { *this = *this - rhs; return *this; }
	//template<typename T2> Vector3<T> operator*=(T2 const &rhs) { *this = *this * rhs; return *this; }
	//template<typename T2> Vector3<T> operator/=(T2 const &rhs) { *this = *this / rhs; return *this; }

	Vector3<T> operator=(Vector3<T> const &rhs) { x = rhs.x; y = rhs.y; z = rhs.z; return *this; }
	bool operator==(Vector3<T> const &rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }

	//template<typename T2> Vector3<T> operator=(Vector3<T2> const &rhs) { x = rhs.x; y = rhs.y; z = rhs.z; return *this; }
	//template<typename T2> bool operator==(Vector3<T2> const &rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }

	//template<typename T2> operator Vector3<T2>() const { return Vector3<T2>(x, y, z); }
	template<typename T2> explicit operator Vector3<T2>() const { return Vector3<T2>(T2(x), T2(y), T2(z)); }

	static Vector3<T> Zero() { return{ 0, 0, 0 }; }
};

typedef Vector3<float> Vec3;
typedef Vector3<int> Vec3i;

#endif