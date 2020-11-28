#include "ui/Crosshair.h"

#include <vector>

Crosshair::Crosshair()
    : shader(PT_SHADER_XYRGBA), ibo(std::vector<unsigned char>({0, 1, 2,  0, 2, 3}))
{
    std::vector<float> vertices =
    {
        0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f
    };

    vbo = new PT::VertexBuffer(vertices);
    vao.addBuffer(*vbo, shader.getLayout());
}

void Crosshair::render()
{
    //PT::clearGlErrors();
    shader.bindShader();
    PT::drawVA(vao, ibo, shader);
    PT::getGlErrors();
}

Crosshair::~Crosshair()
{
    delete vbo;
}
