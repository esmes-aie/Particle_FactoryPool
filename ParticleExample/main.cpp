#include "sfwdraw.h"



void main()
{
	sfw::initContext();


	while (sfw::stepContext());

	sfw::termContext();

}