#pragma once

#include "particle.h"
#include "vec2.h"

class ParticleContact
{
public:
	Particle* particles[2];

	float restitution = 1.0f;

	vec2 contactNormal = vec2(0,1);
	void resolve(float duration);


protected:
	float calculateSperatingSpeed() const;

private:
	void resolveVelocity(float duration);
	void resolveInterpenetration(float duration);
	float penetration;

};
