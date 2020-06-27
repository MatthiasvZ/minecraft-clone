#include "ErrorFeedback.h"

#include <GL/glew.h>
#include <iostream>

void ErrorFeedback::clearErrors()
{
    while (glGetError());
}

void ErrorFeedback::getErrors()
{
    while (GLenum error = glGetError())
        std::cerr << "[OpenGL Error] (" << error \
                << ')' << std::endl;
}
