#include "Math.h"

vec2 math::normalized(const vec2 & v)
{
	return v / length(v);
}

vec2 math::rotate(const vec2 & v, float angle)
{
	vec2 result;
	result.x = v.x * cosf(angle) - v.y * sinf(angle);
	result.y = v.x * sinf(angle) + v.y * cosf(angle);
	return result;
}

vec2 math::ceil(const vec2 & v)
{
	return vec2(std::ceil(v.x), std::ceil(v.y));
}

float math::dot(const vec2 & a, const vec2 & b)
{
	return a.x * b.x + a.y * b.y;
}

float math::length(const vec2 & v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

float math::clamp(float value, float min, float max)
{
	if (value < min) {
		return min;
	}
	else if (value > max) {
		return max;
	}
	else {
		return value;
	}
}

float math::toRadians(float degrees)
{
	return degrees * MATH_PI / 180.0f;
}

float math::toDegrees(float radians)
{
	return radians * 180.0f / MATH_PI;
}

float math::interpolate(const std::vector<std::pair<float, float>>& curve, float x)
{
	if (x > curve.back().first) {
		return curve.back().second;
	}
	if (x < curve[0].first) {
		return curve[0].second;
	}

	std::vector<std::pair<float, float>>::const_iterator left, right;

	left = std::lower_bound(curve.begin(), curve.end(), std::make_pair(x, -INFINITY));

	if (left == curve.begin()) {
		return left->second;
	}

	right = left;
	--right;
	return right->second + (left->second - right->second) * (x - right->first) / (left->first - right->first);
}

vec3 math::lerp(const vec3 & a, const vec3 & b, float t)
{
	return a * (1 - t) + b * t;
}

sf::Color math::lerp(const sf::Color & a, const sf::Color & b, float t)
{
	return sf::Color(
		static_cast<sf::Uint8>(a.r * (1 - t) + b.r * t),
		static_cast<sf::Uint8>(a.g * (1 - t) + b.g * t),
		static_cast<sf::Uint8>(a.b * (1 - t) + b.b * t),
		static_cast<sf::Uint8>(a.a * (1 - t) + b.a * t));
}

float math::scalarProjection(const vec2 & a, const vec2 & b)
{
	float len = length(a);
	if (len == 0.0f) {
		return 0.0f;
	}
	else {
		return dot(a, b) / len;
	}
}

vec2 math::vectorProjection(const vec2 & a, const vec2 & b)
{
	float len = length(a);
	if (len == 0.0f) {
		return vec2();
	}
	else {
		return dot(a, b) * a / (len * len);
	}
}


float CCW(const vec2& a, const vec2& b, const vec2& c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool middle(float a, float b, float c)
{
	if (a < b) {
		return a <= c && c <= b;
	}
	else {
		return b <= c && c <= a;
	}
}

bool math::intersect(const vec2 & a1, const vec2 & a2, const vec2 & b1, const vec2 & b2)
{
	if ((CCW(a1, a2, b1) * CCW(a1, a2, b2) < 0) &&
		(CCW(b1, b2, a1) * CCW(b1, b2, a2) < 0))
	{
		return true;
	}

	return 
		(CCW(a1, a2, b1) == 0 && middle(a1.x, a2.x, b1.x) && middle(a1.y, a2.y, b1.y)) ||
		(CCW(a1, a2, b2) == 0 && middle(a1.x, a2.x, b2.x) && middle(a1.y, a2.y, b2.y)) ||
		(CCW(b1, b2, a1) == 0 && middle(b1.x, b2.x, a1.x) && middle(b1.y, b2.y, a1.y)) ||
		(CCW(b1, b2, a2) == 0 && middle(b1.x, b2.x, a2.x) && middle(b1.y, b2.y, a2.y));
}
