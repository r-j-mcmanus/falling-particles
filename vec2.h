#pragma once

class vec2 {
public:
	float x;
	float y;

	vec2(const float fx, const float fy);
	vec2();

	vec2& operator*=(const float& fRHS);
	vec2& operator*(const float& fScale);

	vec2& operator/=(const float& fRHS);
	vec2& operator/(const float& fScale);

	vec2& operator+=(const vec2& fRHS);
	vec2& operator+(const vec2& fRHS);

	vec2& operator-=(const vec2& fRHS);
	vec2& operator-(const vec2& fRHS);

	float operator*(const vec2& fRHS);
};

float Dot(const vec2 v1, const vec2 v2);