#include "sfwdraw.h"



void main()
{ 
	sfw::initContext();


	unsigned sprite = 
	sfw::loadTextureMap("../res/particle_sprite.png");

	while (sfw::stepContext())
	{
		sfw::drawTexture(sprite, 400, 300, 100, 100, 0, true,0, MAGENTA);
	}

	sfw::termContext();
}