#include"particle.h"

#include <assert.h>

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp> //glm::translate

Particle::Particle(const float pos_x, const float pos_y)
{
	position.x = pos_x;
	position.y = pos_y;
};

Particle::Particle(const vec2 pos)
{
	position.x = pos.x;
	position.y = pos.y;
};

Particle::Particle()
{
};

void Particle::integrate(float dt)
{
	assert(dt > 0.0);

	position.x = position.x + velocity.x * dt;
	position.y = position.y + velocity.y * dt;

	velocity.x = velocity.x + acceleration.x * dt - velocity.x * fDamping;
	velocity.y = velocity.y + acceleration.y * dt - velocity.y * fDamping;
}

glm::mat4 Particle::getTranslationMatrix()
{
	const glm::vec3 translationVector = glm::vec3(position.x, position.y, 0);
	return glm::translate(glm::mat4(1.0f), translationVector);
}