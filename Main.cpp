#include "Petroleum.h"

#include "game/World.h"

#include <iostream>
#include <cstring>

int main()
{
    PT::setDataDir(strcat(std::getenv("HOME"), "/.local/share/minecraft-clone"));
    PT::Config cfg {PT::parseConfig()};
    cfg.clear_colour = PT_SKY_BLUE;
    cfg.msaa = 0;
    PT::saveConfig(cfg);

    PT::Window window(cfg);
    PT::initGL(cfg);
    window.changeTitle("Minecraft Clone");

    World world;

    float deltaTime = 0.0f;
    float lastFrame = glfwGetTime();
    while (window.shouldRun())
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        PT::clearScreen();

        world.drawChunks(deltaTime, window.getInputs());

        window.update();
        PT::doEvents();
        #ifdef DEBUG
            PT::getGlErrors();
        #endif //DEBUG
    }
    return 0;
}
