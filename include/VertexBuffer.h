#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H


class VertexBuffer
{
    public:
        ~VertexBuffer();

        void addData(const void* data, unsigned int size);
        void bindBuffer() const;
        void unbindBuffer() const;

    protected:

    private:
        unsigned int m_RendererID;
};

#endif // VERTEXBUFFER_H
