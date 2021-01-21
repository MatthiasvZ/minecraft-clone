#include "ui/Crosshair.h"

#include <vector>

namespace PT
{
    std::vector<float> coloriseXY(const std::vector<float>& vertices, float r, float g, float b, float a)
    {
        std::vector<float> result;
        result.reserve(3 * vertices.size());

        for (unsigned long int i {0}; i < vertices.size() / 2; ++i)
        {
            result.push_back(vertices[2 * i]);
            result.push_back(vertices[2 * i + 1]);
            result.push_back(r);
            result.push_back(g);
            result.push_back(b);
            result.push_back(a);
        }
        return result;
    }
}

Crosshair::Crosshair()
    : shader(PT_SHADER_XYRGBA), ibo(std::vector<unsigned char>({0, 1, 2,  0, 2, 3}))
{
    std::vector<float> vertices(PT::coloriseXY(PT::tVertsSquareXY(0.0f, 0.0f, 0.02f, true), 0.0f, 1.0f, 0.0f, 0.5f));

    vbo = new PT::VertexBuffer(vertices);
    vao.addBuffer(*vbo, shader.getLayout());

}

void Crosshair::render()
{
    shader.bindShader();
    PT::drawVA(vao, ibo, shader);
}

Crosshair::~Crosshair()
{
    delete vbo;
}
