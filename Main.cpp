#include "FileManagement.h"
#include "Window.h"
#include "World.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

#ifdef DEBUG
#include "ErrorFeedback.h"
#endif //DEBUG

#include <iostream>


int main()
{
    FileManagement::setWorkingDir();
    FileManagement::createFolders();

    Window window;

    SourcePackage srcpkg(Shader::readFromFile("src/shaders/BasicTexVertex.glsl"), \
                         Shader::readFromFile("src/shaders/BasicTexFragment.glsl"));
    Shader shader(srcpkg);
    shader.bindShader();

    Texture kitten("assets/texAtlas.bmp", 0);
    shader.setUniform1i("tex", 0);

    World world;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    while (window.shouldRun())
    {
        window.updateCamera(deltaTime);
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        shader.setUniformMat4f("u_MVP", window.getMatrices());

        world.drawChunks(shader);

        window.updateWindow();

        #ifdef DEBUG
            ErrorFeedback::getErrors();
        #endif //DEBUG
    }

    return 0; // Destructors handle the rest
}
