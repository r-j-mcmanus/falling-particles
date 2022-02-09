#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Utility.h"

std::string readFile(const char* filepath)
{
    std::string content;
    std::ifstream fileStream(filepath, std::ios::in);

    if (!fileStream.is_open())
    {
        std::cerr << "could not open file " << filepath << " . File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
};

GLuint loadShader(const char* vertexPath, const char* fragmentPath)
{
    //https://learnopengl.com/Getting-started/Shaders
    //https://badvertex.com/2012/11/20/how-to-load-a-glsl-shader-in-opengl-using-c.html


    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint program = glCreateProgram();

    std::string vertShaderStr = readFile(vertexPath);
    std::string fragShaderStr = readFile(fragmentPath);

    const char* vertShaderSrc = vertShaderStr.c_str();
    const char* fragShaderSrc = fragShaderStr.c_str();

    int success = 1;
    char infoLog[512];

    std::cout << "Compiling vertex shader." << std::endl;
    glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShader);
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    std::cout << "Compiling fragment shader." << std::endl;
    glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return program;
};

float* Mat4ToArray(glm::mat4 MyMatrix)
{
    //https://stackoverflow.com/questions/18890084/how-to-read-the-values-from-a-glmmat4

    static float fArray[16] = { 0 };

    const float* pSource = (const float*)glm::value_ptr(MyMatrix);
    for (int i = 0; i < 16; ++i)
    {
        fArray[i] = pSource[i];
    }

    return fArray;
};

void printMat4(glm::mat4 MyMatrix)
{
    /*
    float* fArray = Mat4ToArray(MyMatrix);

    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            std::cout << *(fArray + 4 * i + j) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    */

    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            std::cout << MyMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
};