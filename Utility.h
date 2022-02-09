#pragma once

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#include <string>

#include <glm/glm.hpp>

#include "vec2.h"

std::string readFile(const char* filepath);

GLuint loadShader(const char* vertexPath, const char* fragmentPath);

float* Mat4ToArray(glm::mat4 MyMatrix);

void printMat4(glm::mat4 MyMatrix);

float seperationSquared(const vec2 v1, const vec2 v2);