#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "VertexBuffer.h"

class VertexBufferLayout;


class VertexArray
{
    public:
        ~VertexArray();

        void genArray();
        void addBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout);
        void bindArray() const;
        void unbindArray() const;
        unsigned int m_RendererID;

    protected:

    private:

};

#endif // VERTEXARRAY_H
