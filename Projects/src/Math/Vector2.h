#ifndef VECTOR2_H
#define VECTOR2_H

template<typename T>
struct Vector2
{
	union
	{
		struct { T x, y; };
		T components[2];
	};

	Vector2() {};

	Vector2(T _x, T _y) : x(_x), y(_y) {};

	Vector2(Vector2<T> const &other) : Vector2<T>(other.x, other.y) {};

	T X() const { return x; }
	T Y() const { return y; }
	Vector2<T> XY() const { return{ x, y }; }
	Vector2<T> YX() const { return{ y, x }; }

	void X(T _x) { x = _x };
	void Y(T _y) { y = _y };

	void XY(Vector2<T> const &_xy) { x = _xy.x; y = _xy.y; };
	void YX(Vector2<T> const &_yx) { y = _xy.x; x = _xy.y; };
	void XY(T _x, T _y) { x = _x; y = _y; };
	void YX(T _x, T _y) { y = _x; x = _y; };

	float Length() const { return sqrt((float)LengthSquared()); }
	T LengthSquared() const { return Dot2(*this, *this); }
	Vector2<float> Normalise() const { return Vector2<float>(*this) / Length(); }

	T const &operator[](size_t index) const { return components[index]; }
	T &operator[](size_t index) { return components[index]; }

	friend Vector2<T> operator+(Vector2<T> lhs, Vector2<T> const &rhs) { lhs.x += rhs.x; lhs.y += rhs.y; return lhs; }
	friend Vector2<T> operator-(Vector2<T> lhs, Vector2<T> const &rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; return lhs; }
	friend Vector2<T> operator*(Vector2<T> lhs, Vector2<T> const &rhs) { lhs.x *= rhs.x; lhs.y *= rhs.y; return lhs; }
	friend Vector2<T> operator/(Vector2<T> lhs, Vector2<T> const &rhs) { lhs.x /= rhs.x; lhs.y /= rhs.y; return lhs; }

	//template<typename T2> friend Vector2<T> operator+(Vector2<T> lhs, Vector2<T2> const &rhs) { lhs.x += rhs.x; lhs.y += rhs.y; return lhs; }
	//template<typename T2> friend Vector2<T> operator-(Vector2<T> lhs, Vector2<T2> const &rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; return lhs; }
	//template<typename T2> friend Vector2<T> operator*(Vector2<T> lhs, Vector2<T2> const &rhs) { lhs.x *= rhs.x; lhs.y *= rhs.y; return lhs; }
	//template<typename T2> friend Vector2<T> operator/(Vector2<T> lhs, Vector2<T2> const &rhs) { lhs.x /= rhs.x; lhs.y /= rhs.y; return lhs; }

	//friend Vector2<T> operator+(Vector2<T> const &lhs, Vector2<T> rhs) { rhs.x = lhs.x + rhs.x; rhs.y = lhs.y + rhs.y; return rhs; }
	//friend Vector2<T> operator-(Vector2<T> const &lhs, Vector2<T> rhs) { rhs.x = lhs.x - rhs.x; rhs.y = lhs.y - rhs.y; return rhs; }
	//friend Vector2<T> operator*(Vector2<T> const &lhs, Vector2<T> rhs) { rhs.x = lhs.x * rhs.x; rhs.y = lhs.y * rhs.y; return rhs; }
	//friend Vector2<T> operator/(Vector2<T> const &lhs, Vector2<T> rhs) { rhs.x = lhs.x / rhs.x; rhs.y = lhs.y / rhs.y; return rhs; }

	//template<typename T2> friend Vector2<T> operator+(Vector2<T2> const &lhs, Vector2<T> rhs) { rhs.x = lhs.x + rhs.x; rhs.y = lhs.y + rhs.y; return rhs; }
	//template<typename T2> friend Vector2<T> operator-(Vector2<T2> const &lhs, Vector2<T> rhs) { rhs.x = lhs.x - rhs.x; rhs.y = lhs.y - rhs.y; return rhs; }
	//template<typename T2> friend Vector2<T> operator*(Vector2<T2> const &lhs, Vector2<T> rhs) { rhs.x = lhs.x * rhs.x; rhs.y = lhs.y * rhs.y; return rhs; }
	//template<typename T2> friend Vector2<T> operator/(Vector2<T2> const &lhs, Vector2<T> rhs) { rhs.x = lhs.x / rhs.x; rhs.y = lhs.y / rhs.y; return rhs; }

	friend Vector2<T> operator+(Vector2<T> lhs, T const &rhs) { lhs.x += rhs; lhs.y += rhs; return lhs; }
	friend Vector2<T> operator-(Vector2<T> lhs, T const &rhs) { lhs.x -= rhs; lhs.y -= rhs; return lhs; }
	friend Vector2<T> operator*(Vector2<T> lhs, T const &rhs) { lhs.x *= rhs; lhs.y *= rhs; return lhs; }
	friend Vector2<T> operator/(Vector2<T> lhs, T const &rhs) { lhs.x /= rhs; lhs.y /= rhs; return lhs; }

	//template<typename T2> friend Vector2<T> operator+(Vector2<T> lhs, T2 const &rhs) { lhs.x += rhs; lhs.y += rhs; return lhs; }
	//template<typename T2> friend Vector2<T> operator-(Vector2<T> lhs, T2 const &rhs) { lhs.x -= rhs; lhs.y -= rhs; return lhs; }
	//template<typename T2> friend Vector2<T> operator*(Vector2<T> lhs, T2 const &rhs) { lhs.x *= rhs; lhs.y *= rhs; return lhs; }
	//template<typename T2> friend Vector2<T> operator/(Vector2<T> lhs, T2 const &rhs) { lhs.x /= rhs; lhs.y /= rhs; return lhs; }

	//friend Vector2<T> operator+(T const &lhs, Vector2<T> rhs) { rhs.x = lhs + rhs.x; rhs.y = lhs + rhs.y; return rhs; }
	//friend Vector2<T> operator-(T const &lhs, Vector2<T> rhs) { rhs.x = lhs - rhs.x; rhs.y = lhs + rhs.y; return rhs; }
	//friend Vector2<T> operator*(T const &lhs, Vector2<T> rhs) { rhs.x = lhs * rhs.x; rhs.y = lhs + rhs.y; return rhs; }
	//friend Vector2<T> operator/(T const &lhs, Vector2<T> rhs) { rhs.x = lhs / rhs.x; rhs.y = lhs + rhs.y; return rhs; }

	//template<typename T2> friend Vector2<T> operator+(T2 const &lhs, Vector2<T> rhs) { rhs.x = lhs + rhs.x; rhs.y = lhs + rhs.y; return rhs; }
	//template<typename T2> friend Vector2<T> operator-(T2 const &lhs, Vector2<T> rhs) { rhs.x = lhs - rhs.x; rhs.y = lhs + rhs.y; return rhs; }
	//template<typename T2> friend Vector2<T> operator*(T2 const &lhs, Vector2<T> rhs) { rhs.x = lhs * rhs.x; rhs.y = lhs + rhs.y; return rhs; }
	//template<typename T2> friend Vector2<T> operator/(T2 const &lhs, Vector2<T> rhs) { rhs.x = lhs / rhs.x; rhs.y = lhs + rhs.y; return rhs; }

	Vector2<T> operator+=(Vector2<T> const &rhs) const { *this = *this + rhs; return *this; }
	Vector2<T> operator-=(Vector2<T> const &rhs) const { *this = *this - rhs; return *this; }
	Vector2<T> operator*=(Vector2<T> const &rhs) const { *this = *this * rhs; return *this; }
	Vector2<T> operator/=(Vector2<T> const &rhs) const { *this = *this / rhs; return *this; }
																					  														  
	//template<typename T2> Vector2<T> operator+=(Vector2<T2> const &rhs) const { *this = *this + rhs; return *this; }
	//template<typename T2> Vector2<T> operator-=(Vector2<T2> const &rhs) const { *this = *this - rhs; return *this; }
	//template<typename T2> Vector2<T> operator*=(Vector2<T2> const &rhs) const { *this = *this * rhs; return *this; }
	//template<typename T2> Vector2<T> operator/=(Vector2<T2> const &rhs) const { *this = *this / rhs; return *this; }

	Vector2<T> operator+=(T const &rhs) const { *this = *this + rhs; return *this; }
	Vector2<T> operator-=(T const &rhs) const { *this = *this - rhs; return *this; }
	Vector2<T> operator*=(T const &rhs) const { *this = *this * rhs; return *this; }
	Vector2<T> operator/=(T const &rhs) const { *this = *this / rhs; return *this; }

	//template<typename T2> Vector2<T> operator+=(T2 const &rhs) const { *this = *this + rhs; return *this; }
	//template<typename T2> Vector2<T> operator-=(T2 const &rhs) const { *this = *this - rhs; return *this; }
	//template<typename T2> Vector2<T> operator*=(T2 const &rhs) const { *this = *this * rhs; return *this; }
	//template<typename T2> Vector2<T> operator/=(T2 const &rhs) const { *this = *this / rhs; return *this; }

	//Vector2<T> operator=(Vector2<T> const &rhs) { x = rhs.x; y = rhs.y; return *this; }
	template<typename T2> Vector2<T> operator=(Vector2<T2> const &rhs) { x = rhs.x; y = rhs.y; return *this; }
	bool operator==(Vector2<T> const &rhs) const { return x == rhs.x && y == rhs.y; }
  bool operator!=(Vector2<T> const &rhs) const { return !(rhs == *this); }

	//template<typename T2> bool operator==(Vector2<T2> const &rhs) const { return x == rhs.x && y == rhs.y; }

	template <typename T2> operator T2() const { return T2(x, y); }

	template <typename T2> explicit operator Vector2<T2>() const { return Vector2<T2>(T2(x), T2(y)); }

	static Vector2<T> Zero() { return{ 0, 0 }; }
};

typedef Vector2<float> Vec2;
typedef Vector2<int> Vec2i;

#endif