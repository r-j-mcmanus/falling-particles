#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "GLDrawable.h"

//https://www.youtube.com/watch?v=YDCSKlFqpaU
//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/

class GLQuadrangle : virtual public GLDrawable {
public:
	GLQuadrangle(const glm::vec3 corner1, const glm::vec3 corner2, const glm::vec3 corner3, const glm::vec3 corner4);
private:
};
