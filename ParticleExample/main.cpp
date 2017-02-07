#include "sfwdraw.h"
#include "maths.h"
#include <iostream>
#include "particle.h"

void main()
{ 
	sfw::initContext();

	unsigned sprite = 
	sfw::loadTextureMap("../res/particle_sprite.png");

	particle part;

	part.sprite = sprite;
	part.pos    = vec2{400, 300};
	part.vel    = randDir(0, 360) * lerp(20, 80, rand01());
	part.sDim   = randRange(vec2{   8,  8 }, vec2{ 64, 64});
	part.eDim   = lerp(vec2{ 256,256 }, vec2{512,512}, rand01());
	
	part.sColor.ui_color = WHITE;
	part.sColor.ui_color = WHITE;
	part.lifespan = 4.5f;
	part.lifetime = 0;

	while (sfw::stepContext())
	{
		float dt = sfw::getDeltaTime();

		if (!part.refesh(dt))
		{
			part.pos  = vec2{ 400, 300 };
			part.vel  = randDir(0, 360) * lerp(20, 80, rand01());
			part.sDim = randRange(vec2{ 8,  8 }, vec2{ 32, 32 });
			part.eDim = lerp(vec2{ 256,256 }, vec2{ 512,512 }, rand01());
			part.lifetime = 0;
		}
	}

	sfw::termContext();
}