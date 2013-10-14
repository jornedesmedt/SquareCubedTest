#pragma once

#include <cmath>

/// Vector2 ///

template<class T>
struct Vector2 final {
	T X;
	T Y;

	Vector2() : X(0), Y(0) {}
	Vector2(T x, T y) : X(x), Y(y) {}

};

// Common variations of Vector2
typedef Vector2<unsigned int> Vector2ui;
typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;


/// Vector3 ///

template<class T>
struct Vector3 final {
	T X;
	T Y;
	T Z;

	Vector3() : X(0), Y(0), Z(0) {}
	Vector3(T x, T y, T z) : X(x), Y(y), Z(z) {}
};

// Common variations of Vector3
typedef Vector3<unsigned int> Vector3ui;
typedef Vector3<int> Vector3i;
typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;


/// Rect ///

template<class T>
struct Rect final {
	T X;
	T Y;
	T W;
	T H;

	Rect() : X(0), Y(0), W(0), H(0) {}
	Rect(T x, T y, T w, T h) : X(x), Y(y), W(w), H(h) {}
};

// Common variations of Rect
typedef Rect<double> Rectd;


/// Angle ///

template<class T>
struct Angle final {
	T Radians;

	T GetDegrees() {
		return (T) (180.0f / M_PI * Radians);
	}

	T GetSin() {
		return sin(Radians);
	}

	T GetCos() {
		return cos(Radians);
	}

	Angle() :
		Radians(0)
	{}
	Angle(T r) :
		Radians(r)
	{}

	Angle<T>& operator=(T r) {
		return Angle<T>(r);
	}
};

// Common variations of Angle
typedef Angle<float> Anglef;