
#include "GLQuadrangle.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>

#include "Utility.h"

GLQuadrangle::GLQuadrangle(const glm::vec3 corner1, const glm::vec3 corner2, const glm::vec3 corner3, const glm::vec3 corner4)
{
	float* vertexArray = new float[2 * 9];

	vertexArray[0] = corner1.x;
	vertexArray[1] = corner1.y;
	vertexArray[2] = corner1.z;

	vertexArray[3] = corner2.x;
	vertexArray[4] = corner2.y;
	vertexArray[5] = corner2.z;

	vertexArray[6] = corner3.x;
	vertexArray[7] = corner3.y;
	vertexArray[8] = corner3.z;

	vertexArray[9] = corner4.x;
	vertexArray[10] = corner4.y;
	vertexArray[11] = corner4.z;

	vertexArray[12] = corner1.x;
	vertexArray[13] = corner1.y;
	vertexArray[14] = corner1.z;

	vertexArray[15] = corner3.x;
	vertexArray[16] = corner3.y;
	vertexArray[17] = corner3.z;

	makeShader(vertexArray, 2 * 9, "blue_fs.glsl");

	delete[] vertexArray;
}

