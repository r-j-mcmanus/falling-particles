#pragma once

#include "particle.h"
#include "vec2.h"


//Game physics engine development

namespace phys {
	void computeForces(Particle& partical, float dt);
	void applyForces(Particle& partical, float dt);
	void updatePositions(Particle& partical, float dt);
	void detectCollisions(Particle& partical);
	void solveConstraints();

}

void phys::applyForces(Particle& partical, float dt)
{
	partical.force.y = -10.0f;
	partical.velocity += partical.force * partical.fInvMass * dt;

}

void phys::updatePositions(Particle& partical, float dt)
{
	partical.newPosition += partical.velocity * dt;
}

/// <summary>
/// we find where collisions occure, ensure they are not and then accumulate reaction forces
/// </summary>
/// <param name="partical"></param>
void phys::detectCollisions(Particle& partical)
{
	partical.collision = false; 

	if (partical.newPosition.y < 0)
	{
		partical.collision = true; 
		const float deltat = partical.position.y / partical.velocity.y;
		partical.position.x -= partical.velocity.x * deltat;
		partical.position.y = 0;
	}
}

void phys::solveConstraints() {};