#ifndef WORLD_H
#define WORLD_H

#include "gl/Shader.h"


class World
{
    public:
        World();
        void drawChunks();
        constexpr static unsigned int getSeed() {return m_Seed;}
        ~World();
    protected:

    private:
        static const unsigned int m_Seed {1337};
};

#endif // WORLD_H
