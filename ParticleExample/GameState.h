#pragma once

#include "Factory.h"

class GameState
{
	Factory factory;

public:
	unsigned puff_sprite;

	void update(float dt)
	{
		factory.spawnStaticImage(puff_sprite,
		   rand() % 800, rand() % 600, rand() % 40 + 40, rand() % 40 + 40, 3.f);

		for (auto e = factory.begin(); e != factory.end();)
		{
			// Rendering System
			if (e->sprt)
			{
				e->sprt->draw(*e->tran);
			}
			
			// Lifetime management System
			if (e->life)
			{
				if (!(e->life->isAlive()))
				{
					factory.destroy(e);
					continue;
				}
				e->life->age(dt);
			}

			// Rigidbody Physics System
			if (e->rdby && e->tran)
			{
				e->rdby->integrate(*e->tran,dt);
			}

			// controller system
			if (e->ctrl  && e->rdby && e->tran)
			{
				e->ctrl->poll(*e->tran, *e->rdby);
			}

			// particle system
			if (e->part && e->life && e->tran && e->sprt)
			{
				e->part->update(*e->life,*e->tran, *e->sprt);
			}

			++e;
		}
	}
};