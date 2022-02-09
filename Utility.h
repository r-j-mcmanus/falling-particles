#pragma once

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#include <string>

#include <glm/glm.hpp>

std::string readFile(const char* filepath);

GLuint loadShader(const char* vertexPath, const char* fragmentPath);

float* Mat4ToArray(glm::mat4 MyMatrix);

void printMat4(glm::mat4 MyMatrix);