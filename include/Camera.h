#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera
{
    public:
        void sprint();
        void stopSprinting();
        void moveForwards();
        void moveBackwards();
        void moveUp();
        void moveLeft();
        void moveDown();
        void moveRight();
        void lookMouse(double xpos, double ypos);
        void lookReset();
        void posReset();
        void setSpeed(const float& deltaTime);
        glm::mat4 getMatrices();

    protected:

    private:
        void updateDirection();
        float movSpeed;
        float movFac {6};
        float turnSpeed;
        const float turnFac {80};
        float m_Pitch;
        float m_Yaw = -90.0f;
        glm::vec3 camPos   = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec3 camFront = glm::vec3(0.0f, 0.0f, 0.0f);
        double lastMousePosX;
        double lastMousePosY;
};

#endif // CAMERA_H
