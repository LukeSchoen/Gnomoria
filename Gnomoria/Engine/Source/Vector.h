
#define GM_VECMIDTYPE(derived, type, dimensions) Vector ## dimensions<derived, type>
#define GM_NORMALTYPE(dimensions) GM_VECMIDTYPE(Vec3, float, dimensions)
#define GM_VECBASETYPE(derived, type, dimensions) VectorBase<derived, GM_NORMALTYPE(dimensions), type, dimensions>

struct Vec2;
struct Vec3;
struct Vec4;

template<typename derivedType, typename normalType,  typename componentType, int D>
struct VectorBase
{
	VectorBase() {};

	VectorBase(componentType const *value )
	{
		memcpy(components, value, sizeof(componentType) * D)
	}

	VectorBase(derivedType const &src)
		: VectorBase(src.components)
	{
		//memcpy(components, src.components, sizeof(componentType) * D);
	}

	float Length() const { return sqrt((float)LengthSquared()); }

	componentType LengthSquared() const { return Dot(*(derivedType*)this); }

	componentType Dot(derivedType const &other) const 
	{
		componentType dotProduct = 0;
		for (int i = 0; i < D; i++)
			dotProduct += components[i] * other[i];
		return dotProduct;
	}

	normalType Normalize()
	{
		return *(derivedType*)this / Length();
	}


	static derivedType Zero()
	{
		derivedType result;
		for (int i = 0; i < D; i++)
			result[i] = 0;
		return result
	}


	componentType& operator[](int index)
	{
		return components[index];
	}

	componentType const& operator[](int index) const
	{
		return components[index];
	}

	derivedType& operator=(derivedType const& rhs)
	{
		new(this) derivedType(rhs);
		return *(derivedType*)this;
	}

	 derivedType operator+(componentType rhs)
	{
		derivedType result = *(derivedType*)this;
		for (int i = 0; i < D; i++)
			result[i] += rhs;
		return result;
	}

	 derivedType operator-(componentType rhs)
	{
		derivedType result = *(derivedType*)this;
		for (int i = 0; i < D; i++)
			result[i] -= rhs;
		return result;
	}

	 derivedType operator*(componentType rhs)
	{
		derivedType result = *(derivedType*)this;
		for (int i = 0; i < D; i++)
			result[i] *= rhs;
		return result;
	}

	derivedType operator/(componentType rhs)
	{
		derivedType result = *(derivedType*)this;
		for (int i = 0; i < D; i++)
			result[i] /= rhs;
		return result;
	}


	derivedType operator+(derivedType const& rhs)
	{
		derivedType result = *(derivedType*)this;
		for (int i = 0; i < D; i++)
			result[i] += rhs[i];
		return result;
	}

	 derivedType operator-(derivedType const& rhs)
	{
		derivedType result = *(derivedType*)this;
		for (int i = 0; i < D; i++)
			result[i] -= rhs[i];
		return result;
	}

	 derivedType operator*(derivedType const& rhs)
	{
		derivedType result = *(derivedType*)this;
		for (int i = 0; i < D; i++)
			result[i] *= rhs[i];
		return result;
	}

	 derivedType operator/(derivedType const& rhs)
	{
		derivedType result = *(derivedType*)this;
		for (int i = 0; i < D; i++)
			result[i] /= rhs[i];
		return result;
	}

protected:
	componentType components[D];
};

template <typename derivedType, typename componentType>
struct Vector2 : public GM_VECBASETYPE(derivedType, componentType, 2)
{
	Vector2() {}
	Vector2(componentType _x, componentType _y) : GM_VECBASETYPE(derivedType, componentType, 2)({ _x, _y }) {}

	componentType &x = components[0];
	componentType &y = components[1];
};

template <typename derivedType, typename componentType>
struct Vector3 : public GM_VECBASETYPE(derivedType, componentType, 3)
{
	Vector3() {}
	Vector3(componentType _x, componentType _y, componentType _z) : GM_VECBASETYPE(derivedType, componentType, 3)({ _x, _y, _z}) {}

	componentType &x = components[0];
	componentType &y = components[1];
	componentType &z = components[2];
};


template <typename derivedType, typename componentType>
struct Vector4 : public GM_VECBASETYPE(derivedType, componentType, 4)
{
	Vector4() {}
	Vector4(componentType _x, componentType _y, componentType _z, componentType _w) : GM_VECBASETYPE(derivedType, componentType, 4)({ _x, _y, _z, _w }) {}

	componentType &x = components[0];
	componentType &y = components[1];
	componentType &z = components[2];
	componentType &w = components[3];
};

struct Vec2 : public GM_VECMIDTYPE(Vec2, float, 2)
{

};

struct Vec3 : public GM_VECMIDTYPE(Vec3, float, 3)
{

};

struct Vec4 : public GM_VECMIDTYPE(Vec4, float, 4)
{
};

struct Vec2i : public GM_VECMIDTYPE(Vec2i, int, 2)
{
	
};
