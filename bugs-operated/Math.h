#pragma once

#include <vector>
#include <cmath>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>

#include "Constants.h"

using vec2 = sf::Vector2f;
using ivec2 = sf::Vector2i;
using uvec2 = sf::Vector2u;

using vec3 = sf::Vector3f;
using ivec3 = sf::Vector3i;

using rect = sf::FloatRect;
using recti = sf::IntRect;

namespace math
{
	vec2 normalized(const vec2& v);

	vec2 rotate(const vec2& v, float angle);

	vec2 ceil(const vec2& v);

	float dot(const vec2& a, const vec2& b);

	float length(const vec2& v);

	float clamp(float value, float min, float max);

	float toRadians(float degrees);

	float toDegrees(float radians);

	float interpolate(const std::vector<std::pair<float, float>>& curve, float x);

	vec3 lerp(const vec3& a, const vec3& b, float t);

	sf::Color lerp(const sf::Color& a, const sf::Color& b, float t);

	template <typename T>
	int sign(T val)
	{
		return (T(0) < val) - (val < T(0));
	}

	// scalar projection b onto a
	float scalarProjection(const vec2& a, const vec2& b);

	// vector projection b onto a
	vec2 vectorProjection(const vec2& a, const vec2& b);

	// Checks intersection between two lines
	bool intersect(const vec2& a1, const vec2& a2, const vec2& b1, const vec2& b2);
}