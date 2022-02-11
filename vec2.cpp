
#include"vec2.h"
#include <math.h>>

vec2::vec2()
{
	x = 0;
	y = 0;
}
vec2::vec2(const float fx, const float fy)
{
	x = fx;
	y = fy;
}

float vec2::magnitude()
{
	return sqrt(this->x * this->x + this->y * this->y);
}


vec2 vec2::normalised()
{
	return vec2(*this) / this->magnitude();
}
vec2& vec2::operator*(const float& fRHS)
{
	return vec2(*this) *= fRHS;
}

float vec2::operator*(const vec2& fRHS)
{
	return this->x * fRHS.x + this->y * fRHS.y;
}

vec2& vec2::operator+(const vec2& mRHS)
{
	return vec2(*this) += mRHS;
}
vec2& vec2::operator-(const vec2& mRHS)
{
	return vec2(*this) -= mRHS;
}
vec2& vec2::operator/(const float& fRHS)
{
	return vec2(*this) /= fRHS;
}


vec2 vec2::normalise()
{
	this->x = this->x / this->magnitude();
	this->y = this->y / this->magnitude();
	return *this;
}
vec2& vec2::operator+=(const vec2& mRHS)
{
	this->x += mRHS.x;
	this->y += mRHS.y;

	return *this;
}
vec2& vec2::operator-=(const vec2& mRHS)
{
	this->x -= mRHS.x;
	this->y -= mRHS.y;

	return *this;
}
vec2& vec2::operator/=(const float& fRHS)
{
	this->x /= fRHS;
	this->y /= fRHS;

	return *this;
}
vec2& vec2::operator*=(const float& fRHS)
{
	this->x *= fRHS;
	this->y *= fRHS;

	return *this;
}


float Dot(const vec2 v1, const vec2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}