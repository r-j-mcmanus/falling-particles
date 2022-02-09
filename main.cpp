//https://antongerdelan.net/opengl/hellotriangle.html

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> //glm::lookAt
#include <stdio.h>

#include <cstdlib>
#include <iostream>

#include "GLCircle.h"
#include "GLQuadrangle.h"
#include "particle.h"   
#include "ParticalContact.h"

#include "Utility.h"

glm::mat4 updatePosition()
{
    const float fLoopDuration = 5.0f;
    const float fScale = 3.1415926f * 2.0f / fLoopDuration;

    const float currentTime = (float)glfwGetTime();

    const float fCurrentTimeThroughLoop = fmodf(currentTime, fLoopDuration);

    const glm::vec3 translationVector = glm::vec3(sinf(fCurrentTimeThroughLoop * fScale) * 0.5f, cosf(fCurrentTimeThroughLoop * fScale) * 0.5f, 0.0f);

    return glm::translate(glm::mat4(1.0f), translationVector);
}

int main() {

    // start GL context and O/S window using the GLFW helper library
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);


    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        glfwTerminate();
        return -1;
    }

    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

    ///
    ///
    ///  
    
    GLCircle myCircles[3]{
        {0, 0, 5.0f, 1.0f, 8},
        {0, 0, 5.0f, 1.0f, 8},
        {0, 0, 5.0f, 1.0f, 8}
    };

    GLQuadrangle myFloor(
        glm::vec3(-10, 0, 10),
        glm::vec3(-10, 0, -10),
        glm::vec3(10, 0, -10),
        glm::vec3(10, 0, 10)
    );

    // Camera matrix
    glm::mat4 M4view = glm::lookAt(
        glm::vec3(0, 1, -10), // Camera is at (4,3,3), in World Space
        glm::vec3(0, 0, 0), // and looks at the origin
        glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Projection matrix : 45° Field of View, 4 : 3 ratio, display range : 0.1 unit < -> 100 units
    const glm::mat4 M4projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 M4model = glm::mat4(1.0f);

    Particle particles[3];

    particles[0].position = vec2(0.0f,1.5f);
    particles[0].velocity = vec2(0.0f, 0.0f);
    particles[0].acceleration = vec2(0,-10);
    
    particles[1].position = vec2(-4.0f, 3.0f);
    particles[1].velocity = vec2(2.0f, 5.0f);
    particles[1].acceleration = vec2(0.0f, -10.0f);

    particles[2].position = vec2(1.5f, 3.0f);
    particles[2].velocity = vec2(-4.0f, 5.0f);
    particles[2].acceleration = vec2(0.0f, -10.0f);

    float currentTime = (float)glfwGetTime();
    float dt = 1.0f / 120.0f;
    float T = 0;

    ParticleContact particalContact;

    float minSep = 0;
    float pSeperation = 0;

    while (!glfwWindowShouldClose(window)) {

        T += (float)glfwGetTime() - currentTime;
        currentTime = (float)glfwGetTime();

        while (T > dt)
        {
            particles[0].integrate(dt);
            particles[1].integrate(dt);
            particles[2].integrate(dt);

            if (particles[0].position.y <= particles[0].fRadius)
            {
                particalContact.particles[0] = &particles[0];
                particalContact.particles[1] = NULL;
                particalContact.contactNormal = vec2(0, 1);
                particalContact.resolve(dt);
            }

            pSeperation = seperationSquared(particles[1].position, particles[2].position);
            minSep = (particles[1].fRadius + particles[2].fRadius) * (particles[1].fRadius + particles[2].fRadius);
            std::cout << "pSeperation " << pSeperation << " minSep " << minSep << " equality " << (pSeperation < minSep) << std::endl;

            if (seperationSquared(particles[1].position, particles[2].position) <= (particles[1].fRadius + particles[2].fRadius) * (particles[1].fRadius + particles[2].fRadius))
            {
                particalContact.particles[0] = &particles[1];
                particalContact.particles[1] = &particles[2];
                particalContact.contactNormal = vec2(-1,0);// (particles[1].position - particles[2].position).normalised();
                particalContact.resolve(dt);
                break;
            }

            // wipe the drawing surface clear
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            myCircles[0].composeTransformation(M4projection, M4view, particles[0].getTranslationMatrix());
            myCircles[0].draw();

            myCircles[1].composeTransformation(M4projection, M4view, particles[1].getTranslationMatrix());
            myCircles[1].draw();

            myCircles[2].composeTransformation(M4projection, M4view, particles[2].getTranslationMatrix());
            myCircles[2].draw();

            myFloor.composeTransformation(M4projection, M4view, glm::mat4(1.0));
            myFloor.draw();

            // update other events like input handling 
            glfwPollEvents();
            // put the stuff we've been drawing onto the display
            glfwSwapBuffers(window);

            T -= dt;
        }
    }

    // close GL context and any other GLFW resources
    glfwTerminate();

    return 1;
}
