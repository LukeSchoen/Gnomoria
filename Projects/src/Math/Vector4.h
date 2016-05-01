#ifndef VECTOR4_H
#define VECTOR4_H

#include "Vector.h"

template<typename T>
struct Vector4
{
	union
	{
		struct { T x, y, z, w; };
		struct { Vector2<T> xy; Vector2<T> zw; };
		struct { T x; Vector2<T> yz; T w; };
		struct { T x; Vector3<T> yzw; };
		struct { Vector3<T> xyz; T w; };
		T components[4];
	};

	Vector4() {};
	Vector4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {};
	Vector4(Vector2<T> const &_xy, Vector2<T> const &_zw) : xy(_xy), zw(_zw) {}
	Vector4(T _x, T _y, Vector2<T> const &_zw) : x(_x), y(_y), zw(_zw) {}
	Vector4(T _x, Vector2<T> const &_yz, T _w) : x(_x), yz(_yz), w(_w) {}
	Vector4(Vector2<T> const &_xy, T _z, T _w) : xy(_xy), z(_z), w(_w) {}
	Vector4(Vector3<T> const &_xyz, T _w) : xyz(_xyz), w(_w) {}
	Vector4(T _x, Vector3<T> const &_yzw) : x(_x), yzw(_yzw) {}
	Vector4(Vector4<T> const &other) : Vector4<T>(other.x, other.y, other.z, other.w) {}


	float Length() const { return sqrt(LengthSquared()); }
	float LengthSquared() const { return Dot3(*this); }
	Vector3<float> Normalise() const { return Vector3<float>(*this) / Length(); }

	T const &operator[](size_t index) const { return components[index]; }
	T &operator[](size_t index) { return components[index]; }

	friend Vector4<T> operator+(Vector4<T> lhs, Vector4<T> const &rhs) { lhs.x += rhs.x; lhs.y += rhs.y; lhs.z += rhs.z; lhs.w += rhs.w; return lhs; }
	friend Vector4<T> operator-(Vector4<T> lhs, Vector4<T> const &rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; lhs.z -= rhs.z; lhs.w -= rhs.w; return lhs; }
	friend Vector4<T> operator*(Vector4<T> lhs, Vector4<T> const &rhs) { lhs.x *= rhs.x; lhs.y *= rhs.y; lhs.z *= rhs.z; lhs.w *= rhs.w; return lhs; }
	friend Vector4<T> operator/(Vector4<T> lhs, Vector4<T> const &rhs) { lhs.x /= rhs.x; lhs.y /= rhs.y; lhs.z /= rhs.z; lhs.w /= rhs.w; return lhs; }

	//template<typename T2> friend Vector4<T> operator+(Vector4<T> lhs, Vector4<T2> const &rhs) { lhs.x += rhs.x; lhs.y += rhs.y; lhs.z += rhs.z; lhs.w += rhs.w; return lhs; }
	//template<typename T2> friend Vector4<T> operator-(Vector4<T> lhs, Vector4<T2> const &rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; lhs.z -= rhs.z; lhs.w -= rhs.w; return lhs; }
	//template<typename T2> friend Vector4<T> operator*(Vector4<T> lhs, Vector4<T2> const &rhs) { lhs.x *= rhs.x; lhs.y *= rhs.y; lhs.z *= rhs.z; lhs.w *= rhs.w; return lhs; }
	//template<typename T2> friend Vector4<T> operator/(Vector4<T> lhs, Vector4<T2> const &rhs) { lhs.x /= rhs.x; lhs.y /= rhs.y; lhs.z /= rhs.z; lhs.w /= rhs.w; return lhs; }

	friend Vector4<T> operator+(Vector4<T> const &lhs, Vector4<T> rhs) { rhs.x = lhs + rhs.x; rhs.y = lhs.y + rhs.y; rhs.z = lhs.z + rhs.z; rhs.w = lhs.w + rhs.w; return rhs; }
	friend Vector4<T> operator-(Vector4<T> const &lhs, Vector4<T> rhs) { rhs.x = lhs - rhs.x; rhs.y = lhs.y - rhs.y; rhs.z = lhs.z - rhs.z; rhs.w = lhs.w - rhs.w; return rhs; }
	friend Vector4<T> operator*(Vector4<T> const &lhs, Vector4<T> rhs) { rhs.x = lhs * rhs.x; rhs.y = lhs.y * rhs.y; rhs.z = lhs.z * rhs.z; rhs.w = lhs.w * rhs.w; return rhs; }
	friend Vector4<T> operator/(Vector4<T> const &lhs, Vector4<T> rhs) { rhs.x = lhs / rhs.x; rhs.y = lhs.y / rhs.y; rhs.z = lhs.z / rhs.z; rhs.w = lhs.w / rhs.w; return rhs; }

	//template<typename T2> friend Vector4<T> operator+(Vector4<T2> const &lhs, Vector4<T> rhs) { rhs.x = lhs + rhs.x; rhs.y = lhs.y + rhs.y; rhs.z = lhs.z + rhs.z; rhs.w = lhs.w + rhs.w; return rhs;}
	//template<typename T2> friend Vector4<T> operator-(Vector4<T2> const &lhs, Vector4<T> rhs) { rhs.x = lhs - rhs.x; rhs.y = lhs.y - rhs.y; rhs.z = lhs.z - rhs.z; rhs.w = lhs.w - rhs.w; return rhs; }
	//template<typename T2> friend Vector4<T> operator*(Vector4<T2> const &lhs, Vector4<T> rhs) { rhs.x = lhs * rhs.x; rhs.y = lhs.y * rhs.y; rhs.z = lhs.z * rhs.z; rhs.w = lhs.w * rhs.w; return rhs; }
	//template<typename T2> friend Vector4<T> operator/(Vector4<T2> const &lhs, Vector4<T> rhs) { rhs.x = lhs / rhs.x; rhs.y = lhs.y / rhs.y; rhs.z = lhs.z / rhs.z; rhs.w = lhs.w / rhs.w; return rhs; }


	friend Vector4<T> operator+(Vector4<T> lhs, T const &rhs) { lhs.x += rhs; lhs.y += rhs; lhs.z += rhs; lhs.w += rhs; return lhs; }
	friend Vector4<T> operator-(Vector4<T> lhs, T const &rhs) { lhs.x -= rhs; lhs.y -= rhs; lhs.z -= rhs; lhs.w -= rhs; return lhs; }
	friend Vector4<T> operator*(Vector4<T> lhs, T const &rhs) { lhs.x *= rhs; lhs.y *= rhs; lhs.z *= rhs; lhs.w *= rhs; return lhs; }
	friend Vector4<T> operator/(Vector4<T> lhs, T const &rhs) { lhs.x /= rhs; lhs.y /= rhs; lhs.z /= rhs; lhs.w /= rhs; return lhs; }

	//template<typename T2> friend Vector4<T> operator+(Vector4<T> lhs, T2 const &rhs) { lhs.x += rhs; lhs.y += rhs; lhs.z += rhs; lhs.w += rhs; return lhs;}
	//template<typename T2> friend Vector4<T> operator-(Vector4<T> lhs, T2 const &rhs) { lhs.x -= rhs; lhs.y -= rhs; lhs.z -= rhs; lhs.w -= rhs; return lhs; }
	//template<typename T2> friend Vector4<T> operator*(Vector4<T> lhs, T2 const &rhs) { lhs.x *= rhs; lhs.y *= rhs; lhs.z *= rhs; lhs.w *= rhs; return lhs; }
	//template<typename T2> friend Vector4<T> operator/(Vector4<T> lhs, T2 const &rhs) { lhs.x /= rhs; lhs.y /= rhs; lhs.z /= rhs; lhs.w /= rhs; return lhs; }


	friend Vector4<T> operator+(T const &lhs, Vector4<T> rhs) { rhs.x = lhs + rhs.x; rhs.y = lhs + rhs.y; rhs.z = lhs + rhs.z; rhs.w = lhs + rhs.w; return rhs; }
	friend Vector4<T> operator-(T const &lhs, Vector4<T> rhs) { rhs.x = lhs - rhs.x; rhs.y = lhs - rhs.y; rhs.z = lhs - rhs.z; rhs.w = lhs - rhs.w; return rhs; }
	friend Vector4<T> operator*(T const &lhs, Vector4<T> rhs) { rhs.x = lhs * rhs.x; rhs.y = lhs * rhs.y; rhs.z = lhs * rhs.z; rhs.w = lhs * rhs.w; return rhs; }
	friend Vector4<T> operator/(T const &lhs, Vector4<T> rhs) { rhs.x = lhs / rhs.x; rhs.y = lhs / rhs.y; rhs.z = lhs / rhs.z; rhs.w = lhs / rhs.w; return rhs; }

	//template<typename T2> friend Vector4<T> operator+(T2 const &lhs, Vector4<T> rhs) { rhs.x = lhs + rhs.x; rhs.y = lhs + rhs.y; rhs.z = lhs + rhs.z; rhs.w = lhs + rhs.w; return rhs;}
	//template<typename T2> friend Vector4<T> operator-(T2 const &lhs, Vector4<T> rhs) { rhs.x = lhs - rhs.x; rhs.y = lhs - rhs.y; rhs.z = lhs - rhs.z; rhs.w = lhs - rhs.w; return rhs; }
	//template<typename T2> friend Vector4<T> operator*(T2 const &lhs, Vector4<T> rhs) { rhs.x = lhs * rhs.x; rhs.y = lhs * rhs.y; rhs.z = lhs * rhs.z; rhs.w = lhs * rhs.w; return rhs; }
	//template<typename T2> friend Vector4<T> operator/(T2 const &lhs, Vector4<T> rhs) { rhs.x = lhs / rhs.x; rhs.y = lhs / rhs.y; rhs.z = lhs / rhs.z; rhs.w = lhs / rhs.w; return rhs; }

	Vector4<T> operator+=(Vector4<T> const &rhs) { *this = *this + rhs; return *this; }
	Vector4<T> operator-=(Vector4<T> const &rhs) { *this = *this - rhs; return *this; }
	Vector4<T> operator*=(Vector4<T> const &rhs) { *this = *this * rhs; return *this; }
	Vector4<T> operator/=(Vector4<T> const &rhs) { *this = *this / rhs; return *this; }

	//template<typename T2> Vector4<T> operator+=(Vector4<T2> const &rhs) { *this = *this + rhs; return *this; }
	//template<typename T2> Vector4<T> operator-=(Vector4<T2> const &rhs) { *this = *this - rhs; return *this; }
	//template<typename T2> Vector4<T> operator*=(Vector4<T2> const &rhs) { *this = *this * rhs; return *this; }
	//template<typename T2> Vector4<T> operator/=(Vector4<T2> const &rhs) { *this = *this / rhs; return *this; }

	Vector4<T> operator+=(T const &rhs) { *this = *this + rhs; return *this; }
	Vector4<T> operator-=(T const &rhs) { *this = *this - rhs; return *this; }
	Vector4<T> operator*=(T const &rhs) { *this = *this * rhs; return *this; }
	Vector4<T> operator/=(T const &rhs) { *this = *this / rhs; return *this; }

	//template<typename T2> Vector4<T> operator+=(T2 const &rhs) { *this = *this + rhs; return *this; }
	//template<typename T2> Vector4<T> operator-=(T2 const &rhs) { *this = *this - rhs; return *this; }
	//template<typename T2> Vector4<T> operator*=(T2 const &rhs) { *this = *this * rhs; return *this; }
	//template<typename T2> Vector4<T> operator/=(T2 const &rhs) { *this = *this / rhs; return *this; }


	Vector4<T> operator=(Vector4<T> const &rhs) { x = rhs.x; y = rhs.y; z = rhs.z; w = rhs.w; return *this; }
	bool operator==(Vector4<T> const &rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z && w == rhz.w; }
  bool operator!=(Vector4<T> const &rhs) const { return !(rhs == *this); }

	//template<typename T2> Vector4<T> operator=(Vector4<T2> const &rhs) { x = rhs.x; y = rhs.y; z = rhs.z; w = rhs.w; return *this; }
	//template<typename T2> bool operator==(Vector4<T2> const &rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z && w == rhz.w; }

	//template<typename T2> operator T2() const { return T2(x, y, z, w); }
	template<typename T2> explicit operator Vector4<T2>() const { return Vector4<T2>(T2(x), T2(y), T2(z), T2(w)); }

	static Vector3<T> Zero() { return{ 0, 0, 0 }; }

#pragma region Swizzles

	T X() const { return x; }
	T Y() const { return y; }
	T Z() const { return z; }
	T W() const { return w; }

	Vector2<T> const XY() { return{ x, z }; }
	Vector2<T> const YX() { return{ z, x }; }
	Vector2<T> const XZ() { return{ x, z }; }
	Vector2<T> const ZX() { return{ z, x }; }
	Vector2<T> const YZ() { return{ y, z }; }
	Vector2<T> const ZY() { return{ z, y }; }
	Vector2<T> const XW() { return{ x, w }; }
	Vector2<T> const WX() { return{ w, x }; }
	Vector2<T> const WZ() { return{ w, z }; }
	Vector2<T> const ZW() { return{ z, w }; }
	Vector2<T> const YW() { return{ y, w }; }
	Vector2<T> const WY() { return{ w, y }; }

	Vector3<T> const XYZ() { return{ x, y, z }; }
	Vector3<T> const XZY() { return{ x, z, y }; }
	Vector3<T> const YZX() { return{ y, z, x }; }
	Vector3<T> const YXZ() { return{ y, x, z }; }
	Vector3<T> const ZXY() { return{ z, x, y }; }
	Vector3<T> const ZYX() { return{ z, y, x }; }
	Vector3<T> const WYZ() { return{ w, y, z }; }
	Vector3<T> const WZY() { return{ w, z, y }; }
	Vector3<T> const YZW() { return{ y, z, w }; }
	Vector3<T> const YWZ() { return{ y, w, z }; }
	Vector3<T> const ZWY() { return{ z, w, y }; }
	Vector3<T> const ZYW() { return{ z, y, w }; }
	Vector3<T> const XWZ() { return{ x, w, z }; }
	Vector3<T> const XZW() { return{ x, z, w }; }
	Vector3<T> const WZX() { return{ w, z, x }; }
	Vector3<T> const WXZ() { return{ w, x, z }; }
	Vector3<T> const ZXW() { return{ z, x, w }; }
	Vector3<T> const ZWX() { return{ z, w, x }; }
	Vector3<T> const XYW() { return{ x, y, w }; }
	Vector3<T> const XWY() { return{ x, w, y }; }
	Vector3<T> const YWX() { return{ y, w, x }; }
	Vector3<T> const YXW() { return{ y, x, w }; }
	Vector3<T> const WXY() { return{ w, x, y }; }
	Vector3<T> const WYX() { return{ w, y, x }; }

	Vector4<T> const XYZW() { return{ x, y, z, w }; }
	Vector4<T> const XYWZ() { return{ x, y, w, z }; }
	Vector4<T> const XZXW() { return{ x, z, x, w }; }
	Vector4<T> const XZYW() { return{ x, z, y, w }; }
	Vector4<T> const XWZY() { return{ x, w, z, y }; }
	Vector4<T> const XWYZ() { return{ x, w, y, z }; }
	Vector4<T> const YXZW() { return{ y, x, z, w }; }
	Vector4<T> const YXWZ() { return{ y, x, w, z }; }
	Vector4<T> const YZXW() { return{ y, z, x, w }; }
	Vector4<T> const YZWX() { return{ y, z, w, x }; }
	Vector4<T> const YWXZ() { return{ y, w, x, z }; }
	Vector4<T> const YWZX() { return{ y, w, z, x }; }
	Vector4<T> const ZWXY() { return{ z, w, x, y }; }
	Vector4<T> const ZWYX() { return{ z, w, y, x }; }
	Vector4<T> const ZXWY() { return{ z, x, w, y }; }
	Vector4<T> const ZXYW() { return{ z, x, y, w }; }
	Vector4<T> const ZYWX() { return{ z, y, w, x }; }
	Vector4<T> const ZYXW() { return{ z, y, x, w }; }
	Vector4<T> const WXYZ() { return{ w, x, y, z }; }
	Vector4<T> const WXZY() { return{ w, x, z, y }; }
	Vector4<T> const WYZX() { return{ w, y, z, x }; }
	Vector4<T> const WYXZ() { return{ w, y, x, z }; }
	Vector4<T> const WZYX() { return{ w, z, y, x }; }
	Vector4<T> const WZXY() { return{ w, z, x, y }; }

	void X(T _x) { x = _x };
	void Y(T _y) { y = _y };
	void Z(T _z) { z = _z };
	void W(T _w) { w = _w };

	void XY(T _x, T _y) { x = _x; y = _y; };
	void YX(T _x, T _y) { y = _x; x = _y; };
	void XZ(T _x, T _y) { x = _x; z = _y; };
	void ZX(T _x, T _y) { z = _x; x = _y; };
	void YZ(T _x, T _y) { y = _x; z = _y; };
	void ZY(T _x, T _y) { z = _x; y = _y; };
	void WX(T _x, T _y) { w = _x; x = _y; };
	void XW(T _x, T _y) { x = _x; w = _y; };
	void WZ(T _x, T _y) { w = _x; z = _y; };
	void ZW(T _x, T _y) { z = _x; w = _y; };
	void YW(T _x, T _y) { y = _x; w = _y; };
	void WY(T _x, T _y) { w = _x; y = _y; };
	void XY(Vector2<T> const &_xy) { x = _xy.x; y = _xy.y; };
	void YX(Vector2<T> const &_xy) { y = _xy.x; x = _xy.y; };
	void XZ(Vector2<T> const &_xy) { x = _xy.x; z = _xy.y; };
	void ZX(Vector2<T> const &_xy) { z = _xy.x; x = _xy.y; };
	void YZ(Vector2<T> const &_xy) { y = _xy.x; z = _xy.y; };
	void ZY(Vector2<T> const &_xy) { z = _xy.x; y = _xy.y; };
	void WX(Vector2<T> const &_xy) { w = _xy.x; x = _xy.y; };
	void XW(Vector2<T> const &_xy) { x = _xy.x; w = _xy.y; };
	void WZ(Vector2<T> const &_xy) { w = _xy.x; z = _xy.y; };
	void ZW(Vector2<T> const &_xy) { z = _xy.x; w = _xy.y; };
	void YW(Vector2<T> const &_xy) { y = _xy.x; w = _xy.y; };
	void WY(Vector2<T> const &_xy) { w = _xy.x; y = _xy.y; };

	void XYZ(T _x, T _y, T _z) { x = _x; y = _y; z = _z; }
	void XYW(T _x, T _y, T _z) { x = _x; y = _y; w = _z; }
	void XZW(T _x, T _y, T _z) { x = _x; z = _y; w = _z; }
	void XZY(T _x, T _y, T _z) { x = _x; z = _y; y = _z; }
	void XWY(T _x, T _y, T _z) { x = _x; w = _y; y = _z; }
	void XWZ(T _x, T _y, T _z) { x = _x; w = _y; z = _z; }
	void YZX(T _x, T _y, T _z) { y = _x; z = _y; x = _z; }
	void YZW(T _x, T _y, T _z) { y = _x; z = _y; w = _z; }
	void YWZ(T _x, T _y, T _z) { y = _x; w = _y; z = _z; }
	void YWX(T _x, T _y, T _z) { y = _x; w = _y; x = _z; }
	void YXW(T _x, T _y, T _z) { y = _x; x = _y; w = _z; }
	void YXZ(T _x, T _y, T _z) { y = _x; x = _y; z = _z; }
	void ZWY(T _x, T _y, T _z) { z = _x; w = _y; y = _z; }
	void ZWX(T _x, T _y, T _z) { z = _x; w = _y; x = _z; }
	void ZXW(T _x, T _y, T _z) { z = _x; x = _y; w = _z; }
	void ZXY(T _x, T _y, T _z) { z = _x; x = _y; y = _z; }
	void ZYW(T _x, T _y, T _z) { z = _x; y = _y; w = _z; }
	void ZYX(T _x, T _y, T _z) { z = _x; y = _y; x = _z; }
	void WXY(T _x, T _y, T _z) { w = _x; x = _y; y = _z; }
	void WXZ(T _x, T _y, T _z) { w = _x; x = _y; z = _z; }
	void WYZ(T _x, T _y, T _z) { w = _x; y = _y; z = _z; }
	void WYX(T _x, T _y, T _z) { w = _x; y = _y; x = _z; }
	void WZX(T _x, T _y, T _z) { w = _x; z = _y; x = _z; }
	void WZY(T _x, T _y, T _z) { w = _x; z = _y; y = _z; }
	void XYZ(Vector2<T> const &_xy, T _z) { x = _xy.x; y = _xy.y; z = _z; }
	void XYW(Vector2<T> const &_xy, T _z) { x = _xy.x; y = _xy.y; w = _z; }
	void XZW(Vector2<T> const &_xy, T _z) { x = _xy.x; z = _xy.y; w = _z; }
	void XZY(Vector2<T> const &_xy, T _z) { x = _xy.x; z = _xy.y; y = _z; }
	void XWY(Vector2<T> const &_xy, T _z) { x = _xy.x; w = _xy.y; y = _z; }
	void XWZ(Vector2<T> const &_xy, T _z) { x = _xy.x; w = _xy.y; z = _z; }
	void YZX(Vector2<T> const &_xy, T _z) { y = _xy.x; z = _xy.y; x = _z; }
	void YZW(Vector2<T> const &_xy, T _z) { y = _xy.x; z = _xy.y; w = _z; }
	void YWZ(Vector2<T> const &_xy, T _z) { y = _xy.x; w = _xy.y; z = _z; }
	void YWX(Vector2<T> const &_xy, T _z) { y = _xy.x; w = _xy.y; x = _z; }
	void YXW(Vector2<T> const &_xy, T _z) { y = _xy.x; x = _xy.y; w = _z; }
	void YXZ(Vector2<T> const &_xy, T _z) { y = _xy.x; x = _xy.y; z = _z; }
	void ZWY(Vector2<T> const &_xy, T _z) { z = _xy.x; w = _xy.y; y = _z; }
	void ZWX(Vector2<T> const &_xy, T _z) { z = _xy.x; w = _xy.y; x = _z; }
	void ZXW(Vector2<T> const &_xy, T _z) { z = _xy.x; x = _xy.y; w = _z; }
	void ZXY(Vector2<T> const &_xy, T _z) { z = _xy.x; x = _xy.y; y = _z; }
	void ZYW(Vector2<T> const &_xy, T _z) { z = _xy.x; y = _xy.y; w = _z; }
	void ZYX(Vector2<T> const &_xy, T _z) { z = _xy.x; y = _xy.y; x = _z; }
	void WXY(Vector2<T> const &_xy, T _z) { w = _xy.x; x = _xy.y; y = _z; }
	void WXZ(Vector2<T> const &_xy, T _z) { w = _xy.x; x = _xy.y; z = _z; }
	void WYZ(Vector2<T> const &_xy, T _z) { w = _xy.x; y = _xy.y; z = _z; }
	void WYX(Vector2<T> const &_xy, T _z) { w = _xy.x; y = _xy.y; x = _z; }
	void WZX(Vector2<T> const &_xy, T _z) { w = _xy.x; z = _xy.y; x = _z; }
	void WZY(Vector2<T> const &_xy, T _z) { w = _xy.x; z = _xy.y; y = _z; }
	void XYZ(T _x, Vector2<T> const &_yz) { x = _x; y = _yz.x; z = _yz.y; }
	void XYW(T _x, Vector2<T> const &_yz) { x = _x; y = _yz.x; w = _yz.y; }
	void XZW(T _x, Vector2<T> const &_yz) { x = _x; z = _yz.x; w = _yz.y; }
	void XZY(T _x, Vector2<T> const &_yz) { x = _x; z = _yz.x; y = _yz.y; }
	void XWY(T _x, Vector2<T> const &_yz) { x = _x; w = _yz.x; y = _yz.y; }
	void XWZ(T _x, Vector2<T> const &_yz) { x = _x; w = _yz.x; z = _yz.y; }
	void YZX(T _x, Vector2<T> const &_yz) { y = _x; z = _yz.x; x = _yz.y; }
	void YZW(T _x, Vector2<T> const &_yz) { y = _x; z = _yz.x; w = _yz.y; }
	void YWZ(T _x, Vector2<T> const &_yz) { y = _x; w = _yz.x; z = _yz.y; }
	void YWX(T _x, Vector2<T> const &_yz) { y = _x; w = _yz.x; x = _yz.y; }
	void YXW(T _x, Vector2<T> const &_yz) { y = _x; x = _yz.x; w = _yz.y; }
	void YXZ(T _x, Vector2<T> const &_yz) { y = _x; x = _yz.x; z = _yz.y; }
	void ZWY(T _x, Vector2<T> const &_yz) { z = _x; w = _yz.x; y = _yz.y; }
	void ZWX(T _x, Vector2<T> const &_yz) { z = _x; w = _yz.x; x = _yz.y; }
	void ZXW(T _x, Vector2<T> const &_yz) { z = _x; x = _yz.x; w = _yz.y; }
	void ZXY(T _x, Vector2<T> const &_yz) { z = _x; x = _yz.x; y = _yz.y; }
	void ZYW(T _x, Vector2<T> const &_yz) { z = _x; y = _yz.x; w = _yz.y; }
	void ZYX(T _x, Vector2<T> const &_yz) { z = _x; y = _yz.x; x = _yz.y; }
	void WXY(T _x, Vector2<T> const &_yz) { w = _x; x = _yz.x; y = _yz.y; }
	void WXZ(T _x, Vector2<T> const &_yz) { w = _x; x = _yz.x; z = _yz.y; }
	void WYZ(T _x, Vector2<T> const &_yz) { w = _x; y = _yz.x; z = _yz.y; }
	void WYX(T _x, Vector2<T> const &_yz) { w = _x; y = _yz.x; x = _yz.y; }
	void WZX(T _x, Vector2<T> const &_yz) { w = _x; z = _yz.x; x = _yz.y; }
	void WZY(T _x, Vector2<T> const &_yz) { w = _x; z = _yz.x; y = _yz.y; }
	void XYZ(Vector3<T> const &_xyz) { x = _xyz.x; y = _xyz.y; z = _xyz.z; }
	void XYW(Vector3<T> const &_xyz) { x = _xyz.x; y = _xyz.y; w = _xyz.z; }
	void XZW(Vector3<T> const &_xyz) { x = _xyz.x; z = _xyz.y; w = _xyz.z; }
	void XZY(Vector3<T> const &_xyz) { x = _xyz.x; z = _xyz.y; y = _xyz.z; }
	void XWY(Vector3<T> const &_xyz) { x = _xyz.x; w = _xyz.y; y = _xyz.z; }
	void XWZ(Vector3<T> const &_xyz) { x = _xyz.x; w = _xyz.y; z = _xyz.z; }
	void YZX(Vector3<T> const &_xyz) { y = _xyz.x; z = _xyz.y; x = _xyz.z; }
	void YZW(Vector3<T> const &_xyz) { y = _xyz.x; z = _xyz.y; w = _xyz.z; }
	void YWZ(Vector3<T> const &_xyz) { y = _xyz.x; w = _xyz.y; z = _xyz.z; }
	void YWX(Vector3<T> const &_xyz) { y = _xyz.x; w = _xyz.y; x = _xyz.z; }
	void YXW(Vector3<T> const &_xyz) { y = _xyz.x; x = _xyz.y; w = _xyz.z; }
	void YXZ(Vector3<T> const &_xyz) { y = _xyz.x; x = _xyz.y; z = _xyz.z; }
	void ZWY(Vector3<T> const &_xyz) { z = _xyz.x; w = _xyz.y; y = _xyz.z; }
	void ZWX(Vector3<T> const &_xyz) { z = _xyz.x; w = _xyz.y; x = _xyz.z; }
	void ZXW(Vector3<T> const &_xyz) { z = _xyz.x; x = _xyz.y; w = _xyz.z; }
	void ZXY(Vector3<T> const &_xyz) { z = _xyz.x; x = _xyz.y; y = _xyz.z; }
	void ZYW(Vector3<T> const &_xyz) { z = _xyz.x; y = _xyz.y; w = _xyz.z; }
	void ZYX(Vector3<T> const &_xyz) { z = _xyz.x; y = _xyz.y; x = _xyz.z; }
	void WXY(Vector3<T> const &_xyz) { w = _xyz.x; x = _xyz.y; y = _xyz.z; }
	void WXZ(Vector3<T> const &_xyz) { w = _xyz.x; x = _xyz.y; z = _xyz.z; }
	void WYZ(Vector3<T> const &_xyz) { w = _xyz.x; y = _xyz.y; z = _xyz.z; }
	void WYX(Vector3<T> const &_xyz) { w = _xyz.x; y = _xyz.y; x = _xyz.z; }
	void WZX(Vector3<T> const &_xyz) { w = _xyz.x; z = _xyz.y; x = _xyz.z; }
	void WZY(Vector3<T> const &_xyz) { w = _xyz.x; z = _xyz.y; y = _xyz.z; }

	void XYZW(T _x, T _y, T _z, T _w) { x = _x; y = _y; z = _z; w = _w; }
	void XYWZ(T _x, T _y, T _z, T _w) { x = _x; y = _y; w = _z; z = _w; }
	void XZWY(T _x, T _y, T _z, T _w) { x = _x; z = _y; w = _z; y = _w; }
	void XZYW(T _x, T _y, T _z, T _w) { x = _x; z = _y; y = _z; w = _w; }
	void XWYZ(T _x, T _y, T _z, T _w) { x = _x; w = _y; y = _z; z = _w; }
	void XWZY(T _x, T _y, T _z, T _w) { x = _x; w = _y; z = _z; y = _w; }
	void YZXW(T _x, T _y, T _z, T _w) { y = _x; z = _y; x = _z; w = _w; }
	void YZWX(T _x, T _y, T _z, T _w) { y = _x; z = _y; w = _z; x = _w; }
	void YWZX(T _x, T _y, T _z, T _w) { y = _x; w = _y; z = _z; x = _w; }
	void YWXZ(T _x, T _y, T _z, T _w) { y = _x; w = _y; x = _z; z = _w; }
	void YXWZ(T _x, T _y, T _z, T _w) { y = _x; x = _y; w = _z; z = _w; }
	void YXZW(T _x, T _y, T _z, T _w) { y = _x; x = _y; z = _z; w = _w; }
	void ZWYX(T _x, T _y, T _z, T _w) { z = _x; w = _y; y = _z; x = _w; }
	void ZWXY(T _x, T _y, T _z, T _w) { z = _x; w = _y; x = _z; y = _w; }
	void ZXWY(T _x, T _y, T _z, T _w) { z = _x; x = _y; w = _z; y = _w; }
	void ZXYW(T _x, T _y, T _z, T _w) { z = _x; x = _y; y = _z; w = _w; }
	void ZYWX(T _x, T _y, T _z, T _w) { z = _x; y = _y; w = _z; x = _w; }
	void ZYXW(T _x, T _y, T _z, T _w) { z = _x; y = _y; x = _z; w = _w; }
	void WXYZ(T _x, T _y, T _z, T _w) { w = _x; x = _y; y = _z; z = _w; }
	void WXZY(T _x, T _y, T _z, T _w) { w = _x; x = _y; z = _z; y = _w; }
	void WYZX(T _x, T _y, T _z, T _w) { w = _x; y = _y; z = _z; x = _w; }
	void WYXZ(T _x, T _y, T _z, T _w) { w = _x; y = _y; x = _z; z = _w; }
	void WZXY(T _x, T _y, T _z, T _w) { w = _x; z = _y; x = _z; y = _w; }
	void WZYX(T _x, T _y, T _z, T _w) { w = _x; z = _y; y = _z; x = _w; }
	void XYZW(Vector2<T> const &_xy, T _z, T _w) { x = _xy.x; y = _xy.y; z = _z; w = _w; }
	void XYWZ(Vector2<T> const &_xy, T _z, T _w) { x = _xy.x; y = _xy.y; w = _z; z = _w; }
	void XZWY(Vector2<T> const &_xy, T _z, T _w) { x = _xy.x; z = _xy.y; w = _z; y = _w; }
	void XZYW(Vector2<T> const &_xy, T _z, T _w) { x = _xy.x; z = _xy.y; y = _z; w = _w; }
	void XWYZ(Vector2<T> const &_xy, T _z, T _w) { x = _xy.x; w = _xy.y; y = _z; z = _w; }
	void XWZY(Vector2<T> const &_xy, T _z, T _w) { x = _xy.x; w = _xy.y; z = _z; y = _w; }
	void YZXW(Vector2<T> const &_xy, T _z, T _w) { y = _xy.x; z = _xy.y; x = _z; w = _w; }
	void YZWX(Vector2<T> const &_xy, T _z, T _w) { y = _xy.x; z = _xy.y; w = _z; x = _w; }
	void YWZX(Vector2<T> const &_xy, T _z, T _w) { y = _xy.x; w = _xy.y; z = _z; x = _w; }
	void YWXZ(Vector2<T> const &_xy, T _z, T _w) { y = _xy.x; w = _xy.y; x = _z; z = _w; }
	void YXWZ(Vector2<T> const &_xy, T _z, T _w) { y = _xy.x; x = _xy.y; w = _z; z = _w; }
	void YXZW(Vector2<T> const &_xy, T _z, T _w) { y = _xy.x; x = _xy.y; z = _z; w = _w; }
	void ZWYX(Vector2<T> const &_xy, T _z, T _w) { z = _xy.x; w = _xy.y; y = _z; x = _w; }
	void ZWXY(Vector2<T> const &_xy, T _z, T _w) { z = _xy.x; w = _xy.y; x = _z; y = _w; }
	void ZXWY(Vector2<T> const &_xy, T _z, T _w) { z = _xy.x; x = _xy.y; w = _z; y = _w; }
	void ZXYW(Vector2<T> const &_xy, T _z, T _w) { z = _xy.x; x = _xy.y; y = _z; w = _w; }
	void ZYWX(Vector2<T> const &_xy, T _z, T _w) { z = _xy.x; y = _xy.y; w = _z; x = _w; }
	void ZYXW(Vector2<T> const &_xy, T _z, T _w) { z = _xy.x; y = _xy.y; x = _z; w = _w; }
	void WXYZ(Vector2<T> const &_xy, T _z, T _w) { w = _xy.x; x = _xy.y; y = _z; z = _w; }
	void WXZY(Vector2<T> const &_xy, T _z, T _w) { w = _xy.x; x = _xy.y; z = _z; y = _w; }
	void WYZX(Vector2<T> const &_xy, T _z, T _w) { w = _xy.x; y = _xy.y; z = _z; x = _w; }
	void WYXZ(Vector2<T> const &_xy, T _z, T _w) { w = _xy.x; y = _xy.y; x = _z; z = _w; }
	void WZXY(Vector2<T> const &_xy, T _z, T _w) { w = _xy.x; z = _xy.y; x = _z; y = _w; }
	void WZYX(Vector2<T> const &_xy, T _z, T _w) { w = _xy.x; z = _xy.y; y = _z; x = _w; }
	void XYZW(T _x, Vector2<T> const &_yz, T _w) { x = _x; y = _yz.x; z = _yz.y; w = _w; }
	void XYWZ(T _x, Vector2<T> const &_yz, T _w) { x = _x; y = _yz.x; w = _yz.y; z = _w; }
	void XZWY(T _x, Vector2<T> const &_yz, T _w) { x = _x; z = _yz.x; w = _yz.y; y = _w; }
	void XZYW(T _x, Vector2<T> const &_yz, T _w) { x = _x; z = _yz.x; y = _yz.y; w = _w; }
	void XWYZ(T _x, Vector2<T> const &_yz, T _w) { x = _x; w = _yz.x; y = _yz.y; z = _w; }
	void XWZY(T _x, Vector2<T> const &_yz, T _w) { x = _x; w = _yz.x; z = _yz.y; y = _w; }
	void YZXW(T _x, Vector2<T> const &_yz, T _w) { y = _x; z = _yz.x; x = _yz.y; w = _w; }
	void YZWX(T _x, Vector2<T> const &_yz, T _w) { y = _x; z = _yz.x; w = _yz.y; x = _w; }
	void YWZX(T _x, Vector2<T> const &_yz, T _w) { y = _x; w = _yz.x; z = _yz.y; x = _w; }
	void YWXZ(T _x, Vector2<T> const &_yz, T _w) { y = _x; w = _yz.x; x = _yz.y; z = _w; }
	void YXWZ(T _x, Vector2<T> const &_yz, T _w) { y = _x; x = _yz.x; w = _yz.y; z = _w; }
	void YXZW(T _x, Vector2<T> const &_yz, T _w) { y = _x; x = _yz.x; z = _yz.y; w = _w; }
	void ZWYX(T _x, Vector2<T> const &_yz, T _w) { z = _x; w = _yz.x; y = _yz.y; x = _w; }
	void ZWXY(T _x, Vector2<T> const &_yz, T _w) { z = _x; w = _yz.x; x = _yz.y; y = _w; }
	void ZXWY(T _x, Vector2<T> const &_yz, T _w) { z = _x; x = _yz.x; w = _yz.y; y = _w; }
	void ZXYW(T _x, Vector2<T> const &_yz, T _w) { z = _x; x = _yz.x; y = _yz.y; w = _w; }
	void ZYWX(T _x, Vector2<T> const &_yz, T _w) { z = _x; y = _yz.x; w = _yz.y; x = _w; }
	void ZYXW(T _x, Vector2<T> const &_yz, T _w) { z = _x; y = _yz.x; x = _yz.y; w = _w; }
	void WXYZ(T _x, Vector2<T> const &_yz, T _w) { w = _x; x = _yz.x; y = _yz.y; z = _w; }
	void WXZY(T _x, Vector2<T> const &_yz, T _w) { w = _x; x = _yz.x; z = _yz.y; y = _w; }
	void WYZX(T _x, Vector2<T> const &_yz, T _w) { w = _x; y = _yz.x; z = _yz.y; x = _w; }
	void WYXZ(T _x, Vector2<T> const &_yz, T _w) { w = _x; y = _yz.x; x = _yz.y; z = _w; }
	void WZXY(T _x, Vector2<T> const &_yz, T _w) { w = _x; z = _yz.x; x = _yz.y; y = _w; }
	void WZYX(T _x, Vector2<T> const &_yz, T _w) { w = _x; z = _yz.x; y = _yz.y; x = _w; }
	void XYZW(T _x, T _y, Vector2<T> const &_zw) { x = _x; y = _y; z = _zw.x; w = _zw.y; }
	void XYWZ(T _x, T _y, Vector2<T> const &_zw) { x = _x; y = _y; w = _zw.x; z = _zw.y; }
	void XZWY(T _x, T _y, Vector2<T> const &_zw) { x = _x; z = _y; w = _zw.x; y = _zw.y; }
	void XZYW(T _x, T _y, Vector2<T> const &_zw) { x = _x; z = _y; y = _zw.x; w = _zw.y; }
	void XWYZ(T _x, T _y, Vector2<T> const &_zw) { x = _x; w = _y; y = _zw.x; z = _zw.y; }
	void XWZY(T _x, T _y, Vector2<T> const &_zw) { x = _x; w = _y; z = _zw.x; y = _zw.y; }
	void YZXW(T _x, T _y, Vector2<T> const &_zw) { y = _x; z = _y; x = _zw.x; w = _zw.y; }
	void YZWX(T _x, T _y, Vector2<T> const &_zw) { y = _x; z = _y; w = _zw.x; x = _zw.y; }
	void YWZX(T _x, T _y, Vector2<T> const &_zw) { y = _x; w = _y; z = _zw.x; x = _zw.y; }
	void YWXZ(T _x, T _y, Vector2<T> const &_zw) { y = _x; w = _y; x = _zw.x; z = _zw.y; }
	void YXWZ(T _x, T _y, Vector2<T> const &_zw) { y = _x; x = _y; w = _zw.x; z = _zw.y; }
	void YXZW(T _x, T _y, Vector2<T> const &_zw) { y = _x; x = _y; z = _zw.x; w = _zw.y; }
	void ZWYX(T _x, T _y, Vector2<T> const &_zw) { z = _x; w = _y; y = _zw.x; x = _zw.y; }
	void ZWXY(T _x, T _y, Vector2<T> const &_zw) { z = _x; w = _y; x = _zw.x; y = _zw.y; }
	void ZXWY(T _x, T _y, Vector2<T> const &_zw) { z = _x; x = _y; w = _zw.x; y = _zw.y; }
	void ZXYW(T _x, T _y, Vector2<T> const &_zw) { z = _x; x = _y; y = _zw.x; w = _zw.y; }
	void ZYWX(T _x, T _y, Vector2<T> const &_zw) { z = _x; y = _y; w = _zw.x; x = _zw.y; }
	void ZYXW(T _x, T _y, Vector2<T> const &_zw) { z = _x; y = _y; x = _zw.x; w = _zw.y; }
	void WXYZ(T _x, T _y, Vector2<T> const &_zw) { w = _x; x = _y; y = _zw.x; z = _zw.y; }
	void WXZY(T _x, T _y, Vector2<T> const &_zw) { w = _x; x = _y; z = _zw.x; y = _zw.y; }
	void WYZX(T _x, T _y, Vector2<T> const &_zw) { w = _x; y = _y; z = _zw.x; x = _zw.y; }
	void WYXZ(T _x, T _y, Vector2<T> const &_zw) { w = _x; y = _y; x = _zw.x; z = _zw.y; }
	void WZXY(T _x, T _y, Vector2<T> const &_zw) { w = _x; z = _y; x = _zw.x; y = _zw.y; }
	void WZYX(T _x, T _y, Vector2<T> const &_zw) { w = _x; z = _y; y = _zw.x; x = _zw.y; }
	void XYZW(Vector2<T> const &_xy, Vector2<T> const &_zw) { x = _xy.x; y = _xy.y; z = _zw.x; w = _zw.y; }
	void XYWZ(Vector2<T> const &_xy, Vector2<T> const &_zw) { x = _xy.x; y = _xy.y; w = _zw.x; z = _zw.y; }
	void XZWY(Vector2<T> const &_xy, Vector2<T> const &_zw) { x = _xy.x; z = _xy.y; w = _zw.x; y = _zw.y; }
	void XZYW(Vector2<T> const &_xy, Vector2<T> const &_zw) { x = _xy.x; z = _xy.y; y = _zw.x; w = _zw.y; }
	void XWYZ(Vector2<T> const &_xy, Vector2<T> const &_zw) { x = _xy.x; w = _xy.y; y = _zw.x; z = _zw.y; }
	void XWZY(Vector2<T> const &_xy, Vector2<T> const &_zw) { x = _xy.x; w = _xy.y; z = _zw.x; y = _zw.y; }
	void YZXW(Vector2<T> const &_xy, Vector2<T> const &_zw) { y = _xy.x; z = _xy.y; x = _zw.x; w = _zw.y; }
	void YZWX(Vector2<T> const &_xy, Vector2<T> const &_zw) { y = _xy.x; z = _xy.y; w = _zw.x; x = _zw.y; }
	void YWZX(Vector2<T> const &_xy, Vector2<T> const &_zw) { y = _xy.x; w = _xy.y; z = _zw.x; x = _zw.y; }
	void YWXZ(Vector2<T> const &_xy, Vector2<T> const &_zw) { y = _xy.x; w = _xy.y; x = _zw.x; z = _zw.y; }
	void YXWZ(Vector2<T> const &_xy, Vector2<T> const &_zw) { y = _xy.x; x = _xy.y; w = _zw.x; z = _zw.y; }
	void YXZW(Vector2<T> const &_xy, Vector2<T> const &_zw) { y = _xy.x; x = _xy.y; z = _zw.x; w = _zw.y; }
	void ZWYX(Vector2<T> const &_xy, Vector2<T> const &_zw) { z = _xy.x; w = _xy.y; y = _zw.x; x = _zw.y; }
	void ZWXY(Vector2<T> const &_xy, Vector2<T> const &_zw) { z = _xy.x; w = _xy.y; x = _zw.x; y = _zw.y; }
	void ZXWY(Vector2<T> const &_xy, Vector2<T> const &_zw) { z = _xy.x; x = _xy.y; w = _zw.x; y = _zw.y; }
	void ZXYW(Vector2<T> const &_xy, Vector2<T> const &_zw) { z = _xy.x; x = _xy.y; y = _zw.x; w = _zw.y; }
	void ZYWX(Vector2<T> const &_xy, Vector2<T> const &_zw) { z = _xy.x; y = _xy.y; w = _zw.x; x = _zw.y; }
	void ZYXW(Vector2<T> const &_xy, Vector2<T> const &_zw) { z = _xy.x; y = _xy.y; x = _zw.x; w = _zw.y; }
	void WXYZ(Vector2<T> const &_xy, Vector2<T> const &_zw) { w = _xy.x; x = _xy.y; y = _zw.x; z = _zw.y; }
	void WXZY(Vector2<T> const &_xy, Vector2<T> const &_zw) { w = _xy.x; x = _xy.y; z = _zw.x; y = _zw.y; }
	void WYZX(Vector2<T> const &_xy, Vector2<T> const &_zw) { w = _xy.x; y = _xy.y; z = _zw.x; x = _zw.y; }
	void WYXZ(Vector2<T> const &_xy, Vector2<T> const &_zw) { w = _xy.x; y = _xy.y; x = _zw.x; z = _zw.y; }
	void WZXY(Vector2<T> const &_xy, Vector2<T> const &_zw) { w = _xy.x; z = _xy.y; x = _zw.x; y = _zw.y; }
	void WZYX(Vector2<T> const &_xy, Vector2<T> const &_zw) { w = _xy.x; z = _xy.y; y = _zw.x; x = _zw.y; }
	void XYZW(Vector3<T> const &_xyz, T _w) { x = _xyz.x; y = _xyz.y; z = _xyz.z; w = _w; }
	void XYWZ(Vector3<T> const &_xyz, T _w) { x = _xyz.x; y = _xyz.y; w = _xyz.z; z = _w; }
	void XZWY(Vector3<T> const &_xyz, T _w) { x = _xyz.x; z = _xyz.y; w = _xyz.z; y = _w; }
	void XZYW(Vector3<T> const &_xyz, T _w) { x = _xyz.x; z = _xyz.y; y = _xyz.z; w = _w; }
	void XWYZ(Vector3<T> const &_xyz, T _w) { x = _xyz.x; w = _xyz.y; y = _xyz.z; z = _w; }
	void XWZY(Vector3<T> const &_xyz, T _w) { x = _xyz.x; w = _xyz.y; z = _xyz.z; y = _w; }
	void YZXW(Vector3<T> const &_xyz, T _w) { y = _xyz.x; z = _xyz.y; x = _xyz.z; w = _w; }
	void YZWX(Vector3<T> const &_xyz, T _w) { y = _xyz.x; z = _xyz.y; w = _xyz.z; x = _w; }
	void YWZX(Vector3<T> const &_xyz, T _w) { y = _xyz.x; w = _xyz.y; z = _xyz.z; x = _w; }
	void YWXZ(Vector3<T> const &_xyz, T _w) { y = _xyz.x; w = _xyz.y; x = _xyz.z; z = _w; }
	void YXWZ(Vector3<T> const &_xyz, T _w) { y = _xyz.x; x = _xyz.y; w = _xyz.z; z = _w; }
	void YXZW(Vector3<T> const &_xyz, T _w) { y = _xyz.x; x = _xyz.y; z = _xyz.z; w = _w; }
	void ZWYX(Vector3<T> const &_xyz, T _w) { z = _xyz.x; w = _xyz.y; y = _xyz.z; x = _w; }
	void ZWXY(Vector3<T> const &_xyz, T _w) { z = _xyz.x; w = _xyz.y; x = _xyz.z; y = _w; }
	void ZXWY(Vector3<T> const &_xyz, T _w) { z = _xyz.x; x = _xyz.y; w = _xyz.z; y = _w; }
	void ZXYW(Vector3<T> const &_xyz, T _w) { z = _xyz.x; x = _xyz.y; y = _xyz.z; w = _w; }
	void ZYWX(Vector3<T> const &_xyz, T _w) { z = _xyz.x; y = _xyz.y; w = _xyz.z; x = _w; }
	void ZYXW(Vector3<T> const &_xyz, T _w) { z = _xyz.x; y = _xyz.y; x = _xyz.z; w = _w; }
	void WXYZ(Vector3<T> const &_xyz, T _w) { w = _xyz.x; x = _xyz.y; y = _xyz.z; z = _w; }
	void WXZY(Vector3<T> const &_xyz, T _w) { w = _xyz.x; x = _xyz.y; z = _xyz.z; y = _w; }
	void WYZX(Vector3<T> const &_xyz, T _w) { w = _xyz.x; y = _xyz.y; z = _xyz.z; x = _w; }
	void WYXZ(Vector3<T> const &_xyz, T _w) { w = _xyz.x; y = _xyz.y; x = _xyz.z; z = _w; }
	void WZXY(Vector3<T> const &_xyz, T _w) { w = _xyz.x; z = _xyz.y; x = _xyz.z; y = _w; }
	void WZYX(Vector3<T> const &_xyz, T _w) { w = _xyz.x; z = _xyz.y; y = _xyz.z; x = _w; }
	void XYZW(T _x, Vector3<T> const &_yzw) { x = _x; y = _yzw.x; z = _yzw.y; w = _yzw.z; }
	void XYWZ(T _x, Vector3<T> const &_yzw) { x = _x; y = _yzw.x; w = _yzw.y; z = _yzw.z; }
	void XZWY(T _x, Vector3<T> const &_yzw) { x = _x; z = _yzw.x; w = _yzw.y; y = _yzw.z; }
	void XZYW(T _x, Vector3<T> const &_yzw) { x = _x; z = _yzw.x; y = _yzw.y; w = _yzw.z; }
	void XWYZ(T _x, Vector3<T> const &_yzw) { x = _x; w = _yzw.x; y = _yzw.y; z = _yzw.z; }
	void XWZY(T _x, Vector3<T> const &_yzw) { x = _x; w = _yzw.x; z = _yzw.y; y = _yzw.z; }
	void YZXW(T _x, Vector3<T> const &_yzw) { y = _x; z = _yzw.x; x = _yzw.y; w = _yzw.z; }
	void YZWX(T _x, Vector3<T> const &_yzw) { y = _x; z = _yzw.x; w = _yzw.y; x = _yzw.z; }
	void YWZX(T _x, Vector3<T> const &_yzw) { y = _x; w = _yzw.x; z = _yzw.y; x = _yzw.z; }
	void YWXZ(T _x, Vector3<T> const &_yzw) { y = _x; w = _yzw.x; x = _yzw.y; z = _yzw.z; }
	void YXWZ(T _x, Vector3<T> const &_yzw) { y = _x; x = _yzw.x; w = _yzw.y; z = _yzw.z; }
	void YXZW(T _x, Vector3<T> const &_yzw) { y = _x; x = _yzw.x; z = _yzw.y; w = _yzw.z; }
	void ZWYX(T _x, Vector3<T> const &_yzw) { z = _x; w = _yzw.x; y = _yzw.y; x = _yzw.z; }
	void ZWXY(T _x, Vector3<T> const &_yzw) { z = _x; w = _yzw.x; x = _yzw.y; y = _yzw.z; }
	void ZXWY(T _x, Vector3<T> const &_yzw) { z = _x; x = _yzw.x; w = _yzw.y; y = _yzw.z; }
	void ZXYW(T _x, Vector3<T> const &_yzw) { z = _x; x = _yzw.x; y = _yzw.y; w = _yzw.z; }
	void ZYWX(T _x, Vector3<T> const &_yzw) { z = _x; y = _yzw.x; w = _yzw.y; x = _yzw.z; }
	void ZYXW(T _x, Vector3<T> const &_yzw) { z = _x; y = _yzw.x; x = _yzw.y; w = _yzw.z; }
	void WXYZ(T _x, Vector3<T> const &_yzw) { w = _x; x = _yzw.x; y = _yzw.y; z = _yzw.z; }
	void WXZY(T _x, Vector3<T> const &_yzw) { w = _x; x = _yzw.x; z = _yzw.y; y = _yzw.z; }
	void WYZX(T _x, Vector3<T> const &_yzw) { w = _x; y = _yzw.x; z = _yzw.y; x = _yzw.z; }
	void WYXZ(T _x, Vector3<T> const &_yzw) { w = _x; y = _yzw.x; x = _yzw.y; z = _yzw.z; }
	void WZXY(T _x, Vector3<T> const &_yzw) { w = _x; z = _yzw.x; x = _yzw.y; y = _yzw.z; }
	void WZYX(T _x, Vector3<T> const &_yzw) { w = _x; z = _yzw.x; y = _yzw.y; x = _yzw.z; }
	void XYZW(Vector4<T> const &_xyzw) { x = _xyzw.x; y = _xyzw.y; z = _xyzw.z; w = _xyzw.w; }
	void XYWZ(Vector4<T> const &_xyzw) { x = _xyzw.x; y = _xyzw.y; w = _xyzw.z; z = _xyzw.w; }
	void XZWY(Vector4<T> const &_xyzw) { x = _xyzw.x; z = _xyzw.y; w = _xyzw.z; y = _xyzw.w; }
	void XZYW(Vector4<T> const &_xyzw) { x = _xyzw.x; z = _xyzw.y; y = _xyzw.z; w = _xyzw.w; }
	void XWYZ(Vector4<T> const &_xyzw) { x = _xyzw.x; w = _xyzw.y; y = _xyzw.z; z = _xyzw.w; }
	void XWZY(Vector4<T> const &_xyzw) { x = _xyzw.x; w = _xyzw.y; z = _xyzw.z; y = _xyzw.w; }
	void YZXW(Vector4<T> const &_xyzw) { y = _xyzw.x; z = _xyzw.y; x = _xyzw.z; w = _xyzw.w; }
	void YZWX(Vector4<T> const &_xyzw) { y = _xyzw.x; z = _xyzw.y; w = _xyzw.z; x = _xyzw.w; }
	void YWZX(Vector4<T> const &_xyzw) { y = _xyzw.x; w = _xyzw.y; z = _xyzw.z; x = _xyzw.w; }
	void YWXZ(Vector4<T> const &_xyzw) { y = _xyzw.x; w = _xyzw.y; x = _xyzw.z; z = _xyzw.w; }
	void YXWZ(Vector4<T> const &_xyzw) { y = _xyzw.x; x = _xyzw.y; w = _xyzw.z; z = _xyzw.w; }
	void YXZW(Vector4<T> const &_xyzw) { y = _xyzw.x; x = _xyzw.y; z = _xyzw.z; w = _xyzw.w; }
	void ZWYX(Vector4<T> const &_xyzw) { z = _xyzw.x; w = _xyzw.y; y = _xyzw.z; x = _xyzw.w; }
	void ZWXY(Vector4<T> const &_xyzw) { z = _xyzw.x; w = _xyzw.y; x = _xyzw.z; y = _xyzw.w; }
	void ZXWY(Vector4<T> const &_xyzw) { z = _xyzw.x; x = _xyzw.y; w = _xyzw.z; y = _xyzw.w; }
	void ZXYW(Vector4<T> const &_xyzw) { z = _xyzw.x; x = _xyzw.y; y = _xyzw.z; w = _xyzw.w; }
	void ZYWX(Vector4<T> const &_xyzw) { z = _xyzw.x; y = _xyzw.y; w = _xyzw.z; x = _xyzw.w; }
	void ZYXW(Vector4<T> const &_xyzw) { z = _xyzw.x; y = _xyzw.y; x = _xyzw.z; w = _xyzw.w; }
	void WXYZ(Vector4<T> const &_xyzw) { w = _xyzw.x; x = _xyzw.y; y = _xyzw.z; z = _xyzw.w; }
	void WXZY(Vector4<T> const &_xyzw) { w = _xyzw.x; x = _xyzw.y; z = _xyzw.z; y = _xyzw.w; }
	void WYZX(Vector4<T> const &_xyzw) { w = _xyzw.x; y = _xyzw.y; z = _xyzw.z; x = _xyzw.w; }
	void WYXZ(Vector4<T> const &_xyzw) { w = _xyzw.x; y = _xyzw.y; x = _xyzw.z; z = _xyzw.w; }
	void WZXY(Vector4<T> const &_xyzw) { w = _xyzw.x; z = _xyzw.y; x = _xyzw.z; y = _xyzw.w; }
	void WZYX(Vector4<T> const &_xyzw) { w = _xyzw.x; z = _xyzw.y; y = _xyzw.z; x = _xyzw.w; }

#pragma endregion

};

typedef Vector4<float> Vec4;
typedef Vector4<int> Vec4i;

#endif