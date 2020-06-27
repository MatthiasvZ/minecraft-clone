#ifndef WORLD_H
#define WORLD_H

#include "Shader.h"


class World
{
    public:
        World();
        void drawChunks(const Shader& shader);
        ~World();

    protected:

    private:
};

#endif // WORLD_H
