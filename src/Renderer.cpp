#include "Renderer.h"

#include <ctime>
#include <stdio.h>

Renderer::Renderer()
{
    m_Fps = 0;
    time(&m_Ta);
}

void Renderer::clear() const
{
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::drawVA(const VertexArray& vao, const VertexBuffer& vbo, const IndexBuffer& ibo, const Shader& shader) const
{
    shader.bindShader();
    vao.bindArray();
    vbo.bindBuffer();
    ibo.bindBuffer();
    glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, nullptr);
}

void Renderer::countfps()
{
    if (time(&m_Tn) != m_Ta)
    {
        m_Ta++;
        printf("FPS = %d\n", m_Fps);
        m_Avg_Fps += m_Fps;
        m_Seconds++;
        m_Fps = 0;
    }
    m_Fps++;
}

Renderer::~Renderer()
{
    printf("avg. Fps = %f\n", m_Avg_Fps/m_Seconds);
}
