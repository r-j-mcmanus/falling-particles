
#include "GLCircle.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>

#include "Utility.h"

GLCircle::GLCircle(const float cfCenterX, const float cfCenterY, const float cfCenterZ, const float cfRadius, const int numberSides)
{
	//noTriangles == numberSides
	//need numberSides>=3

	fRadius = cfRadius;
	fCenterX = cfCenterX;
	fCenterY = cfCenterY;
	fCenterZ = cfCenterZ;

	float angleStep = 2.0f * 3.1415926f / float(numberSides);

	float* circleSlices = new float[numberSides * 9];

	for (int i = 0; i < numberSides; i++)
	{
		circleSlices[0 + i * 9] = fCenterX;
		circleSlices[1 + i * 9] = fCenterY;
		circleSlices[2 + i * 9] = fCenterZ;

		circleSlices[3 + i * 9] = fCenterX + (float)cos(i * angleStep);
		circleSlices[4 + i * 9] = fCenterY + (float)sin(i * angleStep);
		circleSlices[5 + i * 9] = fCenterZ;

		circleSlices[6 + i * 9] = fCenterX + (float)cos((i + 1) * angleStep);
		circleSlices[7 + i * 9] = fCenterY + (float)sin((i + 1) * angleStep);
		circleSlices[8 + i * 9] = fCenterZ;
	}

	/*
	for (int i = 0; i < numberSides; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << circleSlices[0 + 3*j + i * 9] << " " << circleSlices[1 + 3 * j + i * 9] << " " << circleSlices[2 + 3 * j + i * 9] << std::endl;
		}
		std::cout << std::endl;
	}
	*/
	
	makeShader(circleSlices, numberSides * 9);

	delete[] circleSlices;
}

