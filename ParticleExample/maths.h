#pragma once
////////////////////////////////////

struct vec2 { float x, y; };

inline vec2 operator+(const vec2 &A, const vec2 &B)
						{ return vec2{A.x+B.x, A.y+B.y}; }

inline vec2 operator*(const vec2 &A, float b)
						{ return vec2{A.x*b, A.y*b}; }

inline vec2 lerp(const vec2 &S, const vec2 &E, float t)
						{ return S*(t - 1) + E*t; }

///////////////////////////////////

union color
{
	unsigned ui_color;
	struct { char r, g, b, a; };
};

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