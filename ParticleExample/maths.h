#pragma once
#include <random>
#include <cmath>

inline float rand01() { return (float)rand() / RAND_MAX; }

inline float lerp(float s, float e, float t) { return s*(1 - t) + e*t; }

#define DEG2RAD 0.0174533

////////////////////////////////////

struct vec2 { float x, y; };

inline vec2 operator+(const vec2 &A, const vec2 &B)
						{ return vec2{A.x+B.x, A.y+B.y}; }

inline vec2 operator-(const vec2 &A, const vec2 &B)
{
	return vec2{ A.x - B.x, A.y - B.y };
}

inline vec2 operator*(const vec2 &A, float b)
						{ return vec2{A.x*b, A.y*b}; }

inline vec2 normal(const vec2 &A)
{
	float D = sqrt(A.x*A.x + A.y*A.y);
	return vec2{A.x/D, A.y/D};
}

inline vec2 lerp(const vec2 &S, const vec2 &E, float t)
						{ return S*(1 - t) + E*t; }

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
	struct { unsigned char a, b, r, g; };
};
// 0x00 00 00 00

inline color lerp(const color &S, const color &E, float t)
{
	color ret;
	ret.r = S.r*(1 - t) + E.r*t;
	ret.g = S.g*(1 - t) + E.g*t;
	ret.b = S.b*(1 - t) + E.b*t;
	ret.a = S.a*(1 - t) + E.a*t;
	return ret;
}

///////////////////////////////////