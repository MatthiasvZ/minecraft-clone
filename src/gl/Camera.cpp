#include "gl/Camera.h"

#include <stdio.h>


void Camera::sprint()
{
    movFac *= 2;
}

void Camera::stopSprinting()
{
    movFac /= 2;
}

void Camera::moveForwards()
{
    camPos += movSpeed * camFront;
}

void Camera::moveBackwards()
{
    camPos -= movSpeed * camFront;
}

void Camera::moveUp()
{
    camPos.y += movSpeed;
}

void Camera::moveLeft()
{
    camPos -= glm::normalize(glm::cross(camFront, glm::vec3(0.0f, 1.0f, 0.0f))) * movSpeed;
}

void Camera::moveDown()
{
    camPos.y -= movSpeed;
}

void Camera::moveRight()
{
    camPos += glm::normalize(glm::cross(camFront, glm::vec3(0.0f, 1.0f, 0.0f))) * movSpeed;
}

void Camera::lookMouse(double MousePosX, double MousePosY)
{
    m_Yaw += (MousePosX - lastMousePosX) * turnSpeed;
    m_Pitch += (lastMousePosY - MousePosY) * turnSpeed;
    updateDirection();
    lastMousePosX = MousePosX;
    lastMousePosY = MousePosY;
}

void Camera::lookReset()
{
    m_Yaw = -90.f;
    m_Pitch = 0.0f;
}

void Camera::posReset()
{
    camPos.x = 1.0f;
    camPos.y = 1.0f;
    camPos.z = 1.0f;
}

void Camera::setSpeed(const float& deltaTime)
{
    movSpeed = movFac * deltaTime;
}

glm::mat4 Camera::getMatrices()
{
    glm::mat4 projMat  = glm::perspective(glm::radians(90.0f), 16.0f/9.0f, 1.0f, 1000.0f);

    glm::mat4 viewMat  = glm::mat4(glm::lookAt(
            camPos,                         // EYE
            camPos + camFront,              // CENTER
            glm::vec3(0.0f, 1.0f, 0.0f))    // UP
    );

    return projMat * viewMat;
}

void Camera::updateDirection()
{
    if(m_Pitch > 89.99f)
        m_Pitch =  89.99f;
    if(m_Pitch < -89.99f)
        m_Pitch = -89.99f;
    camFront.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    camFront.y = sin(glm::radians(m_Pitch));
    camFront.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
}
