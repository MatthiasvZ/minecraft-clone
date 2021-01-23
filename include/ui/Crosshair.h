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
        void updateVertices();

        PT::Shader shader;
        PT::VertexBuffer* vbo;
        PT::IndexBuffer ibo;
        PT::VertexArray* vao;

        float aspectRatio;
};

#endif // CROSSHAIR_H
