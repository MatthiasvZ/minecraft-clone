#include "Ray.h"
#include <glm/glm.hpp>
#include <cstdio>


void Ray::step(float amount)
{
    x += glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch)) * amount;
//    fprintf(stderr, "yaw = %f, cos(yaw) = %f\n", yaw, glm::cos(glm::radians(yaw)));
    y += glm::sin(glm::radians(pitch)) * amount;
//    fprintf(stderr, "pitch = %f, sin(pitch) = %f\n", pitch, glm::sin(glm::radians(pitch)));
    z += glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch)) * amount;
//    fprintf(stderr, "yaw = %f, sin(yaw) = %f\n\n", yaw, glm::sin(glm::radians(yaw)));
}
