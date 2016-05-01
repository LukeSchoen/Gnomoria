#ifndef VECTOR_H
#define VECTOR_H

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

//Dot Product

template <typename T1, typename T2, size_t D>
inline auto Dot(T1 const &a, T2 const& b)
{
	auto total = a[0] * b[0];
	for (size_t c = 1; c < D; c++)
		total += a[c] * b[c];
	return total;
}

template <typename T1, typename T2>
auto Dot2(T1 const &a, T2 const &b) { return Dot<2>(a, b); }

template <typename T1, typename T2>
auto Dot3(T1 const &a, T2 const &b) { return Dot<3>(a, b); }

template <typename T1, typename T2>
auto Dot4(T1 const &a, T2 const &b) { return Dot<4>(a, b); }

template <typename T1, typename T2>
auto Dot(Vector2<T1> const &a, Vector2<T2> const& b)
{
	return Dot2(a, b);
}

template <typename T1, typename T2>
auto Dot(Vector3<T1> const &a, Vector3<T2> const& b)
{
	return Dot3(a, b);
}

template <typename T1, typename T2>
auto Dot(Vector4<T1> const &a, Vector4<T2> const& b)
{
	return Dot4(a, b);
}


#endif

