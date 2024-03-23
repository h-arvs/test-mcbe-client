#pragma once
#include <type_traits>

template <typename T> requires std::is_arithmetic_v<T>
struct Vec3 {
	T x = 0;
	T y = 0;
	T z = 0;
	Vec3() = default;
	Vec3(T x, T y, T z) : x(x), y(y), z(z){}
	template <typename U> Vec3(const Vec3<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z)) {}
	Vec3<T> operator+(Vec3<T> other) {
		return Vec3<T>(x + other.x, y + other.y, z + other.z);
	}

	Vec3<T> operator-(Vec3<T> other) {
		return Vec3<T>(x - other.x, y - other.y, z - other.z);
	}
};

struct BlockPos : public Vec3<int> {
};

struct AABB {
	Vec3<float> first{ 0, 0, 0 };
	Vec3<float> second{ 0, 0, 0 };
	AABB() = default;
	AABB(Vec3<float> first, Vec3<float> second) : first(first), second(second) {}
	AABB(float f1, float f2, float f3, float s1, float s2, float s3) : first(Vec3<float>(f1, f2, f3)), second(Vec3<float>(s1, s2, s3)) {}
};

