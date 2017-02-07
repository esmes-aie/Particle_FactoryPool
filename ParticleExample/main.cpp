#include "sfwdraw.h"
#include "maths.h"
#include <iostream>
#include "ParticleEmitter.h"

void main()
{ 
	sfw::initContext();

	unsigned sprite = 
	sfw::loadTextureMap("../res/particle_sprite.png");

	ParticleEmitter pe;

	pe.emitRateLo = 0.1f;
	pe.emitRateHi = 0.3f;

	pe.sprite = sprite;

	pe.pos = vec2{400, 300};
	pe.angLo = 0;
	pe.angHi = 360;
	pe.spdLo = 30;
	pe.spdHi = 80;
	pe.dimLoStart = vec2{ 8,8};
	pe.dimHiStart = vec2{32,32};
	pe.dimLoEnd   = vec2{256,256};
	pe.dimHiEnd   = vec2{512,512};

	pe.colLoStart.ui_color = GREEN;
	pe.colHiStart.ui_color = BLUE;
	pe.colLoEnd.ui_color   = YELLOW;
	pe.colHiEnd.ui_color   = RED;

	pe.lifespanLo = .3f;
	pe.lifespanHi = .5f;

	while (sfw::stepContext())
	{
		float dt = sfw::getDeltaTime();

		pe.update(dt);
	}

	sfw::termContext();
}