#include "GLDrawable.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> //glm::value_ptr
#include <glm/gtc/matrix_transform.hpp> //glm::translate

#include "Utility.h"

#include <iostream>

GLDrawable::GLDrawable()
{
}

void GLDrawable::makeShader(float* vertexArray, int arrayLength)
{
	shaderProgram = loadShader("SimpleTransform_vs.glsl", "test_fs.glsl");

	// Make the vertex buffer to be drawn
	glGenBuffers(1, &vertexBuffer); // "generate" an empty buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // set it as the current buffer
	glBufferData(GL_ARRAY_BUFFER, arrayLength * sizeof(float), vertexArray, GL_STATIC_DRAW); // copy the points to bound buffer

	// The VAO that contains the vertex infomations
	glGenVertexArrays(1, &vertexArrayObject); // generate a new VAO
	glBindVertexArray(vertexArrayObject);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayObject);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	MatrixID = glGetUniformLocation(shaderProgram, "MVP");

	noTriangles = arrayLength / 9;
}

void GLDrawable::makeShader(float* vertexArray, int arrayLength, const char* fragmentShaderPath)
{
	shaderProgram = loadShader("SimpleTransform_vs.glsl", fragmentShaderPath);

	// Make the vertex buffer to be drawn
	glGenBuffers(1, &vertexBuffer); // "generate" an empty buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // set it as the current buffer
	glBufferData(GL_ARRAY_BUFFER, arrayLength * sizeof(float), vertexArray, GL_STATIC_DRAW); // copy the points to bound buffer

	// The VAO that contains the vertex infomations
	glGenVertexArrays(1, &vertexArrayObject); // generate a new VAO
	glBindVertexArray(vertexArrayObject);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayObject);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	MatrixID = glGetUniformLocation(shaderProgram, "MVP");

	noTriangles = arrayLength / 9;
}

void GLDrawable::draw()
{
	glUseProgram(shaderProgram);

	// Update MVP
	//composeTransformation();

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	// read more about this

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
	glBindVertexArray(vertexArrayObject);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                 // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                   // stride
		(void*)0            // array buffer offset
	);

	glDrawArrays(GL_TRIANGLES, 0, 3 * noTriangles);
}

void GLDrawable::composeTransformation(const glm::mat4 Projection, const glm::mat4 View, const glm::mat4 Model)
{
	// Our ModelViewProjection : multiplication of our 3 matrices
	MVP = Projection * View * Model;

	
	if (temp < 1)
	{
		std::cout << "projection \n";
		printMat4(Projection);
		std::cout << "View \n";
		printMat4(View);
		std::cout << "Model \n";
		printMat4(Model);
		temp++;
		std::cout << "MVP \n";
		printMat4(MVP);
		temp++;
	}
	
}