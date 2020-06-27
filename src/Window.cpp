#include "Window.h"
#include "Camera.h"
#include "Input.h"

#include <GL/glew.h>
#include <stdio.h>

Input input;
Camera cam;

void Window::error_callback(int error, const char* description)
{
    fprintf(stderr, "Error (%d): %s\n", error, description);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
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

GLFWwindow* window;

Window::Window()
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        throw(1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(1920, 1080, "OpenGL", glfwGetPrimaryMonitor(), nullptr);

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

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
Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
