
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
	template <typename T2> Vector2(Vector2<T2> const &other) : Vector2<T>(other.x, other.y) {};

	T X() const { return x; }
	T Y() const { return y; }
	Vector2<T> const XY() { return{ x, y }; }
	Vector2<T> const YX() { return{ y, x }; }

	void X(T _x) { x = _x };
	void Y(T _y) { y = _y };
	void XY(Vector2<T> _xy) { x = _xy.x; y = _xy.y; };
	void YX(Vector2<T> _yx) { x = _xy.y; y = _xy.x; };

	float Length() const { return sqrt((float)LengthSquared()); }
	float LengthSquared() const { return Dot(*this); }
	Vector2<float> Normalise() const { return Vector2<float>(*this) / Length(); }
	template <typename T2> float Dot(Vector2<T2> other) const { return float(x * other.x + y * other.y); }

	T const &operator[](size_t index) const { return components[index]; }
	T &operator[](size_t index) { return components[index]; }

	friend Vector2<T> operator+(Vector2<T> lhs, Vector2<T> const &rhs) { lhs.x += rhs.x; lhs.y += rhs.y; return lhs; }
	friend Vector2<T> operator-(Vector2<T> lhs, Vector2<T> const &rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; return lhs; }
	friend Vector2<T> operator*(Vector2<T> lhs, Vector2<T> const &rhs) { lhs.x *= rhs.x; lhs.y *= rhs.y; return lhs; }
	friend Vector2<T> operator/(Vector2<T> lhs, Vector2<T> const &rhs) { lhs.x /= rhs.x; lhs.y /= rhs.y; return lhs; }

	friend Vector2<T> operator+(Vector2<T> lhs, T const &rhs) { lhs.x += rhs; lhs.y += rhs; return lhs; }
	friend Vector2<T> operator-(Vector2<T> lhs, T const &rhs) { lhs.x -= rhs; lhs.y -= rhs; return lhs; }
	friend Vector2<T> operator*(Vector2<T> lhs, T const &rhs) { lhs.x *= rhs; lhs.y *= rhs; return lhs; }
	friend Vector2<T> operator/(Vector2<T> lhs, T const &rhs) { lhs.x /= rhs; lhs.y /= rhs; return lhs; }

	Vector2<T> operator+=(T const &rhs) const { *this = *this + rhs; return *this; }
	Vector2<T> operator-=(T const &rhs) const { *this = *this - rhs; return *this; }
	Vector2<T> operator*=(T const &rhs) const { *this = *this * rhs; return *this; }
	Vector2<T> operator/=(T const &rhs) const { *this = *this / rhs; return *this; }

	Vector2<T> operator=(Vector2<T> const &rhs) { x = rhs.x; y = rhs.y; return *this; }
	template <typename T2> bool operator==(Vector2<T2> const &rhs) const { return x == rhs.x && y == rhs.y; }

	template <typename T2> operator Vector2<T2>() const { return Vector2<T2>(x, y); }

	static Vector2<T> Zero() { return{ 0, 0 }; }
};


template<typename T>
struct Vector3
{
	union
	{
		struct { T x, y, z; };
		T components[3];
	};

	Vector3() {};
	Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {};
	template <typename T2> Vector3(Vector3<T2> const &other) : Vector3<T>(other.x, other.y, other.z) {};
	template <typename T2> Vector3(Vector2<T2> const &other, T _z) : Vector3<T>(other.x, other.y, _z) {};
	template <typename T2> Vector3(T _x, Vector2<T2> const &other) : Vector3<T>(_x, other.x, other.y) {};

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
	void XY(Vector2<T> _xy) { x = _xy.x; y = _xy.y; };
	void YX(Vector2<T> _yx) { y = _xy.x; x = _xy.y; };
	void XZ(Vector2<T> _xz) { x = _xy.x; z = _xy.y; };
	void ZX(Vector2<T> _zx) { z = _xy.x; x = _xy.y; };
	void YZ(Vector2<T> _yz) { y = _xy.x; z = _xy.y; };
	void ZY(Vector2<T> _zy) { z = _xy.x; y = _xy.y; };
	void XYZ(Vector3<T> _xyz) { x = _xyz.x; y = _xyz.y; z = _xyz.z; }
	void XZY(Vector3<T> _xzy) { x = _xyz.x; z = _xyz.y; y = _xyz.z; }
	void YZX(Vector3<T> _yzx) { y = _xyz.x; z = _xyz.y; x = _xyz.z; }
	void YXZ(Vector3<T> _yxz) { y = _xyz.x; x = _xyz.y; z = _xyz.z; }
	void ZXY(Vector3<T> _zxy) { z = _xyz.x; x = _xyz.y; y = _xyz.z; }
	void ZYX(Vector3<T> _zyx) { z = _xyz.x; y = _xyz.y; z = _xyz.z; }

	float Length() const { return sqrt((float)LengthSquared()); }
	float LengthSquared() const { return Dot(*this); }
	Vector3<float> Normalise() const { return Vector3<float>(*this) / Length(); }
	template <typename T2> float Dot(Vector3<T2> other) const { return float(x * other.x + y * other.y + z * other.z); }

	T const &operator[](size_t index) const { return components[index]; }
	T &operator[](size_t index) { return components[index]; }

	friend Vector3<T> operator+(Vector3<T> lhs, Vector3<T> const &rhs) { lhs.x += rhs.x; lhs.y += rhs.y; lhs.z += rhs.z; return lhs; }
	friend Vector3<T> operator-(Vector3<T> lhs, Vector3<T> const &rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; lhs.z -= rhs.z; return lhs; }
	friend Vector3<T> operator*(Vector3<T> lhs, Vector3<T> const &rhs) { lhs.x *= rhs.x; lhs.y *= rhs.y; lhs.z *= rhs.z; return lhs; }
	friend Vector3<T> operator/(Vector3<T> lhs, Vector3<T> const &rhs) { lhs.x /= rhs.x; lhs.y /= rhs.y; lhs.z /= rhs.z; return lhs; }

	friend Vector3<T> operator+(Vector3<T> lhs, T const &rhs) { lhs.x += rhs; lhs.y += rhs; lhs.z += rhs; return lhs;}
	friend Vector3<T> operator-(Vector3<T> lhs, T const &rhs) { lhs.x -= rhs; lhs.y -= rhs; lhs.z -= rhs; return lhs; }
	friend Vector3<T> operator*(Vector3<T> lhs, T const &rhs) { lhs.x *= rhs; lhs.y *= rhs; lhs.z *= rhs; return lhs; }
	friend Vector3<T> operator/(Vector3<T> lhs, T const &rhs) { lhs.x /= rhs; lhs.y /= rhs; lhs.z /= rhs; return lhs; }

	Vector3<T> operator+=(T const &rhs) { *this = *this + rhs; return *this; }
	Vector3<T> operator-=(T const &rhs) { *this = *this - rhs; return *this; }
	Vector3<T> operator*=(T const &rhs) { *this = *this * rhs; return *this; }
	Vector3<T> operator/=(T const &rhs) { *this = *this / rhs; return *this; }

	Vector3<T> operator=(Vector3<T> const &rhs) { x = rhs.x; y = rhs.y; z = rhs.z; return *this; }
	template <typename T2> bool operator==(Vector3<T2> const &rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }

	template <typename T2> operator Vector3<T2>() const { return Vector3<T2>(x, y, z); }

	static Vector3<T> Zero() { return{ 0, 0, 0 }; }
};

typedef Vector2<float> Vec2;
typedef Vector2<int> Vec2i;

typedef Vector3<float> Vec3;
typedef Vector3<int> Vec3i;