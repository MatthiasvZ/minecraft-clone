#include "Petroleum.h"

#include "game/World.h"
#include "ui/Crosshair.h"

#include <iostream>
#include <cstring>
#include <filesystem>

int main()
{
    #if __unix__
        PT::setDataDir(strcat(std::getenv("HOME"), "/.local/share/minecraft-clone"));
    #elif _WIN32
        PT::setDataDir(strcat(std::getenv("HOME"), "/AppData/minecraft-clone"));
    #else
    #error Unsupported OS
    #endif // __unix__

    PT::Config cfg {PT::parseConfig()};
    if (cfg.fresh)
    {
        cfg.opengl_major = 3;
        cfg.opengl_minor = 2;
        cfg.msaa = 0;
        cfg.window_resizable = true;
    }
    cfg.clear_colour = PT_SKY_BLUE;
    cfg.enable_blending = true;
    cfg.capture_mouse = true;

    PT::saveConfig(cfg);

    PT::Window window(cfg);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    PT::initGL(cfg);
    window.changeTitle("Minecraft Clone");

    World world;
    Crosshair ch;


    float deltaTime = 0.0f;
    float lastFrame = glfwGetTime();

    while (window.shouldRun())
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        PT::clearScreen();

        // 3D
        glEnable(GL_DEPTH_TEST);
        world.drawChunks(deltaTime, window.getInputs(), window.mouseLocked());

        // 2D
        glDisable(GL_DEPTH_TEST);
        ch.render();

        window.update();
        PT::doEvents();
        #ifdef DEBUG
            PT::getGlErrors();
        #endif //DEBUG
    }
    return 0;
}
