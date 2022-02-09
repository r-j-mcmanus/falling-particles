#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

//https://www.youtube.com/watch?v=YDCSKlFqpaU
//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/

class GLDrawable {
public:
	GLDrawable();

	void draw();
	void makeShader(float* vertexArray, int arrayLength);
	void makeShader(float* vertexArray, int arrayLength, const char* fragmentShaderPath);
	void composeTransformation(const glm::mat4 Projection, const glm::mat4 View, const glm::mat4 Model);

private:
	GLuint shaderProgram = NULL;
	GLuint vertexBuffer = NULL;

	GLuint vertexArrayObject = NULL;

	GLuint MatrixID = NULL;

	int noTriangles = 0;

	glm::mat4 MVP = glm::mat4(1.0f);

	int temp = 0;
};
