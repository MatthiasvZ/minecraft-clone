#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Chunk.h"


class Renderer
{
    public:
        Renderer();
        void clear() const;
        void drawVA(const VertexArray& vao, const VertexBuffer& vbo, const IndexBuffer& ibo, const Shader& shader) const;
        void countfps();
        ~Renderer();

    protected:

    private:
        unsigned int m_Fps;
        float m_Avg_Fps {0};
        int m_Seconds {0};
        long m_Tn, m_Ta;
};

#endif // RENDERER_H
