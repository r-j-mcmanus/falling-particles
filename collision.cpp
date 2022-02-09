
//https://www.toptal.com/game/video-game-physics-part-i-an-introduction-to-rigid-body-dynamics

#include<vector>

#include"vec2.h"
#include"particle.h"

void EulerTimeStep(Particle& particle, const float dt)
{
	//reset Forces
	float accel_x = particle.force.x * particle.fInvMass;
	float accel_y = particle.force.y * particle.fInvMass;

	particle.velocity.x = accel_x * dt;
	particle.velocity.y = accel_y * dt;

	particle.position.x = particle.velocity.x * dt;
	particle.position.y = particle.velocity.y * dt;
	
}

void CheckGroundCollisions(Particle& particle, const float dt)
{
	vec2 normal(0,1);
	vec2 normalForce(0,0);
	particle.collision = false;

	const float groundPos = 0.0;
	if (particle.position.y <= particle.fRadius + groundPos)
	{

		float normalSpeed = Dot(normal, particle.velocity);
		if (normalSpeed < 0) {
			float dt1 = (particle.position.y - groundPos) / particle.velocity.y;
			//float dt2 = dt - dt1;
			//dtFracEuler = dt2 / dt 
			//if we were to do a more acuret simulation we would not use the whole dt in the reaction force.

			particle.force += normal * normalSpeed * (particle.fRestitution + 1.0f) / particle.fInvMass / dt;
			particle.collision = true;

			//the force applied is from the ground so we move the particle to be on the gorund
			particle.position.y = particle.fRadius + groundPos;
			particle.position.x = particle.velocity.x * dt1;
		}
	}
}

void ComputeForces(Particle& particle, const float dt)
{
	//reset Forces
	particle.force = vec2(0, 0);

	CheckGroundCollisions(particle, dt);

	if (!particle.collision)
	{
		particle.force.y += 9.81f / particle.fInvMass;
	}
}