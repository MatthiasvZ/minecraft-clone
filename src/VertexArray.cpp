#include "VertexArray.h"

#include "VertexBufferLayout.h"
#include "Renderer.h"

#include <iostream>


void VertexArray::genArray()
{
    glGenVertexArrays(1, &m_RendererID);
}

void VertexArray::addBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout)
{
    VertexArray::bindArray();
    vbo.bindBuffer();
    const auto& elements = layout.getElements();
    unsigned long offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, \
                element.normalised, layout.getStride(), (const void*)offset);
        offset += element.count*VertexBufferElement::getSizeOfType(element.type);
    }
}

void VertexArray::bindArray() const
{
    glBindVertexArray(m_RendererID);
}

void VertexArray::unbindArray() const
{
    glBindVertexArray(0);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);
}
