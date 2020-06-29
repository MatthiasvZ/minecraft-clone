#include "gl/Renderer.h"

Renderer::Renderer()
{

}

void Renderer::clear() const
{
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::drawVA(const VertexArray& vao, const VertexBuffer& vbo, const IndexBuffer& ibo) const
{
    vao.bindArray();
    vbo.bindBuffer();
    ibo.bindBuffer();
    glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr);
    #ifdef DEBUG
        vao.unbindArray();
        vbo.unbindBuffer();
        ibo.unbindBuffer();
    #endif // DEBUG
}



Renderer::~Renderer()
{

}
