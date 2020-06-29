#include "gl/Renderer.h"

#include <ctime>
#include <stdio.h>

Renderer::Renderer()
{
    fps = 0;
    time(&ta);
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

void Renderer::countfps()
{
    if (time(&tn) != ta)
    {
        ta++;
        printf("FPS = %d\n", fps);
        avg_fps += fps;
        seconds++;
        fps = 0;
    }
    fps++;
}

Renderer::~Renderer()
{
    printf("avg. Fps = %f\n", avg_fps/seconds);
}
