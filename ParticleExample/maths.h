#pragma once
#include <random>
#include <cmath>

inline float rand01() { return (float)rand() / RAND_MAX; }

inline float lerp(float s, float e, float t) { return s*(t - 1) + e*t; }

#define DEG2RAD 0.0174533

////////////////////////////////////

struct vec2 { float x, y; };

inline vec2 operator+(const vec2 &A, const vec2 &B)
						{ return vec2{A.x+B.x, A.y+B.y}; }

inline vec2 operator*(const vec2 &A, float b)
						{ return vec2{A.x*b, A.y*b}; }

inline vec2 lerp(const vec2 &S, const vec2 &E, float t)
						{ return S*(t - 1) + E*t; }

inline vec2 randRange(const vec2 &A, const vec2 &B)
{
	return vec2{ lerp(A.x,B.x,rand01()), lerp(A.y,B.y,rand01()) };
}

// assuming degrees between 0-360
inline vec2 randDir(float min_deg, float max_deg)
{
	float deg = lerp(min_deg, max_deg, rand01());
	float rad = DEG2RAD * deg;

	return vec2{cos(rad), sin(rad)};
}

///////////////////////////////////

union color
{
	unsigned ui_color;
	struct { unsigned char a, r, b, g; };
};
// 0x00 00 00 00

inline color lerp(const color &S, const color &E, float t)
{
	color ret;
	ret.r = S.r*(t - 1) + E.r*t;
	ret.g = S.g*(t - 1) + E.g*t;
	ret.b = S.b*(t - 1) + E.b*t;
	ret.a = S.a*(t - 1) + E.a*t;
	return ret;
}

///////////////////////////////////