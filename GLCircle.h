#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "GLDrawable.h"

//https://www.youtube.com/watch?v=YDCSKlFqpaU
//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/

class GLCircle : virtual public GLDrawable {
public:
	GLCircle(const float cfCenterX, const float cfCenterY, const float cfCenterZ, const float cfRadius, const int noSides);

private:
	float fRadius;
	float fCenterX;
	float fCenterY;
	float fCenterZ;
};
