#pragma once
#include "components.h"
#include "ObjectPool.h"

// templated alias, or templated typedef
//template<typename T>
//using ObjectPool = ObjectPool<T>::iterator;


struct Entity
{
	class Factory *factory;
	ObjectPool<transform>::iterator  tran;
	ObjectPool<rigidbody>::iterator  rdby;
	ObjectPool<controller>::iterator ctrl;
	ObjectPool<sprite>::iterator     sprt;
	ObjectPool<lifetime>::iterator   life;
	ObjectPool<particle>::iterator   part;

	void onFree()
	{
		if (tran) tran.free();
		if (rdby) rdby.free();
		if (ctrl) ctrl.free();
		if (sprt) sprt.free();
		if (life) life.free();
		if (part) part.free();
	}
};

class Factory
{
	ObjectPool<transform>  transforms;
	ObjectPool<rigidbody>  rigidbodies;
	ObjectPool<controller> controllers;
	ObjectPool<sprite>     sprites;
	ObjectPool<lifetime>   lifetimes;
	ObjectPool<particle>   particles;
	ObjectPool<Entity>     entities;
public:

	Factory() : entities(512), transforms(512), rigidbodies(512), controllers(512),
		        sprites(512), lifetimes(512), particles(512)
	{ }

	ObjectPool<Entity>::iterator begin() { return entities.begin(); }
	ObjectPool<Entity>::iterator end() { return entities.end(); }


	ObjectPool<Entity>::iterator destroy(ObjectPool<Entity>::iterator &eit) { eit->onFree(); return eit.free(); }

	// transform, sprite, O:lifetime
	ObjectPool<Entity>::iterator spawnStaticImage(unsigned sprite_id, float x, float y,
															 float w, float h, float time = -1)
	{
		ObjectPool<Entity>::iterator retval = entities.push();
		if (!retval) return retval;

		retval->factory = this;

		retval->tran = transforms.push();
		retval->sprt = sprites.push();

		retval->tran->position  = vec2{ x, y };
		retval->tran->scale     = vec2{ w, h };		
		retval->sprt->sprite_id = sprite_id;

		if (time > 0)
		{
			retval->life = lifetimes.push();
			retval->life->lifespan = time;
		}

		return retval;
	}
};