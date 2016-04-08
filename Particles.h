/*#ifndef PARTICLES_H
#define PARTICLES_H

#include <vector>

#include "SpriteManager.h"
#include "Object.h"

struct Particle : Object
{
	float thetaX;
	float thetaY;
}

typedef std::vector<Particle> ParticleList;

extern ParticleList AllTheParticles;

void CreateExplosion();

#endif PARTICLES_H*/