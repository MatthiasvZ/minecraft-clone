#include "IndexBuffer.h"

#include "Renderer.h"
#include <stdio.h>

void IndexBuffer::addData(const unsigned short* data, unsigned int count)
{
    m_Count = count;
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned short), data, GL_STATIC_DRAW);
}

void IndexBuffer::bindBuffer() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

}

void IndexBuffer::unbindBuffer() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}
