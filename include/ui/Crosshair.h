#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include "Petroleum.h"

class Crosshair
{
    public:
        Crosshair();
        void render();
        virtual ~Crosshair();

    protected:

    private:
        PT::Shader shader;
        PT::VertexBuffer* vbo;
        PT::IndexBuffer ibo;
        PT::VertexArray vao;
};

#endif // CROSSHAIR_H
