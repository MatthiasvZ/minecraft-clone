#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H


class IndexBuffer
{
    public:
        ~IndexBuffer();

        void addData(const unsigned short* data, unsigned int count);
        void bindBuffer() const;
        void unbindBuffer() const;

        inline unsigned int getCount() const {return m_Count;}
        unsigned int m_RendererID;

    protected:

    private:
        unsigned int m_Count;
};

#endif // INDEXBUFFER_H
