#include "gl/Window.h"
#include "gl/Camera.h"
#include "gl/Input.h"
#include "gl/Renderer.h"

#include <GL/glew.h>
#include <ctime>
#include <stdio.h>

Input input;
Camera cam;

void Window::error_callback(int error, const char* description)
{
    fprintf(stderr, "Error (%d): %s\n", error, description);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    static bool fullscreen {false};
    static int windowPosX, windowPosY;
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_ESCAPE:  glfwSetWindowShouldClose(window, GLFW_TRUE); break;
        case GLFW_KEY_LEFT_CONTROL: input.ctrlHeld = true;
                                    cam.sprint();             break;
        case GLFW_KEY_SPACE:      input.spaceHeld = true;     break;
        case GLFW_KEY_LEFT_SHIFT: input.shiftHeld = true;     break;
        case GLFW_KEY_W:            input.wHeld   = true;     break;
        case GLFW_KEY_A:            input.aHeld   = true;     break;
        case GLFW_KEY_S:            input.sHeld   = true;     break;
        case GLFW_KEY_D:            input.dHeld   = true;     break;
        case GLFW_KEY_DOWN:        input.downHeld = true;     break;
        case GLFW_KEY_LEFT:        input.leftHeld = true;     break;
        case GLFW_KEY_RIGHT:      input.rightHeld = true;     break;
        case GLFW_KEY_UP:           input.upHeld  = true;     break;
        case GLFW_KEY_KP_2:         input.kp2Held = true;     break;
        case GLFW_KEY_KP_4:         input.kp4Held = true;     break;
        case GLFW_KEY_KP_5:         input.kp5Held = true;     break;
        case GLFW_KEY_KP_6:         input.kp6Held = true;     break;
        case GLFW_KEY_KP_8:         input.kp8Held = true;     break;
        case GLFW_KEY_F11:
            if (!fullscreen)
            {
                glfwGetWindowPos(window, &windowPosX, &windowPosY);
                glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, 1920, 1080, GLFW_DONT_CARE);
                fullscreen = true;
            }
            else
            {
                glfwSetWindowMonitor(window, nullptr, windowPosX, windowPosY, 1280, 720, GLFW_DONT_CARE);
                fullscreen = false;
            }
        }
    }
    if (action == GLFW_RELEASE)
    {
        switch (key)
        {
        case GLFW_KEY_LEFT_CONTROL: input.ctrlHeld = false;
                                    cam.stopSprinting();      break;
        case GLFW_KEY_SPACE:      input.spaceHeld = false;    break;
        case GLFW_KEY_LEFT_SHIFT: input.shiftHeld = false;    break;
        case GLFW_KEY_W:            input.wHeld   = false;    break;
        case GLFW_KEY_A:            input.aHeld   = false;    break;
        case GLFW_KEY_S:            input.sHeld   = false;    break;
        case GLFW_KEY_D:            input.dHeld   = false;    break;
        case GLFW_KEY_DOWN:        input.downHeld = false;    break;
        case GLFW_KEY_LEFT:        input.leftHeld = false;    break;
        case GLFW_KEY_RIGHT:      input.rightHeld = false;    break;
        case GLFW_KEY_UP:           input.upHeld  = false;    break;
        case GLFW_KEY_KP_2:         input.kp2Held = false;    break;
        case GLFW_KEY_KP_4:         input.kp4Held = false;    break;
        case GLFW_KEY_KP_5:         input.kp5Held = false;    break;
        case GLFW_KEY_KP_6:         input.kp6Held = false;    break;
        case GLFW_KEY_KP_8:         input.kp8Held = false;    break;
        }
    }
}

void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{

}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
GLFWwindow* window;

Window::Window()
{
    fps = 0;
    time(&ta);

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(-1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(1280, 720, "OpenGL, FPS = 0", nullptr, nullptr);

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    glewExperimental = true;
    if (glewInit())
        fprintf(stderr, "Error during glewInit(), %d\n", glewInit());
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    fprintf(stdout, "Status: Using OpenGL %s\n", glGetString(GL_VERSION));

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    glFrontFace(GL_CW);
}

bool Window::shouldRun()
{
    return !glfwWindowShouldClose(window);
}

void Window::updateCamera(float deltatime)
{
    cam.setSpeed(deltatime);
    if (input.downHeld || input.sHeld)
        cam.moveBackwards();
    if (input.rightHeld || input.dHeld)
        cam.moveRight();
    if (input.leftHeld || input.aHeld)
        cam.moveLeft();
    if (input.upHeld || input.wHeld)
        cam.moveForwards();
    if (input.spaceHeld)
        cam.moveUp();
    if (input.shiftHeld)
        cam.moveDown();
    if (input.kp5Held && !input.ctrlHeld)
        cam.lookReset();
    if (input.kp5Held && input.ctrlHeld)
        cam.posReset();

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    cam.lookMouse(xpos, ypos);
}

glm::mat4 Window::getMatrices()
{
    return cam.getMatrices();
}

void Window::updateWindow()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::countfps()
{
    if (time(&tn) != ta)
    {
        ta++;
        glfwSetWindowTitle(window, ("OpenGL, FPS =" + std::to_string(fps)).c_str());
        fps = fps;
        avg_fps += fps;
        seconds++;
        fps = 0;
    }
    fps++;
}

Window::~Window()
{
    printf("avg. Fps = %f\n", avg_fps/seconds);
    glfwDestroyWindow(window);
    glfwTerminate();
}
