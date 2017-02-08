#pragma once
#include "components.h"
#include "ObjectPool.h"

// templated alias, or templated typedef
template<typename T>
using handle = ObjectPool<T>::iterator;

struct Entity
{
	class Factory *factory;
	handle<transform>  tran;
	handle<rigidbody>  rdby;
	handle<controller> ctrl;
	handle<sprite>     sprt;
	handle<lifetime>   life;
	handle<particle>   part;

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

	handle<Entity> begin() { return entities.begin(); }
	handle<Entity> end() { return entities.end(); }


	handle<Entity> destroy(handle<Entity> &eit) { eit->onFree(); return eit.free(); }

	// transform, sprite, O:lifetime
	handle<Entity> spawnStaticImage(unsigned sprite_id, float x, float y, float w, float h, float time = -1)
	{
		handle<Entity> retval = entities.push();
		
		retval->tran = transforms.push();
		retval->sprt = sprites.push();

		retval->tran->position  = vec2{ x,y };
		retval->tran->scale     = vec2{ w,h };		
		retval->sprt->sprite_id = sprite_id;

		if (time > 0)
		{
			retval->life = lifetimes.push();
			retval->life->time = time;
		}

		return retval;
	}
};