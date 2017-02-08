#pragma once

#include "maths.h"
#include "sfwdraw.h"
struct transform
{
	vec2 position, scale;
	float angle = 0;
};

struct rigidbody
{
	vec2 velocity, acceleration;
	void integrate(transform &T, float dt)
	{
		velocity   = velocity + acceleration * dt;
		T.position = T.position + velocity * dt;
	}
};

struct lifetime
{
	float time = 0, lifespan;

	void age(float dt) { time += dt; }
	bool isAlive() const { time < lifespan; }
	float pctAlive() const { return time / lifespan; }
};

struct sprite
{
	size_t sprite_id;
	color tint = { WHITE };

	void draw(const transform &T)
	{
	sfw::drawTexture(sprite_id, T.position.x, T.position.y, 
								T.scale.x,    T.scale.y, T.angle, true, 0, tint.ui_color);
	}
};