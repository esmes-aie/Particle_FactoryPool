#pragma once

#include "particle.h"

#define PART_SIZE 24

// Factory
class ParticleEmitter
{
	// Data Structure to store all of our particles
	particle particles[PART_SIZE];

	void emit()
	{
		for(int i = 0; i < PART_SIZE; ++i) // linear time every time we add a particle
			if (!particles[i].isActive())
			{
				particles[i] = _generate();
				return;
			}
	}

	particle _generate()
	{
		particle part;
		part.pos = pos;
		part.sprite = sprite;

		part.vel = randDir(angLo, angHi) * lerp(spdLo, spdHi, rand01());

		part.lifespan = lerp(lifespanLo, lifespanHi, rand01());

		part.sColor = lerp(colLoStart, colHiStart, rand01());
		part.eColor = lerp(colLoEnd, colHiEnd, rand01());

		part.sDim = randRange(dimLoStart, dimHiStart);
		part.eDim = randRange(dimLoEnd, dimHiEnd);

		part.lifetime = 0;
		return part;
	}

public:
	// emissions
	float emitRateLo, emitRateHi;
	float emissionTimer;

	// defaults
	vec2 pos;
	unsigned sprite;
	float angLo, angHi; // direction *
	float spdLo, spdHi; // speed = velocity
	vec2  dimLoStart, dimHiStart; // range of acceptable starting dimensions
	vec2  dimLoEnd  , dimHiEnd;	  // range of acceptable ending dimensions
	color colLoStart, colHiStart; // ....
	color colLoEnd  , colHiEnd;
	float lifespanLo, lifespanHi;


	void update(float dt)
	{
		for (int i = 0; i < PART_SIZE; ++i)
			if(particles[i].isActive())
				particles[i].refresh(dt);

		emissionTimer -= dt;
		if(emissionTimer < 0)
			do
			{
				emit();
			}
			while(emissionTimer += lerp(emitRateLo, emitRateHi, rand01()) < 0);
	}
};