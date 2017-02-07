#include "sfwdraw.h"
#include "maths.h"
#include <iostream>

void main()
{ 
	sfw::initContext();


	unsigned sprite = 
	sfw::loadTextureMap("../res/particle_sprite.png");


	color startColor, endColor;

	startColor.ui_color = GREEN;
	endColor.ui_color = RED;
	float timer = 0;

	while (sfw::stepContext())
	{
		timer += sfw::getDeltaTime();

		color currentColor = lerp(startColor, endColor, timer/10.f);

		sfw::drawTexture(sprite, 400, 300, 100, 100, 0, true, 0, currentColor.ui_color);
	}

	sfw::termContext();
}