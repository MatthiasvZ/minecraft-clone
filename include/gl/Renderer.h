#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>

#include "gl/VertexArray.h"
#include "gl/IndexBuffer.h"
#include "gl/Shader.h"
#include "game/Chunk.h"


class Renderer
{
    public:
        Renderer();
        void clear() const;
        void drawVA(const VertexArray& vao, const VertexBuffer& vbo, const IndexBuffer& ibo) const;
        void countfps();
        ~Renderer();

    protected:

    private:
        unsigned int fps;
        float avg_fps {0};
        int seconds {0};
        long tn, ta;
};

#endif // RENDERER_H
