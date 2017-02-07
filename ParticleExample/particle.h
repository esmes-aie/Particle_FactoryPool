#pragma once

#include "sfwdraw.h"
#include "maths.h"

struct particle
{
	unsigned sprite;
	vec2 pos, vel;
	vec2 sDim, eDim;
	color sColor, eColor;

	float lifetime, lifespan;

	particle() : lifespan(-1), lifetime(0) {}

	bool refresh(float dt)
	{
		lifetime += dt;

		float alpha = lifetime / lifespan;

		vec2  dim   = lerp(sDim,   eDim,   alpha);
		color color = lerp(sColor, eColor, alpha);

		pos = pos + vel * dt;

		sfw::drawTexture(sprite, pos.x, pos.y, dim.x, dim.y, 0, true, 0, color.ui_color);

		return alpha < 1;
	}

	bool isActive() const { return lifetime < lifespan; }
};