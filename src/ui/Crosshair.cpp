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
    float vp[4];
    glGetFloatv(GL_VIEWPORT, vp);
    aspectRatio = vp[2] / vp[3];

    updateVertices();
}

void Crosshair::render()
{
    float vp[4];
    glGetFloatv(GL_VIEWPORT, vp);
    if(vp[2] / vp[3] != aspectRatio)
    {
        vao->remove();
        vbo->remove();
        delete vao;
        delete vbo;

        aspectRatio = vp[2] / vp[3];
        updateVertices();
    }

    PT::drawVA(*vao, ibo, shader);
}

void Crosshair::updateVertices()
{
    constexpr float centre = 0.0f;
    constexpr float size = 0.01f;
    std::vector<float> vertices
    {// X                          Y
        centre - size/aspectRatio, centre - size,
        centre - size/aspectRatio, centre + size,
        centre + size/aspectRatio, centre + size,
        centre + size/aspectRatio, centre - size
    };

    vertices = PT::coloriseXY(vertices, 0.0f, 1.0f, 0.0f, 0.5f);

    vbo = new PT::VertexBuffer(vertices);
    vao = new PT::VertexArray();
    vao->addBuffer(*vbo, shader.getLayout());
}

Crosshair::~Crosshair()
{
    vao->remove();
    vbo->remove();
    delete vao;
    delete vbo;
}
