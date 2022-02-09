#pragma once

#include"vec2.h"
#include "glm/glm.hpp"

class Particle
{
public:
	vec2 position = vec2(0,0);
	vec2 newPosition = vec2(0, 0);
	vec2 velocity = vec2(0, 0);
	vec2 force = vec2(0, 0);
	vec2 impulse = vec2(0, 0);
	vec2 acceleration = vec2(0, 0);
	vec2 gravity = vec2(0, 0);

	float fInvMass = 1.0f;
	float fRadius = 1.0f;
	float fRestitution = 0.1f;
	float fDamping = 0.0f; //0.0001f;

	bool collision = true;

	//float dtFracEuler = 1.0f;

	void setMass(const float mass) { fInvMass = 1 / mass; };
	void integrate(float dt);

	glm::mat4 getTranslationMatrix();

	Particle(const float pos_x, const float pos_y);
	Particle(const vec2 pos);
	Particle();
};