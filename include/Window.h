#ifndef WINDOW_H
#define WINDOW_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


class Window
{
    public:
        Window();
        bool shouldRun();
        void updateCamera(float deltaTime);
        glm::mat4 getMatrices();
        void updateWindow();
        ~Window();

    protected:

    private:
        static void error_callback(int error, const char* description);
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
};

#endif // WINDOW_H
