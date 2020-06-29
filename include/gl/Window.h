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
        void countfps();
        ~Window();

    protected:

    private:
        static void error_callback(int error, const char* description);
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

        unsigned int fps;
        float avg_fps {0};
        int seconds {0};
        long tn, ta;
};

#endif // WINDOW_H
