#include "other/FileManagement.h"
#include "gl/Window.h"
#include "game/World.h"
#include "gl/Shader.h"
#include "gl/Texture.h"
#include "gl/Camera.h"

#ifdef DEBUG
#include "other/ErrorFeedback.h"
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

        world.drawChunks();

        window.countfps();
        window.updateWindow();

        #ifdef DEBUG
            ErrorFeedback::getErrors();
        #endif //DEBUG
    }

    return 0; // Destructors handle the rest
}
