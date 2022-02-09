#include "ParticalContact.h"

#include <iostream>

void ParticleContact::resolve(float duration)
{
	resolveVelocity(duration);
	//resolveInterpenetration(duration);
}

float ParticleContact::calculateSperatingSpeed() const
{
	vec2 relativeVelocity = particles[0]->velocity;
	//std::cout << "relativeVelocity.x " << relativeVelocity.x << std::endl;
	if (particles[1])
	{
		relativeVelocity -= particles[1]->velocity;
		//std::cout << "relativeVelocity.x " << relativeVelocity.x << std::endl;
	}

	return relativeVelocity * contactNormal;
}

void ParticleContact::resolveVelocity(float duration)
{
	//std::cout << "contactNormal.x " << contactNormal.x << std::endl;
	//std::cout << "contactNormal.y " << contactNormal.y << std::endl;

	const float seperatingSpeed = calculateSperatingSpeed();

	//std::cout << "seperatingSpeed " << seperatingSpeed << std::endl;

	// if they are moving appart there is no problem
	if (seperatingSpeed > 0)
	{
		return;
	}

	// the relative speed along the normal after the bounce
	float newSeperationSpeed = -seperatingSpeed * restitution;

	//std::cout << "newSeperationSpeed " << newSeperationSpeed << std::endl;


	///My note: is this is enirely due to collision handeling happening at O(dt) and not O(dt^2)?

	//check if vel is due to accel only
	//objects should be at rest on one another when in free fall
	//accCausedSeperationSpeed is caused by the two objects falling together
	//vec2 seperationAcceleration = particles[0]->acceleration;
	//if (particles[1])
	//{
	//	seperationAcceleration -= particles[1]->acceleration;
	//}
	//const float accCausedSeperationSpeed = seperationAcceleration * contactNormal * duration;

	//are these collision objects falling into each other?
	//set remove that component
	//if (accCausedSeperationSpeed < 0)
	//{
	//	newSeperationSpeed += restitution * accCausedSeperationSpeed;
	//}

	// deltaVel is the total velocity to be delt out to solve the collision
	const float deltaVel = newSeperationSpeed - seperatingSpeed;
	//std::cout << "deltaVel " << deltaVel << std::endl;

	float totalInverseMass = particles[0]->fInvMass;
	if (particles[1])
	{
		totalInverseMass += particles[1]->fInvMass;
	}
	
	// We portion deltaVel propotional to the % of inv mass each partical has
	// so that light things get more of deltaVel and heavy less
	const float impulseMagPerInvMass = deltaVel / totalInverseMass;
	//std::cout << "impulseMagPerInvMass " << impulseMagPerInvMass << std::endl;
	vec2 impulsePerInvMass = contactNormal * impulseMagPerInvMass;
	//std::cout << "impulsePerInvMass.x " << impulsePerInvMass.x << std::endl;
	//std::cout << "impulsePerInvMass.y " << impulsePerInvMass.y << std::endl;


	vec2 deltavP0 = impulsePerInvMass * particles[0]->fInvMass;
	//std::cout << "deltavP0.x " << deltavP0.x << std::endl;
	//std::cout << "deltavP0.y " << deltavP0.y << std::endl;

	particles[0]->velocity += impulsePerInvMass * particles[0]->fInvMass;
	if (particles[1])
	{
		particles[1]->velocity -= impulsePerInvMass * particles[1]->fInvMass;
	}
}

void ParticleContact::resolveInterpenetration(float duration)
{
	if (penetration <= 0)
	{
		return;
	}

	float totalInverseMass = particles[0]->fInvMass;
	if (particles[1])
	{
		totalInverseMass += particles[1]->fInvMass;
	}

	vec2 movePerInvMass = contactNormal * (-penetration / totalInverseMass);

	particles[0]->position += movePerInvMass * particles[0]->fInvMass;
	if (particles[1])
	{
		particles[1]->position -= movePerInvMass * particles[1]->fInvMass;
	}
}
